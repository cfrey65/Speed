#include "GameFrameWork.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

extern g* mainGame;

typedef struct st{
    size_t cap;
    size_t size;
    void* mem;
    void (*remove) (void*);
    size_t instSize;
} stack;

void push(stack* stack, void* inst) {
    if (stack->size+1 > stack->cap) {
        stack->mem = realloc(stack->mem, stack->cap*2);
        stack->cap = stack->cap*2;
    }
    *((char*)stack->mem + stack->instSize*stack->size) = *((char*)(inst));
    stack->size += 1;
}

void* pop(stack* stack) {
    stack->size -= 1;
    void* inst = (char*)stack->mem + stack->instSize*stack->size;
    stack->remove((char*)stack->mem+(stack->instSize*stack->size));
    free((char*)stack->mem + stack->instSize*stack->size);
    return inst;
}

int main(int argc, char** args) {
    if (argc == 2) {
        char* cmd = malloc(9 + strlen(args[1]) + 29);
        if (!cmd) {
            printf("Could not allocate memory!");
            return 1;
        }
        memcpy(cmd, "gcc game\\", 9);
        memcpy(cmd+4, args[1], strlen(args[1]));
        memcpy(cmd+4+strlen(args[1]), "-I\'C:\raylib\\lib\\src\' -o game", 28);
        cmd[9+strlen(args[1])+29] = '\0';
        if (system(cmd) != 0) {
            printf("Game file compilation error!");
            return 1;
        }
        free(cmd);
        cmd = NULL;
        system("game.exe");
        stack st = {.cap = mainGame->envSize*50, .size = 0, .remove = mainGame->deleteGameEnv, 
            .instSize = mainGame->envSize};
        InitWindow(mainGame->width, mainGame->length, "Purdoom");
        mainGame->loadGame;
        while (!WindowShouldClose()) {
            mainGame->updateGame;
        }
    } 
    return 0;   
}