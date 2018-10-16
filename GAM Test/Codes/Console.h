
#ifndef GRAPHICS_H

#define GRAPHIC_H
#define CONSOLE_TITLE "Test Window"

void console_init();

int console_getConsoleWidth();
int console_getConsoleHeight();

void console_setCursorPosition(int x, int y);

void console_draw(int drawX, int drawY, int drawChar);
void console_clear();

#endif
