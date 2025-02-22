#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <raylib.h>

#include "rpp.h"

// Internal message buffer
char PRG_MSG[128];

ScreenPhase currScreen = MAIN;
int finishMainScreen = 0;
int frameCount = 0;

//! Global GUI Vars
int scrnWidth = 0;
int scrnHeight = 0;
int scrnScale = 0;
int currMonitor = 0;

int appWidth = 0;
int appHeight = 0;
int appPosX = 0;
int appPosY = 0;

//! Fonts
Font font1 = { 0 };
Font font2 = { 0 };
Font font3 = { 0 };

//! BG Colors
Color BG_COLOR1 = { 0, 0, 0, 0 };
Color BG_COLOR2 = { 255, 255, 255, 255 };
Color BG_COLOR3 = { 100, 100, 100, 200 };

//! Additional colors
Color DOSBLUE = {.r = 0, .g = 0, .b = 170, .a = 200 };
Color BTNGRAY = {.r = 174, .g = 174, .b = 170, .a = 200 };
Color BTNGRAY_LIGHT = {.r = 187, .g = 187, .b = 187, .a = 200 };
Color BTNGRAY_DARK = {.r = 87, .g = 87, .b = 87, .a = 200 };
Color BIOSTEAL_TWEAK = { .r = 0, .g = 80, .b = 120, .a = 200};

Color GH_BLACK = { .r=1, .g=4, .b=9, .a=200 };
Color GH_GRAY = { .r=13, .g=17, .b=23, .a=200 };
Color GH_BLUE_VDARK = {5, 21, 47, 200};
Color GH_BLUE_DARK = {9, 38, 85, 200};
Color GH_BLUE_MID = {13, 55, 123, 200};
Color GH_BLUE_LIGHT = {17, 72, 161, 200};
Color GH_BLUE_BRIGHT = {21, 89, 199, 200};

void InitMainScreen() {
    finishMainScreen = 0;
}

void UpdateMainScreen() {

}

void DrawMainScreen() {
    ClearBackground(BIOSTEAL_TWEAK);
}

void UpdateDrawFrame() {
    //? Update current screen
    switch (currScreen) {
        case MAIN: 
            UpdateMainScreen();
            //if (FinishMainScreen() == 1) {
            //    ChangeToScreen([next screen]);
            //}
        default: break;
    }

    //? Draw current screen  
    BeginDrawing();
        switch (currScreen) {
            case MAIN: DrawMainScreen();
            default:
                break;
        }
    EndDrawing();
}

void ChangeToScreen(ScreenPhase screen) {
    // Unload current screen
    //switch (currScreen) {
    //    case MAIN: break;
    //    default: break;
    //}
    // Init next screen
    //switch (screen) {
    //    case MAIN: InitMainScreen(); break;
    //    default: break;
    //}
    //
    //currentScreen = screen;
}

int FinishMainScreen() {
    return finishMainScreen;
}

void UnloadMainScreen() {
    return;
}

void GUI_DeInit() {
    //? Unload per-screen data
    switch(currScreen) {
        case MAIN: UnloadMainScreen(); break;
        default: break;
    }

    //? Unload fonts
    UnloadFont(font1);
    UnloadFont(font2);
    UnloadFont(font3);
}

int GUI_Init(bool debugText, KeyboardKey escKey, Vector2 windowDims, Vector2 windowPos, const char *windowTitle) {
    if (!debugText) {
        // Sets raylib logger function to output nothing, reduces console spam
        // Comment this line out when there are raylib errors to see the causes
        SetTraceLogCallback(CustomLog);
    }

    //? Load fonts
    font1 = LoadFontEx("resource/font/MxPlus_IBM_VGA_8x16.tff", 16, 0, 437);
    font2 = LoadFontEx("resource/font/Px437_SperryPC_8x16.tff", 16, 0, 437);
    font3 = LoadFontEx("resource/font/PxPlus_ToshibaSat_8x14.tff", 14, 0, 437);

    //? Call raylib init functions
    InitWindow(1, 1, windowTitle);
    SetTargetFPS(60);

    //? Get monitor ID and dimensions
    currMonitor = GetCurrentMonitor();
    scrnWidth = GetMonitorWidth(currMonitor);
    scrnHeight = GetMonitorHeight(currMonitor);

    //? Validate dimensions and location; set to defaults if invalid
    appWidth = (windowDims.x < 0) ? 800 : windowDims.x;
    appHeight = (windowDims.y < 0) ? 600 : windowDims.y;
    appPosX = (windowPos.x < 0) ? ((scrnWidth - 800) / 2) : windowPos.x;
    appPosY = (windowPos.y < 0) ? ((scrnHeight - 600) / 2) : windowPos.y;

    //? Set window to requested size after input validation
    SetWindowSize(appWidth, appHeight);
    SetWindowPosition(appPosX, appPosY);

    //? Set or disable app exit key, depending on "escKey"
    //? Set to KEY_NULL to disable exiting via key; can only escape via corner (x) button
    SetExitKey(escKey);

    //! Screen info
    //! NOTE: GetWindowScaleDPI.x/.y represents scale of your monitor from the base
    //!       DPI setting from Windows of 96 DPI where 1pt = 0.75px
    //! Work laptop: 120 DPI therefore 1pt = 0.6px

    return EXIT_SUCCESS;
}

int GUI_Main() {
    int RUN_CODE = 0;

    //? Main program loop; calls UpdateDrawFrame 60 times/sec
    while (!WindowShouldClose()) {
        UpdateDrawFrame();
        if (frameCount < 60) {
            frameCount++;
        }
        else {
            frameCount = 0;
        }
    }

    return RUN_CODE;
}