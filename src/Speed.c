#include "Speed.h"

g* mainGame = NULL;

int CreateGame(int w, int h, const char* title) {
    mainGame = malloc(sizeof(gaming));
    if (mainGame == NULL) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int InitGUI