// Direct3D 9 device management, transforms and texture helpers.
#include "d3d.h"
#include "../platform/window.h"

IDirect3D9 *g_d3d;                 // @ 0x4571e4
IDirect3DDevice9 *g_device;        // @ 0x4571ec
IDirect3DSurface9 *g_backBuffer;   // @ 0x4571e0
D3DCAPS9 g_caps;                   // @ 0x457200
int g_screenWidth;                 // @ 0x457334
int g_screenHeight;                // @ 0x457338
int g_screenBits;                  // @ 0x4571f4
int g_screenRefresh;               // @ 0x4571f0
char g_windowed;                   // @ 0x45733c
int g_windowWidth = 400;           // @ 0x4533e4
int g_windowHeight = 300;          // @ 0x4533e8
float g_aspect = 1.333f;           // @ 0x4533f0

float g_pickOffsetX;               // @ 0x45509c
float g_pickOffsetY;               // @ 0x455094
float g_pickScaleX;                // @ 0x4550a0
float g_pickScaleY;                // @ 0x455098

Vec3 g_renderPos;                  // @ 0x4550a4
Mat3 g_renderRot;                  // @ 0x4550b0

static DisplayMode *g_displayModes;  // @ 0x457158
static int g_adapterCount;           // @ 0x45715c

// @ 0x40386a
void setProjection()
{
    float aspect = g_aspect;
    double t = fp::tan(0.6544984877109528); // 37.5 degrees
    float sx = (float)(t / aspect);
    const double minWidth = 0.55f;
    if (sx < minWidth) {
        t = (t / sx) * minWidth;
        sx = (float)minWidth;
    }
    double invT = 1.0 / t;
    double invSx = 1.0 / sx;
    g_pickOffsetX = (float)(-0.5f * (double)g_windowWidth);
    g_pickOffsetY = (float)(-0.5f * (double)g_windowHeight);
    g_pickScaleX = (float)((2.0f / invT) / g_windowWidth);
    g_pickScaleY = (float)((2.0f / invSx) / g_windowHeight);

    D3DMATRIX m;
    memset(&m, 0, sizeof(m));
    m._11 = (float)invT;
    m._22 = (float)invSx;
    *(DWORD *)&m._33 = 0x3f8000d2;   // 1.000025
    m._34 = 1.0f;
    *(DWORD *)&m._43 = 0xbdccce1d;   // -0.1000025
    m._44 = 0.0f;
    g_device->SetTransform(D3DTS_PROJECTION, &m);
}

// @ 0x40397a  (translation already expressed in camera space)
void setViewTransform(const Vec3 &translation, const Mat3 &rot)
{
    D3DMATRIX m;
    m._11 = rot.m[0];
    m._12 = rot.m[3];
    m._13 = rot.m[6];
    m._14 = 0.0f;
    m._21 = rot.m[1];
    m._22 = rot.m[4];
    m._23 = rot.m[7];
    m._24 = 0.0f;
    m._31 = rot.m[2];
    m._32 = rot.m[5];
    m._33 = rot.m[8];
    m._34 = 0.0f;
    m._41 = -translation.x;
    m._42 = -translation.y;
    m._43 = -translation.z;
    m._44 = 1.0f;
    g_device->SetTransform(D3DTS_VIEW, &m);
}

// @ 0x4039f6
void applyRenderView()
{
    Vec3 t = g_renderRot * g_renderPos;
    setViewTransform(t, g_renderRot);
}

// @ 0x403a1e
static int findAdapter(const GUID *adapter, IDirect3D9 *d3d)
{
    D3DADAPTER_IDENTIFIER9 id;
    g_adapterCount = d3d->GetAdapterCount();
    for (int i = 0; i < g_adapterCount; ++i) {
        d3d->GetAdapterIdentifier(i, 0, &id);
        if (memcmp(&id.DeviceIdentifier, adapter, 16) == 0)
            return i;
    }
    return -1;
}

// @ 0x403a86
void enumerateDisplayModes(const GUID *adapter, DisplayMode **modes, int *count)
{
    IDirect3D9 *d3d = Direct3DCreate9(D3D_SDK_VERSION);
    D3DFORMAT formats[5] = { D3DFMT_X8R8G8B8, D3DFMT_A8R8G8B8, D3DFMT_X8R8G8B8, D3DFMT_R8G8B8, D3DFMT_R5G6B5 };
    UINT adapterIndex = adapter ? (UINT)findAdapter(adapter, d3d) : 0;

    int modeCount = 0;
    unsigned f = 0;
    for (;;) {
        modeCount = d3d->GetAdapterModeCount(adapterIndex, formats[f]);
        if (modeCount != 0 || f + 1 >= 5)
            break;
        ++f;
    }

    g_displayModes = (DisplayMode *)realloc(g_displayModes, modeCount * sizeof(DisplayMode));
    int added = 0;
    int prevWidth = 0;
    int prevHeight = 0;
    for (int i = 0; i < modeCount; ++i) {
        D3DDISPLAYMODE mode;
        d3d->EnumAdapterModes(adapterIndex, formats[f], i, &mode);
        // Quirk of the original: R8G8B8 modes get 24 bpp but are then
        // rejected, A8R8G8B8 modes are kept with 0 bpp.
        int bpp = 0;
        bool keep = false;
        if (mode.Format == D3DFMT_R8G8B8) {
            bpp = 24;
        } else if (mode.Format == D3DFMT_X8R8G8B8) {
            bpp = 32;
            keep = true;
        } else if (mode.Format == D3DFMT_A8R8G8B8) {
            keep = true;
        }
        if (keep && ((int)mode.Width != prevWidth || (int)mode.Height != prevHeight)) {
            DisplayMode &m = g_displayModes[added++];
            m.bitsPerPixel = bpp;
            m.width = mode.Width;
            m.height = mode.Height;
            m.refreshRate = mode.RefreshRate;
            prevWidth = mode.Width;
            prevHeight = mode.Height;
        }
    }
    *modes = g_displayModes;
    *count = added;
    d3d->Release();
}

// @ 0x403bb8
HWND createMainWindow(HINSTANCE instance)
{
    if (g_windowed != 0) {
        return CreateWindowExA(0, "archee", "Sumotori", WS_OVERLAPPEDWINDOW, 0, 0,
                               g_windowWidth, g_windowHeight, GetDesktopWindow(), nullptr,
                               instance, nullptr);
    }
    HWND hwnd = CreateWindowExA(0, "archee", "Sumotori",
                                WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_MAXIMIZE,
                                0, 0, 2000, 2000, GetDesktopWindow(), nullptr, instance, nullptr);
    g_windowWidth = g_screenWidth;
    g_windowHeight = g_screenHeight;
    return hwnd;
}

// @ 0x403c36
void initDirect3D()
{
    g_d3d = Direct3DCreate9(D3D_SDK_VERSION);
    HWND desktop = GetDesktopWindow();
    HDC dc = GetWindowDC(desktop);
    if (g_screenHeight * g_screenWidth == 0) {
        g_screenWidth = GetDeviceCaps(dc, HORZRES);
        g_screenHeight = GetDeviceCaps(dc, VERTRES);
    }
    g_aspect = (float)((double)g_screenWidth / g_screenHeight);
    ReleaseDC(desktop, dc);

    D3DPRESENT_PARAMETERS pp;
    pp.BackBufferWidth = g_screenWidth;
    pp.BackBufferHeight = g_screenHeight;
    pp.BackBufferFormat = D3DFMT_A8R8G8B8;
    pp.BackBufferCount = 1;
    pp.MultiSampleType = D3DMULTISAMPLE_NONE;
    pp.MultiSampleQuality = 0;
    pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    pp.hDeviceWindow = g_mainWindow;
    pp.Windowed = FALSE;
    pp.EnableAutoDepthStencil = TRUE;
    pp.AutoDepthStencilFormat = D3DFMT_D24S8;
    pp.Flags = 0;
    pp.FullScreen_RefreshRateInHz = 0;
    pp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    g_device = nullptr;

    bool tryWindowed = g_windowed != 0;
    if (!tryWindowed) {
        g_d3d->CreateDevice(0, D3DDEVTYPE_HAL, g_mainWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, &pp, &g_device);
        if (g_device == nullptr)
            g_d3d->CreateDevice(0, D3DDEVTYPE_HAL, g_mainWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pp, &g_device);
        tryWindowed = g_device == nullptr;
    }
    if (tryWindowed) {
        ShowWindow(g_mainWindow, SW_SHOWNORMAL);
        g_aspect = 1.3333f;
        D3DDISPLAYMODE mode;
        pp.PresentationInterval = 0;
        pp.FullScreen_RefreshRateInHz = 0;
        pp.Windowed = TRUE;
        g_d3d->GetAdapterDisplayMode(0, &mode);
        pp.BackBufferFormat = mode.Format;
        if (g_device == nullptr) {
            g_d3d->CreateDevice(0, D3DDEVTYPE_HAL, g_mainWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, &pp, &g_device);
            if (g_device == nullptr)
                g_d3d->CreateDevice(0, D3DDEVTYPE_HAL, g_mainWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pp, &g_device);
        }
    }

    g_device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &g_backBuffer);
    D3DVIEWPORT9 vp;
    vp.X = 0;
    vp.Y = 0;
    vp.Width = g_screenWidth;
    vp.Height = g_screenHeight;
    vp.MinZ = 0.0f;
    vp.MaxZ = 1.0f;
    g_device->SetViewport(&vp);
    g_device->GetDeviceCaps(&g_caps);
}

// @ 0x403e16
// Draws text with GDI and darkens the destination pixels by the glyph
// coverage.  The GDI objects are never released (as in the original).
int renderTextToBitmap(unsigned *pixels, const char *text, int x, int y, int pitch,
                       int width, int height, int pointSize, unsigned color,
                       unsigned background, const char *font)
{
    BITMAPINFO bmi;
    memset(&bmi, 0, sizeof(bmi.bmiHeader));
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height;
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biBitCount = 32;
    HDC dc = CreateCompatibleDC(nullptr);
    unsigned char *glyphs;
    HBITMAP bitmap = CreateDIBSection(dc, &bmi, DIB_RGB_COLORS, (void **)&glyphs, nullptr, 0);
    SetMapMode(dc, MM_TEXT);
    int fontHeight = MulDiv(pointSize, GetDeviceCaps(dc, LOGPIXELSY), 72);
    HFONT hfont = CreateFontA(fontHeight, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                              ANTIALIASED_QUALITY, VARIABLE_PITCH, font);
    if (hfont != nullptr) {
        SelectObject(dc, bitmap);
        SelectObject(dc, hfont);
        SetTextColor(dc, color ^ 0xffffff);
        SetBkColor(dc, background ^ 0xffffff);
        SetTextAlign(dc, TA_LEFT | TA_TOP);
        ExtTextOutA(dc, 0, 0, ETO_OPAQUE, nullptr, text, (UINT)strlen(text), nullptr);
        unsigned char *dst = (unsigned char *)(pixels + (y * pitch + x));
        for (int row = height; row != 0; --row) {
            for (int col = width; col != 0; --col) {
                dst[0] = (unsigned char)(((0xff - (unsigned)glyphs[0]) * dst[0]) >> 8);
                dst[1] = (unsigned char)(((0xff - (unsigned)glyphs[1]) * dst[1]) >> 8);
                unsigned char b = (unsigned char)(((0xff - (unsigned)glyphs[2]) * dst[2]) >> 8);
                dst[2] = b;
                dst[3] = (unsigned char)(((0xff - (unsigned)glyphs[2]) * b) >> 8);
                glyphs += 4;
                dst += 4;
            }
            dst += (pitch - width) * 4;
        }
    }
    return 0;
}

// @ 0x415a5c
IDirect3DTexture9 *createTexture(const void *pixels, int width, int height, int levels)
{
    IDirect3DTexture9 *texture;
    g_device->CreateTexture(width, height, levels, (levels ^ 1) << 10, D3DFMT_A8R8G8B8,
                            D3DPOOL_MANAGED, &texture, nullptr);
    D3DLOCKED_RECT lr;
    texture->LockRect(0, &lr, nullptr, 0);
    const unsigned char *src = (const unsigned char *)pixels;
    unsigned char *dst = (unsigned char *)lr.pBits;
    for (int row = height; row > 0; --row) {
        memcpy(dst, src, width * 4);
        dst += lr.Pitch;
        src += width * 4;
    }
    texture->UnlockRect(0);
    return texture;
}

// @ 0x415ae1  Builds a tangent space normal map from the blue channel.
IDirect3DTexture9 *createNormalMap(const unsigned char *pixels, int width, int height, int depth)
{
    unsigned char *out = (unsigned char *)malloc(width * height * 4);
    unsigned char *o = out;
    const unsigned char *row = pixels;
    const unsigned char *up = pixels + (height - 1) * width * 4;
    int depthSq = depth * depth;
    int sign = depth < 0 ? -2 : 2;
    for (int y = height; y > 0; --y) {
        const unsigned char *left = row + width * 4 - 4;
        const unsigned char *cur = row;
        const unsigned char *above = up;
        for (int x = width; x > 0; --x) {
            int dx = (int)cur[0] - (int)left[0];
            int dy = (int)cur[0] - (int)above[0];
            int sq = dy * dy + depthSq + dx * dx;
            int len = fp::ftol(fp::sqrt((double)sq) * (float)sign);
            o[0] = (unsigned char)((dx << 8) / len + 0x7f);
            o[1] = (unsigned char)((dy << 8) / len + 0x7f);
            o[2] = (unsigned char)((depth << 8) / len + 0x7f);
            o[3] = 0;
            o += 4;
            left = cur;
            cur += 4;
            above += 4;
        }
        up = row;
        row += width * 4;
    }
    IDirect3DTexture9 *texture = createTexture(out, width, height, 0);
    free(out);
    return texture;
}

// @ 0x415c17
void setTexture(int stage, IDirect3DTexture9 *texture)
{
    g_device->SetTexture(stage, texture);
}

static const char *g_screenshotPrefix = "shot";   // @ 0x453864
static int g_screenshotIndex;                     // @ 0xc0a4e8

// @ 0x414f2b
void saveScreenshot()
{
    char path[260];
    FILE *f;
    do {
        sprintf(path, "%s%d.bmp", g_screenshotPrefix, g_screenshotIndex);
        f = fopen(path, "rb");
        if (f != nullptr)
            fclose(f);
        ++g_screenshotIndex;
    } while (f != nullptr);

    IDirect3DSurface9 *surface = nullptr;
    if (SUCCEEDED(g_device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &surface))) {
        unsigned char *image = (unsigned char *)malloc(g_screenHeight * g_screenWidth * 4);
        D3DLOCKED_RECT lr;
        surface->LockRect(&lr, nullptr, 0);
        unsigned char *copy = (unsigned char *)malloc((g_screenHeight * lr.Pitch) / 4 * 4);
        memcpy(copy, lr.pBits, g_screenHeight * lr.Pitch);
        surface->UnlockRect();
        int height = g_screenHeight;
        int width = g_screenWidth;
        for (int i = 0, src = height - 1; i < height; ++i, --src)
            memcpy(image + g_screenWidth * i * 4, copy + (src * lr.Pitch) / 4 * 4, g_screenWidth * 4);

        unsigned char header[0x36] = {
            'B', 'M', 0x36, 0x30, 0, 0, 0, 0, 0, 0, 0x36, 0, 0, 0, 0x28, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0x20, 0, 0, 0, 0, 0, 0, 0x1e,
            0, 0, 0xc6, 0x11, 0, 0, 0xc6, 0x11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        };
        *(unsigned short *)&header[18] = (unsigned short)width;
        *(unsigned short *)&header[22] = (unsigned short)height;
        f = fopen(path, "wb");
        fwrite(header, 1, 0x36, f);
        fwrite(image, 1, height * width * 4, f);
        fclose(f);
        free(copy);
        free(image);
    }
    if (surface != nullptr)
        surface->Release();
}

// @ 0x4151c2
void saveScreenshotAs(const char *prefix, int startIndex)
{
    g_screenshotIndex = startIndex;
    g_screenshotPrefix = prefix;
    saveScreenshot();
}
