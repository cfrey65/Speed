#include <raylib.h>

//If you want to attach a texture to a model consult the castle example on Raylib
void models() {
    Model baseplate_v2 = LoadModel("Models/baseplate_v2.obj");
    Model peteypie = LoadModel("Models/peteypie.png");
}

void textures(){
    //PurDoom Textures
    Texture2D epic_github_logo = LoadTexture("Textures/epic_github_logo.png");
    Texture2D spider_demon_model = LoadTexture("Textures/spider_demon_model.png");
    Texture2D purdue_pete = LoadTexture("Textures/purdue_pete.png");

    //Purdue Themed Galaga Textures
    Texture2D purdue_galaga_plane = LoadTexture("Textures/purdue_galaga_plane.png");
    Texture2D purdue_scorpion = LoadTexture("Textures/purdue_scorpion.png");
    Texture2D purdue_galaxian = LoadTexture("Textures/purdue_galaxian.png");
    Texture2D purdue_galaga = LoadTexture("Textures/purdue_galaga.png");
    Texture2D purdue_butterfly = LoadTexture("Textures/purdue_butterfly.png");
    Texture2D purdue_bumblebee = LoadTexture("Textures/purdue_bumblebee.png");
    Texture2D purdue_boss_galaga = LoadTexture("Textures/purdue_boss_galaga.png");
    Texture2D purdue_boss_galaga_laser = LoadTexture("Textures/purdue_boss_galaga_laser.png");
    Texture2D purdue_bosconian = LoadTexture("Textures/purdue_bosconian.png");
}

void load_textures_and_models() {
    textures();
    models();

    //Connect textures and models with each other when needed
    peteypie.materials[0].maps[MATERIAL_MAP_DIFFUSE].purdue_pete = purdue_pete;
}

/*Examples:
Model model = LoadModel("resources/models/obj/castle.obj");                 // Load model
Texture2D texture = LoadTexture("resources/models/obj/castle_diffuse.png"); // Load model texture
model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;*/

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