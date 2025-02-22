#pragma once

#include "Speed.h"

/////////////////////////////
// Global texture variables
/////////////////////////////
extern Texture2D epic_github_logo; extern Texture2D spider_demon_model;
extern Texture2D purdue_pete; extern Texture2D purdue_galaga_plane;
extern Texture2D purdue_scorpion; extern Texture2D purdue_galaxian;
extern Texture2D purdue_galaga; extern Texture2D purdue_butterfly;
extern Texture2D purdue_bumblebee; extern Texture2D purdue_boss_galaga;
extern Texture2D purdue_boss_galaga_laser; extern Texture2D purdue_bosconian;

/////////////////////////////
// Global model variables
/////////////////////////////
extern Model baseplate_v2;
extern Model peteypie;

// Implementations pointed to by "mainGame"
// The actual "game code"
// Called by the game engine each frame or upon specific events
void GAME_loadGame(void* game_state);
void GAME_drawGame();
void GAME_updateGame(void* game_state);
void GAME_inputHandle();
void GAME_pauseGame();
void GAME_resumeGame();