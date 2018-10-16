
#include <windows.h>
#include <stdio.h>
#include "Console.h"
#include "SpriteReference.h"

static HANDLE writeHandle0, writeHandle1, readHandle;
CONSOLE_CURSOR_INFO cursorInfo;
int width, height;
char buffer[100][250];

void console_init()
{
	SetConsoleTitle(TEXT(CONSOLE_TITLE));

	writeHandle0 = GetStdHandle(STD_OUTPUT_HANDLE);
	writeHandle1 = GetStdHandle(STD_OUTPUT_HANDLE);
	readHandle = GetStdHandle(STD_INPUT_HANDLE);
	
	COORD bufferSize = GetLargestConsoleWindowSize(writeHandle0);
	width = bufferSize.X;
	height = bufferSize.Y;

	/*
	Setting Console Window size to the size of the monitor (largest possible size)
	*/

	SetConsoleScreenBufferSize(writeHandle0, bufferSize);
	SetConsoleScreenBufferSize(writeHandle1, bufferSize);

	SMALL_RECT windowSize = { 0, 0, width - 1, height - 1 };

	SetConsoleWindowInfo(writeHandle0, 1, &windowSize);
	SetConsoleWindowInfo(writeHandle1, 1, &windowSize);

	SetConsoleActiveScreenBuffer(writeHandle0);

	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(writeHandle0, &cursorInfo);

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
	SetConsoleCursorPosition(writeHandle0, pos);
}

void console_draw(int drawX, int drawY, int drawChar)
{
	console_setCursorPosition(drawX, drawY);
	printf_s("%c", drawChar);

/*	char ch = (char)drawChar;
	COORD size = { width, height };
	COORD pos = { drawX, drawY };
	SMALL_RECT rect = { 0, 0, width-1, height-1 };
	WriteConsoleOutput(writeHandle0, ch, size, pos, &rect);
*/
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(writeHandle0, &cursorInfo);
}

void console_clear()
{
	system("cls");
}