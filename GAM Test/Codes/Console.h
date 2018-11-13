
#ifndef GRAPHICS_H

#define GRAPHIC_H
#define CONSOLE_TITLE "Test Window"

void console_init();

int console_getConsoleWidth();
int console_getConsoleHeight();

void console_setCursorPosition(int x, int y);

/*
---Color Chart---
00 - Black
01 - Dark blue
02 - Dark green
03 - Dark cyan
04 - Dark red
05 - Dark magenta
06 - Dark yellow
07 - Bright grey
08 - Dark gray
09 - Bright blue
10 - Bright green
11 - Bright cyan
12 - Bright red
13 - Bright magenta
14 - Bright yellow
15 - White
*/
void console_draw(char drawX, char drawY, char drawChar, char color);
void console_drawString(char drawX, char drawY, char drawChar[], char color);
void console_clear();
int console_getConsoleWidth();
int console_getConsoleHeight();

#endif
