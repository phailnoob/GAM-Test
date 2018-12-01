#pragma once

#include "Data Storage.h"
void mainMenu_Update();
void mainMenu_resetMainMenu();
void mainMenu_draw(int x, int y, AsciiChar * image, char color);
AsciiChar* mainMenu_getOptions();
AsciiChar* mainMenu_getCredits();
