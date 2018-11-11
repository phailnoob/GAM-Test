
#ifndef GRAPHICS_H

#define GRAPHIC_H
#define CONSOLE_TITLE "Test Window"

void console_init();

int console_getConsoleWidth();
int console_getConsoleHeight();

void console_setCursorPosition(int x, int y);

/*
---Color Chart---
Dark gray - 0
Bright red - 1
Bright green - 2
Bright yellow - 3
Bright blue - 4
Bright magenta - 5
Bright cyan - 6
White - 7
Black - 10
Dark red - 11
Dark green - 12
Dark yellow - 13
Dark blue - 14
Dark magenta - 15
Dark cyan - 16
Bright grey - 17
*/
void console_draw(char drawX, char drawY, char drawChar, char color);
void console_drawString(char drawX, char drawY, char drawChar[], char color);
void console_clear();
int console_getConsoleWidth();
int console_getConsoleHeight();

#endif
