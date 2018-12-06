/************************************************
Filename: MainMenu.c
Author: Muhammad Adam Bin Mohamad Amin
DP Email: m.muhammadadambin@digipen.edu
Course: GAM100
Brief Description:
Main Menu functions
*************************************************/

#include "Console.h"
#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include "MainMenu.h"
#include "GameStateManager.h"
#include "Options.h"
#include <conio.h>
#include <stdio.h>

bool staticDrawn;
short consoleWidth, consoleHeight;
char keyDown2, keyPress;

void options_Init()
{
	staticDrawn = false;
	consoleWidth = (short)console_getConsoleWidth();
	consoleHeight = (short)console_getConsoleHeight();
}

void options_DrawUIBox(short boxWidth, short boxHeight, short boxX, short boxY, char color)
{
	int i, j;

	console_draw(boxX, boxY, 201, color);
	console_draw(boxX + boxWidth - 1, boxY, 187, color);
	console_draw(boxX, boxY + boxHeight - 1, 200, color);
	console_draw(boxX + boxWidth - 1, boxY + boxHeight - 1, 188, color);

	for (i = 0; i < boxHeight; i++)
	{
		for (j = 0; j < boxWidth; j++)
		{
			if (i == 0 && (j != 0 && j != boxWidth - 1))
				console_draw(boxX + j, boxY + i, 205, color);

			if (j == 0 && (i != 0 && i != boxHeight - 1))
				console_draw(boxX + j, boxY + i, 186, color);

			if (i == boxHeight - 1 && (j != 0 && j != boxWidth - 1))
				console_draw(boxX + j, boxY + i, 205, color);

			if (j == boxWidth - 1 && (i != 0 && i != boxHeight - 1))
				console_draw(boxX + j, boxY + i, 186, color);

		}
	}

	mainMenu_draw(console_getConsoleWidth() / 2 - mainMenu_getOptions()->width / 2, (int)(console_getConsoleHeight() / 8 * 1.5), mainMenu_getOptions(), 15);
	console_drawString(console_getConsoleWidth() / 2 - 17, (int)(console_getConsoleHeight() / 8 * 7), "Press Escape to return to main menu", 15);
}

void options_Update()
{
	if (!staticDrawn)
	{
		options_DrawUIBox(consoleWidth / 10 * 6, consoleHeight / 10 * 8, consoleWidth / 2 - consoleWidth / 10 * 3, consoleHeight / 10, 15);

		staticDrawn = !staticDrawn;
	}

	keyDown2 = (char)_kbhit();
	if (keyDown2)
	{
		keyPress = (char)_getch();
		if (keyPress == 27)
		{
			console_clear();
			mainMenu_resetMainMenu();
			gsm_returnStateSystem()->next = state_mainMenu;
		}
	}
}