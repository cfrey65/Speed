#pragma once

typedef struct gaming {
    void* game; //self explanatory
    size_t envSize; //do not touch (maybe)
    void (*updateEnviroment) (void* game, char c); //game is the game state
    //and char is for the input action
    void* (*getEnv) (void* game); //check if things need to be updated
    void* (*pause) (void* game); //checks for pause state
    void (*deleteEnv) (void* env); //frees enviroment
} g;

global g* mainGame;