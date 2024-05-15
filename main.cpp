#include <proc_ui/procui.h>
#include <coreinit/foreground.h>
#include <coreinit/screen.h>
#include <stdlib.h>

int main() {
    // Initialize ProcUI (process status management library)
    ProcUIInit(OSSavesDone_ReadyToRelease);
    // Intiialize OSScreen
    OSScreenInit();

    // Allocate data for screen
    void* buffer = aligned_alloc(0x100, OSScreenGetBufferSizeEx(SCREEN_DRC));
    OSScreenSetBufferEx(SCREEN_DRC, buffer);
    // Enable screen
    OSScreenEnableEx(SCREEN_DRC, TRUE);
    // Clear screen
    OSScreenClearBufferEx(SCREEN_DRC, 0);

    // Write text to screen
    OSScreenPutFontEx(SCREEN_DRC, 40, 30, "Hello World");


    /// Draw some dots on screen
    // Red dot
    OSScreenPutPixelEx(SCREEN_DRC, 200, 400, 0xFF000000);
    // White dot
    OSScreenPutPixelEx(SCREEN_DRC, 200, 401, 0xFFFFFF00);

    // Show on screen
    OSScreenFlipBuffersEx(SCREEN_DRC);

    ProcUIStatus procStatus;
    while (true)
    {
        procStatus = ProcUIProcessMessages(TRUE);
        // OS asked application to exit
        if (procStatus == PROCUI_STATUS_EXITING)
            break;
        // OS asked application to release foreground resources
        else if (procStatus == PROCUI_STATUS_RELEASE_FOREGROUND)
        {
            ProcUIDrawDoneRelease();
            continue;
        }
    }

    // De-initialize OSScreen
    OSScreenShutdown();
    
    // Free the buffer
    free(buffer);
    
    // De-initialize ProcUI
    ProcUIShutdown();
    return 0;
}
