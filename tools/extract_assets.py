#!/usr/bin/env python3
"""
Extract the embedded game assets from an original Sumotori Dreams executable
into C++ include files used by the recompilation.

Usage:
    python -I tools/extract_assets.py <path/to/sumofull.exe|sumoeditor.exe> [outdir]

The assets live in the initialized .data section of the original image:

    XM module        0x436070  ("rob me if you can", 16 channels)
    ATG programs     0x44e520 .. 0x44f5c0  (procedural texture scripts)
    GSM 6.10 WAVs    0x44eec0 .. 0x4528f0  (sound effects, decoded via ACM)

Both shipped builds (full 2010-01-06 and editor 2010-01-16) contain byte-identical
asset data, so either executable may be used as the source.
"""

import hashlib
import os
import struct
import sys

KNOWN_IMAGES = {
    "c9a91302e4b7e168a65352642e734efaf27a327ce272eb823f68b6bdc1cae2e3": "sumofull.exe",
    "252c1adc81fd97aa55a415aea1fc60d3a0d136c59b33b5a649b81261d5089155": "sumoeditor.exe",
}

# (symbol, virtual address, used-by-game)
ATG_PROGRAMS = [
    ("kAtg_44e520", 0x44E520, True),
    ("kAtg_44e5b0", 0x44E5B0, False),
    ("kAtg_44e740", 0x44E740, True),
    ("kAtg_44e7c0", 0x44E7C0, True),
    ("kAtg_44e830", 0x44E830, True),
    ("kAtg_44e910", 0x44E910, False),
    ("kAtg_44e9f0", 0x44E9F0, True),
    ("kAtg_44ea40", 0x44EA40, False),
    ("kAtg_44eae0", 0x44EAE0, True),
    ("kAtg_44ebc0", 0x44EBC0, True),
    ("kAtg_44ecb0", 0x44ECB0, True),
    ("kAtg_44ed50", 0x44ED50, True),
    ("kAtg_44edd0", 0x44EDD0, True),
    ("kAtg_44ee40", 0x44EE40, True),
    ("kAtg_44f4b0", 0x44F4B0, True),
    ("kAtg_44f550", 0x44F550, True),
    ("kAtg_44f5c0", 0x44F5C0, False),
]

WAVES = [
    ("kWave_44eec0", 0x44EEC0, True),
    ("kWave_44f640", 0x44F640, True),
    ("kWave_44fbf0", 0x44FBF0, True),
    ("kWave_4502e0", 0x4502E0, True),
    ("kWave_450a90", 0x450A90, False),
    ("kWave_4510f0", 0x4510F0, True),
    ("kWave_451820", 0x451820, False),
    ("kWave_4528f0", 0x4528F0, True),
]

XM_SONG_VA = 0x436070


class PeImage:
    def __init__(self, data):
        self.data = data
        e_lfanew = struct.unpack_from("<I", data, 0x3C)[0]
        if data[e_lfanew:e_lfanew + 4] != b"PE\0\0":
            raise ValueError("not a PE image")
        nsec = struct.unpack_from("<H", data, e_lfanew + 6)[0]
        opt_size = struct.unpack_from("<H", data, e_lfanew + 20)[0]
        self.image_base = struct.unpack_from("<I", data, e_lfanew + 24 + 28)[0]
        self.sections = []
        off = e_lfanew + 24 + opt_size
        for _ in range(nsec):
            name = data[off:off + 8].rstrip(b"\0").decode("latin1")
            vsize, va, rsize, raw = struct.unpack_from("<IIII", data, off + 8)
            self.sections.append((name, va, vsize, raw, rsize))
            off += 40

    def offset(self, va):
        rva = va - self.image_base
        for _, sva, _, raw, rsize in self.sections:
            if sva <= rva < sva + rsize:
                return raw + (rva - sva)
        raise ValueError("VA 0x%x not file-backed" % va)

    def read(self, va, size):
        off = self.offset(va)
        return self.data[off:off + size]


def xm_length(img, va):
    """Walk the XM structure to obtain the exact module length."""
    d = img.data
    p = base = img.offset(va)
    if d[p:p + 17] != b"Extended Module: ":
        raise ValueError("XM signature not found")
    header_size = struct.unpack_from("<I", d, p + 60)[0]
    num_patterns = struct.unpack_from("<H", d, p + 70)[0]
    num_instruments = struct.unpack_from("<H", d, p + 72)[0]
    q = p + 60 + header_size
    for _ in range(num_patterns):
        hdr_len = struct.unpack_from("<I", d, q)[0]
        data_len = struct.unpack_from("<H", d, q + 7)[0]
        q += hdr_len + data_len
    for _ in range(num_instruments):
        inst_size = struct.unpack_from("<I", d, q)[0]
        num_samples = struct.unpack_from("<H", d, q + 27)[0]
        sample_hdr = struct.unpack_from("<I", d, q + 29)[0] if num_samples else 0
        r = q + inst_size
        lengths = []
        for _ in range(num_samples):
            lengths.append(struct.unpack_from("<I", d, r)[0])
            r += sample_hdr
        q = r + sum(lengths)
    return q - base


def atg_length(img, va):
    hdr = img.read(va, 4)
    if hdr[:3] != b"ATG":
        raise ValueError("ATG signature missing at 0x%x" % va)
    count = hdr[3]
    length = 4
    for i in range(count):
        op = img.read(va + 4 + i * 9, 1)[0]
        length += 9
        if op == 0x28:  # 1-bit 256x256 bitmap follows the instruction stream
            length += 0x2000
    return length


def wave_length(img, va):
    hdr = img.read(va, 8)
    if hdr[:4] != b"RIFF":
        raise ValueError("RIFF signature missing at 0x%x" % va)
    return struct.unpack_from("<I", hdr, 4)[0] + 8


def emit_array(out, name, blob, comment):
    out.append("// %s\n" % comment)
    out.append("alignas(4) const unsigned char %s[%d] = {\n" % (name, len(blob)))
    for i in range(0, len(blob), 16):
        out.append("    " + ",".join("0x%02x" % b for b in blob[i:i + 16]) + ",\n")
    out.append("};\n\n")


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        return 1
    exe_path = sys.argv[1]
    here = os.path.dirname(os.path.abspath(__file__))
    out_dir = sys.argv[2] if len(sys.argv) > 2 else os.path.join(here, "..", "src", "generated")
    with open(exe_path, "rb") as f:
        data = f.read()
    digest = hashlib.sha256(data).hexdigest()
    if digest not in KNOWN_IMAGES:
        print("error: %s is not a recognised Sumotori Dreams build (sha256 %s)" % (exe_path, digest))
        return 1
    img = PeImage(data)
    os.makedirs(out_dir, exist_ok=True)

    header = [
        "// Generated by tools/extract_assets.py from %s.\n" % KNOWN_IMAGES[digest],
        "// sha256 %s\n" % digest,
        "// Do not edit; re-run the extractor instead.\n\n",
    ]

    xm_len = xm_length(img, XM_SONG_VA)
    out = list(header)
    emit_array(out, "kXmSong", img.read(XM_SONG_VA, xm_len),
               "XM module at 0x%x (%d bytes)" % (XM_SONG_VA, xm_len))
    with open(os.path.join(out_dir, "music_data.inc"), "w", newline="\n") as f:
        f.writelines(out)

    out = list(header)
    for name, va, used in ATG_PROGRAMS:
        n = atg_length(img, va)
        emit_array(out, name, img.read(va, n),
                   "ATG texture program at 0x%x (%d bytes)%s" % (va, n, "" if used else ", unreferenced by the game"))
    with open(os.path.join(out_dir, "texture_programs.inc"), "w", newline="\n") as f:
        f.writelines(out)

    out = list(header)
    for name, va, used in WAVES:
        n = wave_length(img, va)
        emit_array(out, name, img.read(va, n),
                   "GSM 6.10 WAVE at 0x%x (%d bytes)%s" % (va, n, "" if used else ", unreferenced by the game"))
    with open(os.path.join(out_dir, "sound_data.inc"), "w", newline="\n") as f:
        f.writelines(out)

    print("extracted assets from %s into %s" % (KNOWN_IMAGES[digest], os.path.abspath(out_dir)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
