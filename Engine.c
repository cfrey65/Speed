#include "Engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct st{
    int cap;
    int size;
    void* mem;
    void (*remove) (void*);
    int instSize;
} stack;

void push(void* inst, stack* stack) {
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
    stack->remove(stack->mem+(stack->instSize*stack->size));
    free((char*)stack->mem + stack->instSize*stack->size);
    return inst;
}

int main(int argc, char** args) {
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
    return 0;
}