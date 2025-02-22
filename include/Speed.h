#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "GameObject.h"

// Defined in "Speed.c"
extern g* mainGame;


// Allocates memory for GameObject, assigns "mainGame" pointer, and calls raylib init
// Caller func in Game.c must then set the struct's func. ptrs
int CreateGame(int w, int h, const char* title);

int InitGUI(int w, int h, const char* title);