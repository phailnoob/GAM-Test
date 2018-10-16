
#ifndef DATASTORAGE_H

#define DATASTORAGE_H
#include <stdbool.h>

void dataStorage_init();

void dataStorage_setPlayerPosition(int x, int y);
void dataStorage_getPlayerPosition(int *x, int *y);

void dataStorage_setFogDistance(int start, int end);
void dataStorage_getFogDistance(int *start, int *end);

void dataStorage_setMapData(int *arr, int width, int height);
void dataStorage_getMapSize(int *width, int *height);
bool dataStorage_checkWall();

void dataStorage_clearDraw(int drawOrder);
void dataStorage_draw(int drawOrder);

#endif
