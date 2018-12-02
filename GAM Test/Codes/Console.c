
#include <windows.h>
#include <stdio.h>
#include <wincon.h>
#include <conio.h>
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

	SMALL_RECT windowSize = { 0, 0};
	windowSize.Right = (short)(width - 1);
	windowSize.Bottom = (short)(height - 1);

	SetConsoleWindowInfo(writeHandle, 1, &windowSize);

	SetConsoleActiveScreenBuffer(writeHandle);

	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(writeHandle, &cursorInfo);

	console_setFullScreen();

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
	COORD pos;
	pos.X = (short)x;
	pos.Y = (short)y;
	SetConsoleCursorPosition(writeHandle, pos);
}

void console_draw(int drawX, int drawY, char drawChar, char color)
{
	WORD textColor = 0;

	if (color > 7)
	{
		textColor += FOREGROUND_INTENSITY;
		color -= 8;
	}

	if (color % 2)
	{
		textColor += FOREGROUND_BLUE;
	}

	color /= 2;
	if (color % 2)
	{
		textColor += FOREGROUND_GREEN;
	}

	color /= 2;
	if (color % 2)
	{
		textColor += FOREGROUND_RED;
	}

	color /= 2;

	console_setCursorPosition(drawX, drawY);
	SetConsoleTextAttribute(writeHandle, textColor);
	printf_s("%c", drawChar);

	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(writeHandle, &cursorInfo);
}

void console_setColor(char color) 
{
	WORD textColor = 0;

	if (color > 7)
	{
		textColor += FOREGROUND_INTENSITY;
		color -= 8;
	}

	if (color % 2)
	{
		textColor += FOREGROUND_BLUE;
	}

	color /= 2;
	if (color % 2)
	{
		textColor += FOREGROUND_GREEN;
	}

	color /= 2;
	if (color % 2)
	{
		textColor += FOREGROUND_RED;
	}

	color /= 2;

	SetConsoleTextAttribute(writeHandle, textColor);
}

void console_drawString(int drawX, int drawY, char drawChar[], char color)
{

	WORD textColor = 0;

	if (color > 7)
	{
		textColor += FOREGROUND_INTENSITY;
		color -= 8;
	}

	if (color % 2)
	{
		textColor += FOREGROUND_BLUE;
	}

	color /= 2;
	if (color % 2)
	{
		textColor += FOREGROUND_GREEN;
	}

	color /= 2;
	if (color % 2)
	{
		textColor += FOREGROUND_RED;
	}

	color /= 2;

	SetConsoleTextAttribute(writeHandle, textColor);


	console_setCursorPosition(drawX, drawY);
	printf_s("%s", drawChar);

	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(writeHandle, &cursorInfo);

}


void console_clear()
{
	system("cls");
}
void console_setFullScreen()
{
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}