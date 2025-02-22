#include "Engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct st{
    double cap;
    double size;
    void** mem;
    void (*remove) (void*);
    double instSize;
} stack;

void push(void* inst, stack* stack) {
    if (stack->size+1 > stack->cap) {
        *(stack->mem) = realloc(*(stack->mem), stack->cap*2)
        stack->cap = stack->cap*2;
    }
    stack->mem[instSize*size]
    stack->size += 1;
}

void* pop(stack* stack) {
    stack->size -= 1;
    void* inst = stack->instSize*stack->size
    stack->remove(stack->mem+(stack->instSize*stack->size))
    free(stack->instSize*stack->size)
    return inst;
}

int main(char** args) {
    
}