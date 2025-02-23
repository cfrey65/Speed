#pragma once

typedef struct _gaming{
    int width, height;
    char gameState;
    void* game;
    Camera3D cam;

    size_t envSize; //do not touch (maybe)

    void (*drawGame) (); // Main draw function, called once per frame
    void (*updateGame) (); // Called once per frame
    void (*inputHandle) (); // Called once per frame

    void (*pauseGame) ();
    void (*resumeGame) ();
    
    void (*deleteEnv) (void* env); //frees enviroment
} gaming;