#include <raylib.h>

#include "Game.h"

/////////////////////////////
// Global texture variables
/////////////////////////////
Texture2D epic_github_logo;
Texture2D spider_demon_model;
Texture2D purdue_pete;
Texture2D purdue_galaga_plane;
Texture2D purdue_scorpion;
Texture2D purdue_galaxian;
Texture2D purdue_galaga;
Texture2D purdue_butterfly;
Texture2D purdue_bumblebee;
Texture2D purdue_boss_galaga;
Texture2D purdue_boss_galaga_laser;
Texture2D purdue_bosconian;
Texture2D Industrial;

/////////////////////////////
// Global model variables
/////////////////////////////
Model floorplan_v1;
Model peteypie;

BoundingBox floorplan_bbox;

//If you want to attach a texture to a model consult the castle example on Raylib
void models() {
    floorplan_v1 = LoadModel("game/models/floorplan_v1.obj");
    
    peteypie = LoadModel("game/models/peteypie.png");
}

void textures() {
    //PurDoom Textures
    epic_github_logo = LoadTexture("game/textures/epic_github_logo.png");
    spider_demon_model = LoadTexture("game/textures/spider_demon_model.png");
    purdue_pete = LoadTexture("game/textures/purdue_pete.png");

    //Purdue Themed Galaga Textures
    purdue_galaga_plane = LoadTexture("game/textures/purdue_galaga_plane.png");
    purdue_scorpion = LoadTexture("game/textures/purdue_scorpion.png");
    purdue_galaxian = LoadTexture("game/textures/purdue_galaxian.png");
    purdue_galaga = LoadTexture("game/textures/purdue_galaga.png");
    purdue_butterfly = LoadTexture("game/textures/purdue_butterfly.png");
    purdue_bumblebee = LoadTexture("game/textures/purdue_bumblebee.png");
    purdue_boss_galaga = LoadTexture("game/textures/purdue_boss_galaga.png");
    purdue_boss_galaga_laser = LoadTexture("game/textures/purdue_boss_galaga_laser.png");
    purdue_bosconian = LoadTexture("game/textures/purdue_bosconian.png");
    Industrial = LoadTexture("game/textures/Industrial.png");
}

void load_textures_and_models() {
    textures();
    models();

    //Connect textures and models with each other when needed
    floorplan_v1.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = Industrial;
    peteypie.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = purdue_pete;
    floorplan_bbox = GetMeshBoundingBox(floorplan_v1.meshes[0]);
}

/*Examples:
Model model = LoadModel("resources/models/obj/castle.obj");                 // Load model
Texture2D texture = LoadTexture("resources/models/obj/castle_diffuse.png"); // Load model texture
model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;*/

void unload_models() {
    UnloadModel(floorplan_v1);
    //UnloadModel(peteypie);
}

void unload_textures() {
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