// Ghidra headless script used to complement the REA analysis.
//
// REA's Windows Ghidra profile cannot mutate the analysis database, so routines
// that are only reachable through data tables (script builtins, window
// procedures, MiniFMOD callbacks) are never disassembled.  This script creates
// those functions, then writes a complete assembly listing and pseudocode for
// the game portion of the image (0x401000-0x41c550; the remainder is the
// statically linked MSVC 7.1 runtime).
//
// Usage (see tools/ghidra/dump_game_code.bat):
//   analyzeHeadless <proj> <name> -import <exe> -postScript DumpGameCode.java <outdir>
//@category SumoRecomp

import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;

import java.io.File;
import java.io.PrintWriter;

public class DumpGameCode extends GhidraScript {

    private static final long[] TABLE_ONLY_ENTRIES = {
        0x404872L, // script builtin selx()
        0x404ce4L, // script builtin breakability()
        0x404e53L, // script builtin man()
        0x404f6cL, // script builtin cutplane()
        0x40778fL, // pointer stored at 0x4536cc
        0x407c85L, // XM memory file open callback
        0x407d15L, // XM memory file close callback
        0x4158c7L, // texture generation progress callback
        0x415ed4L, // settings dialog window procedure
        0x4188c7L, // MiniFMOD XM tick callback
    };

    @Override
    public void run() throws Exception {
        String outDir = getScriptArgs().length > 0 ? getScriptArgs()[0] : ".";
        new File(outDir).mkdirs();

        for (long a : TABLE_ONLY_ENTRIES) {
            Address addr = toAddr(a);
            if (getInstructionAt(addr) == null) {
                new DisassembleCommand(addr, null, true).applyTo(currentProgram, monitor);
            }
            if (getFunctionAt(addr) == null) {
                new CreateFunctionCmd(addr).applyTo(currentProgram, monitor);
            }
        }
        analyzeChanges(currentProgram);

        Address lo = toAddr(0x401000L);
        Address hi = toAddr(0x41c54fL);
        AddressSet game = new AddressSet(lo, hi);

        try (PrintWriter asm = new PrintWriter(new File(outDir, "sumofull_game.asm"), "UTF-8")) {
            InstructionIterator it = currentProgram.getListing().getInstructions(game, true);
            Function current = null;
            while (it.hasNext() && !monitor.isCancelled()) {
                Instruction ins = it.next();
                Function f = getFunctionContaining(ins.getAddress());
                if (f != null && f != current && f.getEntryPoint().equals(ins.getAddress())) {
                    asm.println();
                    asm.println("; ==== " + f.getName() + " @ " + f.getEntryPoint() + " ====");
                    current = f;
                }
                asm.println(ins.getAddress() + ": " + ins.toString());
            }
        }

        DecompInterface dec = new DecompInterface();
        dec.openProgram(currentProgram);
        try (PrintWriter c = new PrintWriter(new File(outDir, "sumofull_table_only_functions.c"), "UTF-8")) {
            for (long a : TABLE_ONLY_ENTRIES) {
                Function f = getFunctionAt(toAddr(a));
                if (f == null) {
                    c.println("// ==== 0x" + Long.toHexString(a) + " : no function ====");
                    continue;
                }
                DecompileResults r = dec.decompileFunction(f, 120, monitor);
                c.println("// ==== 0x" + Long.toHexString(a) + " ====");
                c.println(r.decompileCompleted() ? r.getDecompiledFunction().getC() : "// decompilation failed");
            }
        }
        dec.dispose();
        println("DumpGameCode: wrote listing to " + outDir);
    }
}
