#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "GameObject.h"

// Defined in "Speed.c"
extern g* mainGame;
// Global frame counter, for animation timing
// Goes from 0-59 each second (increments each frame)
extern int frameCount;

// Allocates memory for GameObject, assigns "mainGame" pointer, and calls raylib init
// Caller func in Game.c must then set the struct's func. ptrs
int CreateGameInstance(int w, int h, const char* title);

// Call raylib's init functions to set up the game window
int InitGUI(const char* title);

// Calls function pointers from mainGame to:
//      - handle input (keyboard, mouse, window events)
//      - update game state and objects
//      - draw screen
int GameLoop();
