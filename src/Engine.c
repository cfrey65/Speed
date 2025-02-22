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

/* int main(int argc, char** args) {
    if (argc == 2)
    {
        char* cmd = malloc(4 + strlen(args[1]) + 9);
        if (!cmd) {
            printf("Could not allocate memory!");
            return 1;
        }
        memcpy(cmd, "gcc ", 4);
        memcpy(cmd+4, args[1], strlen(args[1]));
        memcpy(cmd+4+strlen(args[1]), " -o game", 8);
        cmd[4+strlen(args[1])+9] = '\0';
        if (system(cmd) != 0) {
            printf("Game file compilation error!");
            return 1;
        }
        free(cmd);
        cmd = NULL;
        system("game.exe");
        stack st = {.cap = mainGame->envSize*50, .size = 0, .remove = mainGame->deleteEnv, 
            .instSize = mainGame->envSize};
        /*void* start = mainGame->getEnv(); //Fix Later
        push(&st, start);
        while (st.size > 0) {
            char c;
            c = getchar();
            for (int i = 0; i < mainGame->numInt; i++) {
                if (c == mainGame->interrupts[i]) {
                    mainGame->updateEnv(c);
                }
            }
        }
    }
    return 0;   
}*/