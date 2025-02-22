#include <raylib.h>

//If you want to attach a texture to a model consult the castle example on Raylib
void unload_models() {
    UnloadModel(baseplate_v2);
    UnloadModel(peteypie);
}

void unload_textures(){
    UnloadTexture(epic_github_logo);
    UnloadTexture(spider_demon_model);
    UnloadTexture(purdue_pete);
    UnloadTexture(purdue_galaga_plane);
}

void unload_textures_and_models() {
    unload_textures();
    unload_models();
}