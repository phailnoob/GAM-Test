
#ifndef DATASTORAGE_H

#define DATASTORAGE_H
#include <stdbool.h>

void dataStorage_init();

void dataStorage_setPlayerPosition(int x, int y);
void dataStorage_getPlayerPosition(int *x, int *y);

void dataStorage_setFogDistance(int start, int end);
void dataStorage_getFogDistance(int *start, int *end);

void dataStorage_setMapData(char *arr, int width, int height);
void dataStorage_getMapData(int *width, int *height);
char dataStorage_getMapValue(int x, int y);
bool dataStorage_checkWall();

#endif
