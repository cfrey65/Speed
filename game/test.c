#include <raylib.h>

int main() {
    Vector3 pos = {250, 250, 0};
    Camera3D cam = {1};
    Vector3 camPos = {0, pos.y+10, pos.z+10};
    cam.position = camPos;
    cam.target = pos;
    InitWindow(500, 500, "test");
    ClearBackground(RED);
    BeginDrawing();
    BeginMode3D(cam);
    LoadModel("C:\\raylib\\raylib\\examples\\models\\resources\\models\\obj\\plane.obj");
    EndMode3D();
    EndDrawing();
}