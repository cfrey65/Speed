#ifndef __RPP_H__
#define __RPP_H__

#include <raylib.h>
#include <stdbool.h>

typedef enum ScreenPhase {UNKNOWN = -1, MAIN = 0} ScreenPhase;

// Frame counter variable for animation
extern int frameCount;

// Error message buffer
extern char PRG_MSG[128];

//? Main GUI management entry point
// Returns 0 if successful (at window close)
// Returns 1 if GUI init error
// Returns an int > 1 if other error
int GUI_MGR(int w, int h, int x, int y, const char *title);

//? GUI management functions
int GUI_Init(bool debugText, KeyboardKey escKey, Vector2 windowDims, Vector2 windowPos, const char *windowTitle);
int GUI_Main(); // Main program loop //TODO: add option for external function pointer to inject
void GUI_DeInit(); // Wraps everything up quite nicely
void RPP_CALLBACK(int msgType); // Prints custom error message at program exit

//? Raylib-specific interaction functions
void CustomLog(int msgType, const char *text, va_list args); // Optionally blocks raylib init text from going to console
void ChangeToScreen(ScreenPhase screen);
void UpdateDrawFrame(); // Called once per frame

void InitMainScreen();
void UpdateMainScreen();
void DrawMainScreen();
int FinishMainScreen();
void UnloadMainScreen();

#endif