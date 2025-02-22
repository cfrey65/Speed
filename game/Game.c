#include "Speed.h"
#include "Game.h"

int main(int argc, char** argv) {
    // Fairly basic game structure
    // 1. Load any fonts or textures needed
    //    (should be stored in ./game/resource/fonts, ./game/resource/textures)
    //TODO ... ... ...
    
    //Textures MUST be loaded after Window initialization (OpenGL context is required)

    // 2. Call "CreateGameInstance()" to allocate mem for the game instance
    if (CreateGameInstance(1000, 700) 
        == EXIT_FAILURE) {
        if (mainGame != NULL) {
            free(mainGame);
        }
        return EXIT_FAILURE;
    }

    // 3. Assign the game's function pointers to the fields of "mainGame"
    mainGame->drawGame = GAME_drawGame;
    mainGame->updateGame = GAME_updateGame;
    mainGame->inputHandle = GAME_inputHandle;
    mainGame->pauseGame = GAME_pauseGame;
    mainGame->resumeGame = GAME_resumeGame;
    
    // 4. Initialize the game window
    if (InitGUI("PurDOOM/Game Engine") == EXIT_FAILURE) {
        printf("*** ERROR: unable to initialize raylib window. Exiting...\n");
        if (mainGame != NULL) {
            free(mainGame);
        }
        return EXIT_FAILURE;
    }

    // 5. Start the main loop (call GameLoop())
    if (GameLoop() == EXIT_FAILURE) {
        // Trust that the callee already printed error msg
        return EXIT_FAILURE;
    }

    // 6. De-init game, unload fonts and textures
    //TODO ... ... ...

    // 7. Free mainGame, anything else that was allocated
    free(mainGame);

    return EXIT_SUCCESS;
}

void GAME_drawGame() {
    // Set background color
    ClearBackground(RED);
}

#Loads all textures and models.
void GAME_loadGame() {

}

void GAME_updateGame(g* game) {
    Camera3D oldCam = game->cam.pos;
    UpdateCamera(&ga)
}

void GAME_inputHandle() {

}

void GAME_pauseGame() {


}

void GAME_resumeGame() {


}