
#ifndef ARRAYREADER_H

#define ARRAYREADER_H

#include <stdbool.h>

void arrayReader_init();

void arrayReader_setMap(int size);
int arrayReader_checkDistance(int x1, int y1, int x2, int y2);
void arrayReader_draw();

void arrayReader_setInitialDraw(bool someBool);

void arrayReader_Destructor();
#endif