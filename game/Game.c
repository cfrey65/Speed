#include "Game.h"
#include "textures_models.h"

#include "../include/Speed.h"

typedef struct hammer {
    float speed;
    Vector3 pos;
} hammer;

typedef struct enemy{
    Model model;
    Vector3 pos;
} enemy;

typedef struct env {
    bool paused;
    Texture2D cubicmap;
    Camera3D cam;
    int playerCellX, playerCellY;
    Vector3 playerPos;
    Vector3 mapPos;
    Model model;
    Model playerModel;
    enemy* enemies;
    hammer* hammers;
    size_t hams [2];
} GAME;

Vector3 floorplan_position;

int main(int argc, char** argv) {
    // Fairly basic game structure
    // 1. Load any fonts needed
    //    (should be stored in ./game/resource/fonts)
    //TODO ... ... ...

    // 2. Call "CreateGameInstance()" to allocate mem for the game instance
    if (CreateGameInstance(1000, 700) 
        == EXIT_FAILURE) {
        if (mainGame != NULL) {
            free(mainGame);
        }
        return EXIT_FAILURE;
    }

    // 3. Assign GAME STATE fields (for the behavior of the game on startup)
    //    Also GAME OBJECT'S function pointers, which are called directly by the "Speed.c" engine
    GAME cur = {.paused = 0};
    mainGame->game = (void*)&cur;
    mainGame->updateGame = GAME_updateGame;
    mainGame->inputHandle = GAME_inputHandle;
    mainGame->drawGame = GAME_drawGame;
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

    // Load TEXTURES (./game/resource/textures)
    //Textures MUST be loaded after Window initialization (OpenGL context is required)
    GAME* game_state = malloc(sizeof(GAME));
    GAME_loadGame(game_state);

    // 5. Start the main loop (call GameLoop())
    if (GameLoop() == EXIT_FAILURE) {
        // Trust that the callee already printed error msg
        return EXIT_FAILURE;
    }

    // 6. De-init game, unload fonts and textures
    unload_textures_and_models();

    // 7. Free mainGame, anything else that was allocated
    free(mainGame);

    return EXIT_SUCCESS;
}

void GAME_pauseGame() {

}

void GAME_resumeGame() {

}

void GAME_drawGame() {
    GAME* game = (GAME*)mainGame->game;
    Texture2D* cubicmap = &(game->cubicmap);

    ClearBackground(GOLD);
    BeginMode3D(game->cam);
        DrawModel(game->model, game->mapPos, 1.0f, BLACK);   
        DrawModel(game->playerModel, game->playerPos, 1.0f, BLACK);
        DrawModel(floorplan_v1, floorplan_position, 1.0f, WHITE);
        for (size_t i = 0; i < game->hams[0]; i++) {
            game->hammers[i].pos.z += game->hammers[i].speed;
            DrawCubeWires(game->hammers[i].pos, 50, 50, 70, BLACK)
        }
    EndMode3D();
    
    DrawTextureEx(*cubicmap, (Vector2){ GetScreenWidth() - cubicmap->width*4.0f - 20, 20.0f }, 0.0f, 4.0f, MAROON);
    DrawRectangleLines(GetScreenWidth() - cubicmap->width*4 - 20, 20, 
                cubicmap->width*4, cubicmap->height*4, ORANGE);
    
    // Draw player position radar
    DrawRectangle(GetScreenWidth() - cubicmap->width*4 - 20 + game->playerCellX*4, 20 + game->playerCellY*4, 4, 4, RED);
    DrawFPS(10, 10);
}

void GAME_inputHandle() {
    GAME* game = (GAME*)mainGame->game;
    if (IsKeyPressed('p') && game->paused == 0){
        if (game->paused) {
            game->paused = 0;
        } else {
            game->paused = 1;
            return;
        }
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (game->hams[0] == 0) {
            game->hammers = realloc(game->hammers, game->hams[1]*sizeof(hammer));
        }
        if (game->hams[0] + 1 > game->hams[1]) {
            game->hammers = realloc(game->hammers, game->hams[1]*sizeof(hammer)*2);
            game->hams[1]*=2;
        }
        hammer h = {.speed = 1.1, .pos.x = game->playerPos.x+1.1, .pos.y = game->playerPos.y, .pos.z = game->playerPos.z};
        game->hammers[game->hams[0]] = h;
        DrawCubeWires(h.pos, 50, 50, 70, BLACK);
    }
}

void GAME_loadGame(void* game_state) {
    GAME* gm = (GAME*)mainGame->game;
    load_textures_and_models();

    // Define the camera to look into our 3d world
    gm->cam = (Camera){ 0 };
    gm->cam.position = (Vector3){ 16.0f, 14.0f, 16.0f };     // Camera position
    gm->cam.target = (Vector3){ 0.0f, 0.0f, 0.0f };          // Camera looking at point
    gm->cam.up = (Vector3){ 0.0f, 1.0f, 0.0f };              // Camera up vector (rotation towards target)
    gm->cam.fovy = 45.0f;                                    // Camera field-of-view Y
    gm->cam.projection = CAMERA_PERSPECTIVE;                 // Camera projection type

    floorplan_position = (Vector3){0.0f, 0.0f, 0.0f }; //Wish this could be initialized seperately from the other models
    // Load cubicmap image (RAM)
    /*gm->cubicmap = LoadTextureFromImage(imMap);       // Convert image to texture to display (VRAM)
    Mesh mesh = GenMeshCubicmap(imMap, (Vector3){ 1.0f, 1.0f, 1.0f });
    gm->model = LoadModelFromMesh(mesh);*/

    // NOTE: By default each cube is mapped to one part of texture atlas
    //Texture2D texture = LoadTexture("game/textures/guytex.png");    // Load map texture
    //gm->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;    // Set map diffuse texture

    gm->mapPos  = (Vector3){ -16.0f, 0.0f, -8.0f }; // Set model position

    //UnloadImage(imMap);     // Unload cubesmap image from RAM, already uploaded to VRAM
                             // Pause camera orbital rotation (and zoom)
}

void GAME_updateGame() {
    GAME* game = (GAME*)mainGame->game;
    if (!game->paused) {
        //Camera3D oldCam = game->cam;
        UpdateCamera(&game->cam, CAMERA_FIRST_PERSON);
        
        Vector2 playerPos = {game->cam.position.x, game->cam.position.z};
        game->playerCellX = (int)(playerPos.x - game->mapPos.x + 0.5f);
        game->playerCellY = (int)(playerPos.y - game->mapPos.z + 0.5f);
        if (game->playerCellX < 0) {
            game->playerCellX = 0;
        }
        else if (game->playerCellX >= game->cubicmap.width) {
            game->playerCellX = game->cubicmap.width - 1;
        }
        if (game->playerCellY < 0) {
            game->playerCellY = 0;
        }
        else if (game->playerCellY >= game->cubicmap.height) {
            game->playerCellY = game->cubicmap.height - 1;
        }
        
        // Add collision detection
    }
}
