
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

/*
return a pointer to the string inside the file
needs to end with a new line
string returned contains all the new lines
*/
char *game_readFile(char * fileName, int *fileWidth, int *fileHeight);

void game_RestartCurrentMap();

void drawUI_border();

#endif
