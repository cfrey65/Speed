#pragma once

#include "Speed.h"
//mtllib floorplan_v1.mtl
/////////////////////////////
// Global texture variables
/////////////////////////////
extern Texture2D epic_github_logo; extern Texture2D spider_demon_model;
extern Texture2D purdue_pete; extern Texture2D purdue_galaga_plane;
extern Texture2D purdue_scorpion; extern Texture2D purdue_galaxian;
extern Texture2D purdue_galaga; extern Texture2D purdue_butterfly;
extern Texture2D purdue_bumblebee; extern Texture2D purdue_boss_galaga;
extern Texture2D purdue_boss_galaga_laser; extern Texture2D purdue_bosconian;
extern Texture2D Industrial;
/////////////////////////////
// Global model variables
/////////////////////////////
extern Model floorplan_v1;
extern Model peteypie;
extern Model demon_spider_monkey_model;
extern Vector3 floorplan_position;
extern Model racetrack_v1;
extern Model racetrack_inside_v1;
extern Model Walc_Baseplate;
extern Model Walc_Backwall;
extern Model Walc_Door;
extern Model Walc_Sidewall2;
extern Model Walc_SideWalls;
extern Model Elliptical_Track;
extern Model Inside_Track;
extern Model Lowpoly_tree_sample;

extern BoundingBox floorplan_bbox;

// Implementations pointed to by "mainGame"
// The actual "game code"
// Called by the game engine each frame or upon specific events
void GAME_loadGame(void* game_state);
void LoadCollisionBounds(); // Populates the Rectangle array in "map_bounds"
void GAME_drawGame();
void GAME_updateGame();
void GAME_inputHandle();
void GAME_pauseGame();
void GAME_resumeGame();
// Check if player is about to move out-of-bounds
bool WallProbe(Camera3D* camera, Vector3* playerPos);