#include "Game.h"
#include "textures_models.h"

#include "../include/Speed.h"

typedef struct _collision_area {
    int range[2];
    bool rangeX; // true if range is on x-axis, false if on y-axis
                // If player is within this range, game will check if next movement will cross "bound" and prevent move if so
    int bound;
    bool boundX; // similar to "rangeX" but for bound dimension
} collision_area;

// Defines out-of-bounds areas
typedef struct _map_collisions {
    collision_area* bounds;
    int boundsN;
} map_collisions;

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
} GAME;

Vector3 floorplan_position;
Vector3 purdue_pete_position;
Vector3 spider_demon_position;
Vector3 baseplate_position;
Vector3 walc_backwall_pos;
Vector3 racetrack_inside_v1_pos;
Vector3 racetrack_v1_pos;
Vector3 ellip_racetrack_pos;
Vector3 ellip_inside_racetrack_pos;
Vector3 Lowpoly_tree_pos;

int MOVEMENT_SPEED_SCALE = 3;
int LOOK_SPEED_SCALE = 2;
float M_STEP;
float L_STEP;

map_collisions map_bounds = { 0 };

// Unit vector representing the view direction of the camera
Vector3 CamHat = { 0 };
float CamHatLen = 0.0f;

int main(int argc, char** argv) {
    // Fairly basic game structure
    // 1. Load any fonts needed
    //    (should be stored in ./game/resource/fonts)
    //TODO ... ... ...

    // 2. Call "CreateGameInstance()" to allocate mem for the game instance
    if (CreateGameInstance(2000, 1400) 
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

    ClearBackground(LIGHTGRAY);
    BeginMode3D(game->cam);
        DrawModel(game->model, game->mapPos, 1.0f, BLACK);   
        DrawModel(game->playerModel, game->playerPos, 1.0f, BLACK);
        for (size_t i = 0; i < game->hammers[0].speed; i++) {
            game->hammers[i].pos.z += game->hammers[i].speed;
            DrawCubeWires(game->hammers[i].pos, 50, 50, 70, BLACK);
        }
        DrawModelEx(floorplan_v1, floorplan_position, (Vector3){1, 0, 0}, -90, (Vector3){1, 1, 1}, WHITE);
        DrawModelEx(peteypie, purdue_pete_position, (Vector3){0, 1, 0}, 90, (Vector3){3, 3, 3}, GOLD);
        DrawModelEx(demon_spider_monkey_model, spider_demon_position, (Vector3){0, 1, 0}, 90, (Vector3){3, 3, 3}, RED);
        DrawModelEx(racetrack_v1, racetrack_v1_pos, (Vector3){1, 0, 0}, -90, (Vector3){1, 1, 1}, BLACK);
        DrawModelEx(racetrack_inside_v1, racetrack_inside_v1_pos, (Vector3){1, 0, 0}, -90, (Vector3){1, 1, 1}, GREEN);
        DrawModelEx(Elliptical_Track, ellip_racetrack_pos, (Vector3){1, 0, 0}, -90, (Vector3){1, 1, 1}, BLACK);
        DrawModelEx(Inside_Track, ellip_inside_racetrack_pos, (Vector3){1, 0, 0}, -90, (Vector3){1, 1, 1}, GREEN);
        DrawModelEx(Lowpoly_tree_sample, Lowpoly_tree_pos, (Vector3){1, 0, 0}, -90, (Vector3){1, 1, 1}, BROWN);
    EndMode3D();
    
    DrawTextureEx(*cubicmap, (Vector2){ GetScreenWidth() - cubicmap->width*4.0f - 20, 20.0f }, 0.0f, 4.0f, MAROON);
    DrawRectangleLines(GetScreenWidth() - cubicmap->width*4 - 20, 20, 
                cubicmap->width*4, cubicmap->height*4, ORANGE);
    
    // Draw player position radar
    //DrawRectangle(GetScreenWidth() - cubicmap->width*4 - 20 + game->playerCellX*4, 20 + game->playerCellY*4, 4, 4, RED);
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

    // Print current camera location to terminal
    if (IsKeyPressed(KEY_L)) {
        printf("%.2f %.2f %.2f\n", game->cam.position.x, game->cam.position.y, game->cam.position.z);
    }

    // if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    //     if (game->hammers[0] == 0) {
    //         game->hammers = realloc(game->hammers, game->hammers[1]*sizeof(hammer));
    //     }void LoadCollisionBounds();
    //     if (game->hammers[0] + 1 > game->hammers[1]) {
    //         game->hammers = realloc(game->hammers, game->hammers[1]*sizeof(hammer)*2);
    //         game->hammers[1]*=2;
    //     }
    //     hammer h = {.speed = 1.1, .pos.x = game->playerPos.x+1.1, .pos.y = game->playerPos.y, .pos.z = game->playerPos.z};
    //     game->hammers[game->hammers[0]] = h;
    //     DrawCubeWires(h.pos, 50, 50, 70, BLACK);
    // }
    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){ 0, 0, GetScreenWidth(), GetScreenHeight() })) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            DisableCursor();
        }
    }
    // Release mouse cursor if you press ESCAPE
    if (IsKeyPressed(KEY_ESCAPE)) {
        EnableCursor();
    }
    
}

void LoadCollisionBounds() {
    map_bounds.boundsN = 17;
    map_bounds.bounds = malloc(sizeof(collision_area) * map_bounds.boundsN);

    // Manually defining the boundaries
    collision_area* _b = map_bounds.bounds;

    _b[0] = (collision_area){ .range={0,268}, .rangeX=true, .bound=130, .boundX=false};
    _b[1] = (collision_area){ .range={0,250}, .rangeX=true, .bound=780, .boundX=false};
    _b[2] = (collision_area){ .range={195,705}, .rangeX=false, .bound=338, .boundX=true};
    
    _b[3] = (collision_area){ .range={418,626}, .rangeX=true, .bound=130, .boundX=false};
    _b[4] = (collision_area){ .range={418,626}, .rangeX=true, .bound=780, .boundX=false};
    _b[5] = (collision_area){ .range={130,780}, .rangeX=false, .bound=418, .boundX=true};
    _b[6] = (collision_area){ .range={130,780}, .rangeX=false, .bound=626, .boundX=true};
    
    _b[7] = (collision_area){ .range={130,180}, .rangeX=false, .bound=1040, .boundX=true};
    _b[8] = (collision_area){ .range={730,780}, .rangeX=false, .bound=1040, .boundX=true};
    
    _b[9] = (collision_area){ .range={1040,1300}, .rangeX=true, .bound=130, .boundX=false};
    _b[10] = (collision_area){ .range={1040,1300}, .rangeX=true, .bound=780, .boundX=false};
    _b[11] = (collision_area){ .range={0,130}, .rangeX=false, .bound=1140, .boundX=true};
    _b[12] = (collision_area){ .range={780,910}, .rangeX=false, .bound=1140, .boundX=true};
    
    _b[13] = (collision_area){ .range={0,1300}, .rangeX=true, .bound=0, .boundX=false};
    _b[14] = (collision_area){ .range={0,1300}, .rangeX=true, .bound=910, .boundX=false};
    _b[15] = (collision_area){ .range={0,910}, .rangeX=false, .bound=0, .boundX=true};
    _b[16] = (collision_area){ .range={0,910}, .rangeX=false, .bound=1300, .boundX=true};
}

void GAME_loadGame(void* game_state) {
    GAME* gm = (GAME*)mainGame->game;
    load_textures_and_models();
    LoadCollisionBounds();

    // Define the camera to look into our 3d world
    gm->cam = (Camera){ 0 };
    gm->cam.position = (Vector3){ 16.0f, 5.0f, 16.0f };     // Camera position
    gm->cam.target = (Vector3){ 0.0f, 0.0f, 0.0f };          // Camera looking at point
    gm->cam.up = (Vector3){ 0.0f, 1.0f, 0.0f };              // Camera up vector (rotation towards target)
    gm->cam.fovy = 45.0f;                                    // Camera field-of-view Y
    gm->cam.projection = CAMERA_PERSPECTIVE;                 // Camera projection type

    // Set camera movement+look step
    M_STEP = 0.1f * MOVEMENT_SPEED_SCALE;
    L_STEP = 0.05f * LOOK_SPEED_SCALE;

    floorplan_position = (Vector3){0.0f, 0.0f, 0.0f };
    purdue_pete_position = (Vector3){-50.0f, 4.5f, -39.0f };
    spider_demon_position = (Vector3){-50.0f, 4.5f, 0.0f};
    racetrack_v1_pos = (Vector3){-200.0f, 0.0f, 0.0f};
    racetrack_inside_v1_pos = (Vector3){-210.0f, 0.0f, 0.0f};
    ellip_inside_racetrack_pos = (Vector3){210.0f, 0.0f, 0.0f};
    ellip_racetrack_pos = (Vector3){210.0f, 0.0f, 0.0f};
    Lowpoly_tree_pos = (Vector3){210.0f, 0.0f, 0.0f};
    // Load cubicmap image (RAM)
    /*gm->cubicmap = LoadTextureFromImage(imMap);       // Convert image to texture to display (VRAM)
    Mesh mesh = GenMfeshCubicmap(imMap, (Vector3){ 1.0f, 1.0f, 1.0f });
    gm->model = LoadModelFromMesh(mesh);*/

    // NOTE: By default each cube is mapped to one part of texture atlas
    //Texture2D texture = LoadTexture("game/textures/guytex.png");    // Load map texture
    //gm->model.matersials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;    // Set map diffuse texture

    gm->mapPos  = (Vector3){ -16.0f, 0.0f, -8.0f }; // Set model position
    gm->hammers = malloc(sizeof(hammer));

}

bool WallProbe(Camera3D* camera) {
    // Get unit vector direction of camera view (adapted from MatrixLookAt() in raylib source)
    CamHat.x = camera->position.x - camera->target.x;
    CamHat.y = camera->position.y - camera->target.y;
    CamHat.z = camera->position.z - camera->target.z;

    CamHatLen = sqrtf(CamHat.x*CamHat.x + CamHat.y*CamHat.y + CamHat.z*CamHat.z);
    if (CamHatLen == 0.0f) CamHatLen = 1.0f;
    
    CamHat.x *= (1.0f / CamHatLen);
    CamHat.y *= (-1.0f / CamHatLen);
    CamHat.z *= (1.0f / CamHatLen);
    // Print cam direction to terminal
    //printf("%.2f %.2f %.2f\n", CamHat.x, CamHat.y, CamHat.z);

    // Check if unit movement would go out-of-bounds
    // for any defined bounds rectangles
    // for (int r = 0; r < )
    //     if ((CamHat.x * M_STEP >))

    return false;
}

void UpdatePlayer() {
    GAME* game = (GAME*)mainGame->game;
    Camera3D* cam = &(game->cam);
        
    // If one unit move would put the player out of bounds,
    // prevent the movement from happening
    if (WallProbe(cam)) {
        return;
    }

    UpdateCameraPro(&game->cam,
        (Vector3){
            M_STEP * (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) -      // Move forward-backward
            M_STEP * (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)),    
            M_STEP * (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) -   // Move right-left
            M_STEP * (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)),
            0.0f                                                // Move up-down
        },
        (Vector3){
            L_STEP * GetMouseDelta().x,                            // Rotation: yaw
            L_STEP * GetMouseDelta().y,                            // Rotation: pitch
            0.0f                                                // Rotation: roll
        },
        GetMouseWheelMove()*2.0f);
}

void GAME_updateGame() {
    GAME* game = (GAME*)mainGame->game;
    if (!game->paused) {
        UpdatePlayer();
        
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
    }
}
