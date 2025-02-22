#include <raylib.h>

//If you want to attach a texture to a model consult the castle example on Raylib
void unload_models() {
    UnloadModel(baseplate_v2);
    UnloadModel(peteypie);
}

void unload_textures(){
    //Unload PurDoom
    UnloadTexture(epic_github_logo);
    UnloadTexture(spider_demon_model);
    UnloadTexture(purdue_pete);

    //Unload Galaga
    UnloadTexture(purdue_galaga_plane);
    UnloadTexture(purdue_scorpion);
    UnloadTexture(purdue_galaxian);
    UnloadTexture(purdue_galaga);
    UnloadTexture(purdue_butterfly);
    UnloadTexture(purdue_bumblebee);
    UnloadTexture(purdue_boss_galaga);
    UnloadTexture(purdue_boss_galaga_laser);
    UnloadTexture(purdue_bosconian);
}

void unload_textures_and_models() {
    unload_textures();
    unload_models();
}