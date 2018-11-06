
#include <windows.h>
#include <stdio.h>
#include "Console.h"
#include "SpriteReference.h"

static HANDLE writeHandle, readHandle;
CONSOLE_CURSOR_INFO cursorInfo;
int width, height;
char buffer[100][250];

void console_init()
{
	SetConsoleTitle(TEXT(CONSOLE_TITLE));

	writeHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	readHandle = GetStdHandle(STD_INPUT_HANDLE);
	
	COORD bufferSize = GetLargestConsoleWindowSize(writeHandle);
	width = bufferSize.X;
	height = bufferSize.Y;

	/*
	Setting Console Window size to the size of the monitor (largest possible size)
	*/

	SetConsoleScreenBufferSize(writeHandle, bufferSize);

	SMALL_RECT windowSize = { 0, 0, width - 1, height - 1 };

	SetConsoleWindowInfo(writeHandle, 1, &windowSize);

	SetConsoleActiveScreenBuffer(writeHandle);

	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(writeHandle, &cursorInfo);

	console_clear();
}

int console_getConsoleWidth()
{
	return width;
}

int console_getConsoleHeight()
{
	return height;
}

void console_setCursorPosition(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(writeHandle, pos);
}

void console_draw(char drawX, char drawY, char drawChar, char color)
{
	console_setCursorPosition(drawX, drawY);
	printf_s("\u001b[3%d;%dm%c", color%10, color/10 + 1, drawChar);

	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(writeHandle, &cursorInfo);
}

void console_clear()
{
	system("cls");
}