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
    }*/

    // 3. Assign the game's function pointers to the fields of "mainGame"
    //mainGame->game = &GAME_createInstance(1000, 700);
    GAME cur = {.paused = 0};
    mainGame->game = cur;
    mainGame->updateGame = GAME_updateGame;
    mainGame->inputHandle = GAME_inputHandle;
    
    // 4. Initialize the game window
    /*if (InitGUI("PurDOOM/Game Engine") == EXIT_FAILURE) {
        printf("*** ERROR: unable to initialize raylib window. Exiting...\n");
        if (mainGame != NULL) {
            free(mainGame);
        }
        return EXIT_FAILURE;
    }
    */
    // 5. Start the main loop (call GameLoop())
    /*if (GameLoop() == EXIT_FAILURE) {
        // Trust that the callee already printed error msg
        return EXIT_FAILURE;
    }*/

    // 6. De-init game, unload fonts and textures
    //TODO ... ... ...

    // 7. Free mainGame, anything else that was allocated
    //free(mainGame);

    return EXIT_SUCCESS;
}


#Loads all textures and models.
void GAME_loadGame(void* g) {
    GAME* g = (GAME) g;

    // Define the camera to look into our 3d world
    g->cam = (Camera){ 0 };
    g->cam.position = (Vector3){ 16.0f, 14.0f, 16.0f };     // Camera position
    g->cam.target = (Vector3){ 0.0f, 0.0f, 0.0f };          // Camera looking at point
    g->cam.up = (Vector3){ 0.0f, 1.0f, 0.0f };              // Camera up vector (rotation towards target)
    g->cam.fovy = 45.0f;                                    // Camera field-of-view Y
    g->cam.projection = CAMERA_PERSPECTIVE;                 // Camera projection type

    Image imMap = LoadImage("resources/cubicmap.png");      // Load cubicmap image (RAM)
    g->cubicmap = LoadTextureFromImage(imMap);       // Convert image to texture to display (VRAM)
    Mesh mesh = GenMeshCubicmap(imMap, (Vector3){ 1.0f, 1.0f, 1.0f });
    g->model = LoadModelFromMesh(mesh);

    // NOTE: By default each cube is mapped to one part of texture atlas
    Texture2D texture = LoadTexture("c:\\raylib-master\\examples\\models\\resources\\models\\iqm\\guytex.png");    // Load map texture
    g->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;    // Set map diffuse texture

    Vector3 mapPosition = { -16.0f, 0.0f, -8.0f };          // Set model position

    UnloadImage(image);     // Unload cubesmap image from RAM, already uploaded to VRAM
                             // Pause camera orbital rotation (and zoom)
    mainGame->game = g;
}

void GAME_updateGame(void* game) {
    GAME* g = (GAME*) game;
    if (!game->paused) {
        Camera3D oldCam = game->cam.pos;
        UpdateCamera(&game->cam, CAMERA_FIRST_PERSON);
        Vector2 playerPos = {game->cam.pos.x, game->cam.pos.z};
        int playerCellX = (int)(game->playerPos.x - game->mapPosition.x + 0.5f);
        int playerCellY = (int)(game->playerPos.y - game->mapPosition.z + 0.5f);
        if (playerCellX < 0) playerCellX = 0;
        else if (playerCellX >= game->cubicmap.width) playerCellX = game->cubicmap.width - 1;
        if (playerCellY < 0) playerCellY = 0;
        else if (playerCellY >= game->cubicmap.height) playerCellY = game->cubicmap.height - 1;
        #Add collision detection
        BeginDrawing();
        ClearBackground(GOLD);
        BeginMode3D(game->cam);
        DrawModel(game->model, game->mapPosition, 1.0f, BLACK);   
        DrawModel(game->playerModel, game->cam.pos, 1.0f, BLACK);  
        EndMode3D();
        DrawTextureEx(game->cubicmap, (Vector2){ GetScreenWidth() - game->cubicmap.width*4.0f - 20, 20.0f }, 0.0f, 4.0f, MAROON);
        DrawRectangleLines(GetScreenWidth() - cubicmap.width*4 - 20, 20, game->cubicmap.width*4, cubicmap.height*4, ORANGE);
        // Draw player position radar
        DrawRectangle(GetScreenWidth() - game->cubicmap.width*4 - 20 + playerCellX*4, 20 + playerCellY*4, 4, 4, RED);
        DrawFPS(10, 10);
        EndDrawing();
    }
    mainGame->game = game;
}

void GAME_inputHandle(void* game) {
    GAME* game = (GAME*) game;
    if (IsKeyPressed('p') && game->paused == 0){
        if (game->paused) {
            game->paused = 0;
        } else {
            game->paused = 1;
            mainGame->game = game;
            return;
        }
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        DrawCubeWires(Vector3 position, float width, float height, float length, BLACK);
    }
    mainGame->game = game;
}


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
    Vector3 playerPos;
    Vector3 mapPos;
    Model model;
    Model playerModel;
    enemy* enemies;
    hammer* hammers;
} GAME;