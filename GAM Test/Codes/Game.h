
#ifndef GAME_H

#define GAME_H
#include <stdbool.h>

void game_init();

bool game_isRunning();

void game_update();

void game_playerAction(int action);
void game_loadMap(int mapNo);

#endif