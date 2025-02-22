#pragma once

#include "Speed.h"

// Implementations pointed to by "mainGame"
// The actual "game code"
// Called by the game engine each frame or upon specific events
void GAME_drawGame();
void GAME_updateGame();
void GAME_inputHandle();
void GAME_pauseGame();
void GAME_resumeGame();