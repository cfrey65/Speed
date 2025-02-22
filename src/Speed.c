#include "Speed.h"

gaming* mainGame = NULL;
int frameCount = 0;

int CreateGameInstance(int w, int h) {
    mainGame = malloc(sizeof(gaming));
    if (mainGame == NULL) {
        printf("*** ERROR: could not allocate memory for mainGame object. Exiting... ***\n");
        return EXIT_FAILURE;
    }

    // Validate requested game dimensions
    if (w < 1 || h < 1) {
        printf("*** ERROR: invalid window dimensions (%d x %d). Exiting...\n", w, h);
        return EXIT_FAILURE;
    }

    // Set mainGame fields for window width+height
    mainGame->width = w;
    mainGame->height = h;

    return EXIT_SUCCESS;
}

int InitGUI(const char* title) {
    // Sets raylib logger function to output nothing, reduces console spam
    // Comment this line out when there are raylib errors to see the causes
    SetTraceLogCallback(CustomLog);

    // Call raylib init function
    InitWindow(mainGame->width, mainGame->height, title);

    

    // Aim to update+draw 60 times per second
    SetTargetFPS(60);
    // Disable exiting with escape key (so you can make a pause menu)
    // Change "KEY_NULL" --> "KEY_ESC" if you want to close app using the escape key
    SetExitKey(KEY_NULL);

    return EXIT_SUCCESS;
}

int GameLoop() {
    while (!WindowShouldClose()) {
        // 1. HANDLE INPUT
        mainGame->inputHandle();
        // 2. UPDATE GAME/OBJECTS
        mainGame->updateGame();
        // 3. DRAW THE SCREEN
        BeginDrawing();
            mainGame->drawGame();
        EndDrawing();

        if (frameCount < 59) {
            frameCount++;
        }
        else {
            frameCount = 0;
        }
    }

    return EXIT_SUCCESS;
}

void CustomLog(int msgType, const char *text, va_list args) {
    // Does nothing, just takes startup output from raylib so there is no console spam
}