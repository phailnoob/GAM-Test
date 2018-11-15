
#ifndef GAME_H

#define GAME_H
#include <stdbool.h>

bool isRunning;
void game_init();

bool game_isRunning();

void game_update();

/*
---Player Movement Direction---
1 - Down
2 - Up
3 - Right
4 - Left
*/
void game_playerAction(int action);
void game_loadMap(int mapNo);


void game_borders();

void drawUI_border()
#endif