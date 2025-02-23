#pragma once

#include <raylib.h>
//#include <raymath.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "GameObject.h"

// Defined in "Speed.c"
extern gaming* mainGame;
// Global frame counter, for animation timing
// Goes from 0-59 each second (increments each frame)
extern int frameCount;

// Allocates memory for GameObject, assigns "mainGame" pointer, and calls raylib init
// Caller func in Game.c must then set the struct's func. ptrs
int CreateGameInstance(int w, int h);

// Call raylib's init functions to set up the game window
int InitGUI(const char* title);

// Calls function pointers from mainGame to:
//      - handle input (keyboard, mouse, window events)
//      - update game state and objects
//      - draw screen
int GameLoop();

// Does nothing, just reduces raylib startup spam
void CustomLog(int msgType, const char *text, va_list args);