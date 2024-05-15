#include <coreinit/foreground.h>
#include <coreinit/screen.h>
#include <stdlib.h>
#include <whb/proc.h>

int main() {
    // Initialize WHBProc
    WHBProcInit();
    
    // Intiialize OSScreen
    OSScreenInit();

    // Allocate data for screen
    void* buffer = aligned_alloc(0x100, OSScreenGetBufferSizeEx(SCREEN_DRC));
    OSScreenSetBufferEx(SCREEN_DRC, buffer);
    
    // Enable screen
    OSScreenEnableEx(SCREEN_DRC, TRUE);
    
    // Clear screen to a medium green color
    OSScreenClearBufferEx(SCREEN_DRC, 0x007F0000);

    // Write text to screen
    OSScreenPutFontEx(SCREEN_DRC, 4, 3, "Hello World");

    /// Draw some pixels on screen
    // Red pixel
    OSScreenPutPixelEx(SCREEN_DRC, 200, 400, 0xFF000000);
    // White pixel
    OSScreenPutPixelEx(SCREEN_DRC, 300, 301, 0xFFFFFF00);

    // Show on screen
    OSScreenFlipBuffersEx(SCREEN_DRC);

    // Wait for OS to request application shutdown
    while (WHBProcIsRunning()) { }
    
    // Free the buffer
    free(buffer);

    // De-initialize WHBProc
    WHBProcShutdown();
    return 0;
}
