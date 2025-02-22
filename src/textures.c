//#include <Speed.h>

/*int main() {
    Vector3 pos = {0, 0, 0};
    Camera3D cam = {0};
    cam.position = (Vector3){ 0.0f, 10.0f, 10.0f };
    cam.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    InitWindow(800, 450, "test");
    Model model = LoadModel("C:\\raylib-master\\examples\\models\\resources\\models\\obj\\cube.obj");
    Texture2D texture = LoadTexture("C:\\raylib-master\\examples\\models\\resources\\models\\obj\\cube_diffuse.png"); 
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    while (!WindowShouldClose()) {
        UpdateCamera(&cam, CAMERA_FIRST_PERSON);
        ClearBackground(RAYWHITE);
        BeginDrawing();
        BeginMode3D(cam);
        DrawModel(model, pos, 1.0f, RED);
        DrawGrid(20, 10.0f);
        EndMode3D();
        DrawText("(c) Cube 3D model", 250, 780, 10, GRAY);
        DrawFPS(10, 10);
        EndDrawing();
    }
}*/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - models loading");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector2){ 50.0f, 50.0f}; // Camera position
    camera.target = (Vector2){ 0.0f, 10.0f};     // Camera looking at point
    camera.up = (Vector2){ 0.0f, 1.0f};          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

    Model model = LoadModel("C:\\raylib-master\\examples\\models\\resources\\models\\obj\\cube.obj");                 // Load model
    Texture2D texture = LoadTexture("C:\\raylib-master\\examples\\models\\resources\\models\\obj\\cube_diffuse.png"); // Load model texture
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;            // Set map diffuse texture

    Vector2 position = { 0.0f, 0.0f};                    // Set model position

    BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);   // Set model bounds

    // NOTE: bounds are calculated from the original size of the model,
    // if model is scaled on drawing, bounds must be also scaled

    bool selected = false;          // Selected object flag

    DisableCursor();                // Limit cursor to relative movement inside the window

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        // Load new models/textures on drag&drop
        if (IsFileDropped())
        {
            FilePathList droppedFiles = LoadDroppedFiles();

            if (droppedFiles.count == 1) // Only support one file dropped
            {
                if (IsFileExtension(droppedFiles.paths[0], ".obj") ||
                    IsFileExtension(droppedFiles.paths[0], ".gltf") ||
                    IsFileExtension(droppedFiles.paths[0], ".glb") ||
                    IsFileExtension(droppedFiles.paths[0], ".vox") ||
                    IsFileExtension(droppedFiles.paths[0], ".iqm") ||
                    IsFileExtension(droppedFiles.paths[0], ".m3d"))       // Model file formats supported
                {
                    UnloadModel(model);                         // Unload previous model
                    model = LoadModel(droppedFiles.paths[0]);   // Load new model
                    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture; // Set current map diffuse texture

                    bounds = GetMeshBoundingBox(model.meshes[0]);

                    // TODO: Move camera position from target enough distance to visualize model properly
                }
                else if (IsFileExtension(droppedFiles.paths[0], ".png"))  // Texture file formats supported
                {
                    // Unload current model texture and load new one
                    UnloadTexture(texture);
                    texture = LoadTexture(droppedFiles.paths[0]);
                    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
                }
            }

            UnloadDroppedFiles(droppedFiles);    // Unload filepaths from memory
        }

        // Select model on mouse click
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // Check collision between ray and box
            if (GetRayCollisionBox(GetScreenToWorldRay(GetMousePosition(), camera), bounds).hit) selected = !selected;
            else selected = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode2D(camera);

                DrawModel(model, position, 1.0f, WHITE);        // Draw 3d model with texture

                DrawGrid(20, 10.0f);         // Draw a grid

                if (selected) DrawBoundingBox(bounds, GREEN);   // Draw selection box

            EndMode2D();

            DrawText("Drag & drop model to load mesh/texture.", 10, GetScreenHeight() - 20, 10, DARKGRAY);
            if (selected) DrawText("MODEL SELECTED", GetScreenWidth() - 110, 10, 10, GREEN);

            DrawText("(c) Castle 3D model by Alberto Cano", screenWidth - 200, screenHeight - 20, 10, GRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);     // Unload texture
    UnloadModel(model);         // Unload model

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}