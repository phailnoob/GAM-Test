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
#include "Options.h"

bool staticDrawn;
short consoleWidth, consoleHeight;



void options_Init()
{
	staticDrawn = false;
	consoleWidth = (short)console_getConsoleWidth();
	consoleHeight = (short)console_getConsoleHeight();
}

void options_DrawUIBox(short boxWidth,short boxHeight,short boxX,short boxY,char color)
{
	int i,j;

	console_draw(boxX, boxY, 201, color);
	console_draw(boxX+boxWidth-1, boxY, 187, color);
	console_draw(boxX, boxY+boxHeight-1, 200, color);
	console_draw(boxX + boxWidth - 1, boxY + boxHeight -1, 188, color);

	for (i = 0; i < boxHeight; i++)
	{
		for (j = 0; j < boxWidth; j++)
		{
			if (i == 0 && (j != 0 && j != boxWidth-1))
				console_draw(boxX + j, boxY + i, 205, color);

			if (j == 0 && (i != 0 && i != boxHeight-1))
				console_draw(boxX + j, boxY + i, 186, color);

			if (i == boxHeight-1 && (j != 0 && j != boxWidth-1))
				console_draw(boxX + j, boxY + i, 205, color);

			if (j == boxWidth-1 && (i != 0 && i != boxHeight-1))
				console_draw(boxX + j, boxY + i, 186, color);

		}
	}

	
}















void options_Update()
{
	if (!staticDrawn)
	{
		options_DrawUIBox(consoleWidth / 10 * 8, consoleHeight / 10 * 8, consoleWidth / 10, consoleHeight / 10, 9);



		staticDrawn = !staticDrawn;
	}
}












































