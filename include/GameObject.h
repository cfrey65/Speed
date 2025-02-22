#pragma once

#include "Engine.h"

typedef struct gaming {
    int width, height;
    char gameState;

    size_t envSize; //do not touch (maybe)

    void (*drawGame) (); // Main draw function, called once per frame
    void (*updateGame) (); // Called once per frame
    void (*inputHandle) (); // Called once per frame

    void (*pauseGame) ();
    void (*resumeGame) ();
    
    void (*deleteEnv) (void* env); //frees enviroment
    void 
} g;