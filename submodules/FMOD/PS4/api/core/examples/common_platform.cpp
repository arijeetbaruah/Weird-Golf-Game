/*==============================================================================
FMOD Example Framework
Copyright (c), Firelight Technologies Pty, Ltd 2012-2020.
==============================================================================*/
#include "common.h"
#include "toolkit/toolkit.h"
#include "toolkit/stack_allocator.h"
#include "dbg_font/dbg_font.h"
#include <kernel.h>
#include <video_out.h>
#include <pad.h>
#include <vector>
#include <perf.h>
#include <gnm.h>

using namespace sce;
using namespace sce::Gnmx;

unsigned int sceLibcHeapExtendedAlloc = 1;
size_t sceLibcHeapSize = SCE_LIBC_HEAP_SIZE_EXTENDED_ALLOC_NO_LIMIT;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int LOG2_CHAR_WIDTH = 4;
const int LOG2_CHAR_HEIGHT = 4;

Gnmx::GfxContext gGFXContext;
Gnm::RenderTarget gRenderTargets[2];
int gBackBufferIndex;
int32_t gVideoOutHandle;
int32_t gVideoOutFlipIndex;
SceKernelEqueue gVideoOutEqueue;
Toolkit::StackAllocator gGarlicAllocator;
Toolkit::StackAllocator gOnionAllocator;
DbgFont::Screen gFontScreen;
DbgFont::Window gFontWindow;
uint32_t gPressedButtons;
uint32_t gDownButtons;
std::vector<char *> gStringList;
int gPadHandle;
SceKernelModule fmodModuleId;
SceKernelModule fmodStudioModuleId;

bool Common_Private_Test;
int Common_Private_Argc;
char** Common_Private_Argv;
void (*Common_Private_Update)(unsigned int*);
void (*Common_Private_Print)(const char*);
void (*Common_Private_Close)();

int main(int argc, char** argv)
{
    Common_Private_Argc = argc;
    Common_Private_Argv = argv;
    return FMOD_Main();
}

void Common_Init(void **extraDriverData)
{
    int err = 0;

    /*
        Load FMOD PRX
    */
    {
        fmodModuleId = sceKernelLoadStartModule(FMOD_LIB_PATH, 0, 0, 0, NULL, NULL);
        assert (fmodModuleId >= SCE_OK);
    }

    #if defined(FMOD_STUDIO_LIB_PATH)
    {
        fmodStudioModuleId = sceKernelLoadStartModule(FMOD_STUDIO_LIB_PATH, 0, 0, 0, NULL, NULL);
        assert (fmodStudioModuleId >= SCE_OK);
    }
    #endif

    /*
        Init controller input
    */
    {
        err = sceUserServiceInitialize(NULL);
        assert(err == 0);

        SceUserServiceUserId userID;
        err = sceUserServiceGetInitialUser(&userID);
        assert(err == 0);

        err = scePadInit();
        assert(err == 0);

        gPadHandle = scePadOpen(userID, SCE_PAD_PORT_TYPE_STANDARD, 0, NULL);
        assert(err >= 0);
    }

    /*
        Initialize rendering
    */
    {
        gOnionAllocator.init(SCE_KERNEL_WB_ONION, 1024 * 1024 * 256);
        gGarlicAllocator.init(SCE_KERNEL_WC_GARLIC, 1024 * 1024 * 512);

        Gnmx::Toolkit::Allocators toolkitMemoryAllocator;
        toolkitMemoryAllocator.m_onion = GetInterface(&gOnionAllocator);
        toolkitMemoryAllocator.m_garlic = GetInterface(&gGarlicAllocator);
        Gnmx::Toolkit::initializeWithAllocators(&toolkitMemoryAllocator);

        Gnmx::Toolkit::Allocators debugFontMemoryAllocators;
        debugFontMemoryAllocators.m_onion = GetInterface(&gOnionAllocator);
        debugFontMemoryAllocators.m_garlic = GetInterface(&gGarlicAllocator);
        DbgFont::initializeWithAllocators(&debugFontMemoryAllocators);

        const int characterWidth = 1 << LOG2_CHAR_WIDTH;
        const int characterHeight = 1 << LOG2_CHAR_HEIGHT;
        const int screenCharactersWide = (SCREEN_WIDTH + characterWidth - 1) / characterWidth;
        const int screenCharactersHigh = (SCREEN_HEIGHT + characterHeight - 1) / characterHeight;

        const Gnm::SizeAlign screenSizeAlign = gFontScreen.calculateRequiredBufferSizeAlign(screenCharactersWide, screenCharactersHigh);
        void *screenPtr = gGarlicAllocator.allocate(screenSizeAlign);
        gFontScreen.initialize(screenPtr, screenCharactersWide, screenCharactersHigh);
        gFontWindow.initialize(&gFontScreen);
        gFontWindow.m_positionXInCharactersRelativeToScreen += 4;
        gFontWindow.m_positionYInCharactersRelativeToScreen += 2;
        gFontWindow.m_widthInCharacters -= 4;
        gFontWindow.m_heightInCharacters -= 2;

        Gnm::RenderTargetSpec renderTargetSpec;
        renderTargetSpec.init();
        renderTargetSpec.m_width = SCREEN_WIDTH;
        renderTargetSpec.m_height = SCREEN_HEIGHT;
        renderTargetSpec.m_numSlices = 1;
        renderTargetSpec.m_colorFormat = Gnm::kDataFormatB8G8R8A8Unorm;
        GpuAddress::computeSurfaceTileMode(Gnm::kGpuModeBase, &renderTargetSpec.m_colorTileModeHint, GpuAddress::kSurfaceTypeColorTargetDisplayable, 
            renderTargetSpec.m_colorFormat, 1);
        renderTargetSpec.m_numSamples = Gnm::kNumSamples1;
        renderTargetSpec.m_numFragments = Gnm::kNumFragments1;

        void* buffer_address[2];

        for (unsigned int i = 0; i < 2; i++)
        {
            err = gRenderTargets[i].init(&renderTargetSpec);
            assert(err == 0);
            const Gnm::SizeAlign sizeAlign = gRenderTargets[i].getColorSizeAlign();
            void *renderTargetPtr = gGarlicAllocator.allocate(sizeAlign);
            buffer_address[i] = renderTargetPtr;
            gRenderTargets[i].setAddresses(renderTargetPtr, 0, 0);
        }

        gBackBufferIndex = 0;

        gVideoOutHandle = sceVideoOutOpen(0, SCE_VIDEO_OUT_BUS_TYPE_MAIN, 0, nullptr);
        sceKernelCreateEqueue(&gVideoOutEqueue, __FUNCTION__);
        sceVideoOutAddFlipEvent(gVideoOutEqueue, gVideoOutHandle, nullptr);

        SceVideoOutBufferAttribute attribute;
        sceVideoOutSetBufferAttribute(&attribute, SCE_VIDEO_OUT_PIXEL_FORMAT_B8_G8_R8_A8_SRGB, SCE_VIDEO_OUT_TILING_MODE_TILE, SCE_VIDEO_OUT_ASPECT_RATIO_16_9, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH);
        sceVideoOutRegisterBuffers(gVideoOutHandle, 0, buffer_address, 2, &attribute );

        const uint32_t kNumRingEntries = 16;
        const uint32_t cueHeapSize = Gnmx::ConstantUpdateEngine::computeHeapSize(kNumRingEntries);

        gGFXContext.init(
            gGarlicAllocator.allocate(cueHeapSize, Gnm::kAlignmentOfBufferInBytes), kNumRingEntries,
            gOnionAllocator.allocate(Gnm::kIndirectBufferMaximumSizeInBytes, Gnm::kAlignmentOfBufferInBytes), Gnm::kIndirectBufferMaximumSizeInBytes,
            gOnionAllocator.allocate(Gnm::kIndirectBufferMaximumSizeInBytes, Gnm::kAlignmentOfBufferInBytes), Gnm::kIndirectBufferMaximumSizeInBytes);
    }
}

void Common_Close()
{
    for (auto item = gStringList.begin(); item != gStringList.end(); ++item)
    {
        free(*item);
    }

    gGarlicAllocator.deinit();
    gOnionAllocator.deinit();

    int err = sceKernelStopUnloadModule(fmodModuleId, 0, 0, 0, 0, 0);
    assert(err == 0);

    #if defined(FMOD_STUDIO_LIB_PATH)
    err = sceKernelStopUnloadModule(fmodStudioModuleId, 0, 0, 0, 0, 0);
    assert(err == 0);
    #endif

    if (Common_Private_Close)
    {
        Common_Private_Close();
    }
}

static unsigned int convertButtonMask(uint32_t btn)
{
    unsigned int mask = 0;
    if (btn & SCE_PAD_BUTTON_CROSS)                     mask |= (1<<BTN_ACTION1);
    if (btn & SCE_PAD_BUTTON_CIRCLE)                    mask |= (1<<BTN_ACTION2);
    if (btn & SCE_PAD_BUTTON_SQUARE)                    mask |= (1<<BTN_ACTION3);
    if (btn & SCE_PAD_BUTTON_TRIANGLE)                  mask |= (1<<BTN_ACTION4);
    if (btn & SCE_PAD_BUTTON_LEFT)                      mask |= (1<<BTN_LEFT);
    if (btn & SCE_PAD_BUTTON_RIGHT)                     mask |= (1<<BTN_RIGHT);
    if (btn & SCE_PAD_BUTTON_UP)                        mask |= (1<<BTN_UP);
    if (btn & SCE_PAD_BUTTON_DOWN)                      mask |= (1<<BTN_DOWN);
    if (btn & SCE_PAD_BUTTON_OPTIONS)                   mask |= (1<<BTN_MORE);
    if (btn & (SCE_PAD_BUTTON_L1|SCE_PAD_BUTTON_R1))    mask |= (1<<BTN_QUIT);
    return mask;
}

void Common_Update()
{
    /*
        Update button presses
    */
    ScePadData data = {0};
    int err = scePadReadState(gPadHandle, &data);
    assert(err == 0);

    unsigned int newButtons = convertButtonMask(data.buttons);
    gPressedButtons = newButtons & ~gDownButtons;
    gDownButtons = newButtons;

    /*
        Render display
    */
    gGFXContext.reset();

    Gnm::RenderTarget *backBuffer = gRenderTargets + gBackBufferIndex;
    Toolkit::SurfaceUtil::clearRenderTarget(gGFXContext, backBuffer, Vector4::zero());
    gFontScreen.render(gGFXContext, backBuffer, LOG2_CHAR_WIDTH, LOG2_CHAR_HEIGHT);

    gGFXContext.submit();
    sceVideoOutSubmitFlip(gVideoOutHandle, gVideoOutFlipIndex, SCE_VIDEO_OUT_FLIP_MODE_VSYNC, 0);
    gVideoOutFlipIndex = (gVideoOutFlipIndex + 1) % 2;

    int out;
    SceKernelEvent ev;
    sceKernelWaitEqueue(gVideoOutEqueue, &ev, 1, &out, 0);

    gBackBufferIndex = 1 - gBackBufferIndex;

    DbgFont::Cell cell;
    cell.m_character = 0;
    cell.m_backgroundColor = DbgFont::kBlack;
    cell.m_backgroundAlpha = 3;
    cell.m_foregroundColor = DbgFont::kWhite;
    cell.m_foregroundAlpha = 15;
    gFontWindow.clear(cell);
    gFontWindow.setCursor(0, 0);

    if (Common_Private_Update)
    {
        Common_Private_Update(&gPressedButtons);
    }

    err = sceRazorCpuSync();
    assert(err == 0);

    sce::Gnm::submitDone();
}

void Common_Sleep(unsigned int ms)
{
    sceKernelUsleep(ms * 1000);
}

void Common_Exit(int returnCode)
{
    exit(returnCode);
}

void Common_DrawText(const char *text)
{
    gFontWindow.putString(text);
    gFontWindow.newLine();
}

void Common_LoadFileMemory(const char *name, void **buff, int *length)
{
    FILE *file = NULL;
    fopen_s(&file, name, "rb");
    fseek(file, 0, SEEK_END);

    long len = ftell(file);
    fseek(file, 0, SEEK_SET);

    void *mem = malloc(len);
    fread(mem, 1, len, file);
    fclose(file);

    *buff = mem;
    *length = len;
}

void Common_UnloadFileMemory(void *buff)
{
    free(buff);
}


bool Common_BtnPress(Common_Button btn)
{
    return ((gPressedButtons & (1 << btn)) != 0);
}

bool Common_BtnDown(Common_Button btn)
{
    return ((gDownButtons & (1 << btn)) != 0);
}

const char *Common_BtnStr(Common_Button btn)
{
    switch (btn)
    {
        case BTN_ACTION1:   return "CROSS";
        case BTN_ACTION2:   return "CIRCLE";
        case BTN_ACTION3:   return "SQUARE";
        case BTN_ACTION4:   return "TRIANGLE";
        case BTN_LEFT:      return "LEFT";
        case BTN_RIGHT:     return "RIGHT";
        case BTN_UP:        return "UP";
        case BTN_DOWN:      return "DOWN";
        case BTN_MORE:      return "START";
        case BTN_QUIT:      return "BOTH SHOULDERS";
        default:            return "Unknown";
    }
}

const char *Common_MediaPath(const char *fileName)
{
    char *filePath = (char *)calloc(256, sizeof(char));

    strcat(filePath, "/app0/media/");
    strcat(filePath, fileName);
    gStringList.push_back(filePath);

    return filePath;
}

const char *Common_WritePath(const char *fileName)
{
    return Common_MediaPath(fileName);
}

void Common_TTY(const char *format, ...)
{
    char string[1024] = {0};

    va_list args;
    va_start(args, format);
    Common_vsnprintf(string, 1023, format, args);
    va_end(args);

    if (Common_Private_Print)
    {
        (*Common_Private_Print)(string);
    }
    else
    {
        fprintf(stderr, "%s", string);
    }
}