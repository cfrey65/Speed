#include <raylib.h>

//If you want to attach a texture to a model consult the castle example on Raylib
void models() {
    Model baseplate = LoadModel("Models/baseplate_v2.obj");
}

void textures(){
    Texture2D epic_github_logo = LoadTexture(const char "Textures/epic_github_logo.png");
    Texture2D spider_demon_model = LoadTexture(const char "Textures/spider_demon_model.png");
}

void load_textures_and_models() {
    textures();
    models();
}