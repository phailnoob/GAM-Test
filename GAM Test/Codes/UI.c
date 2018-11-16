/******************************************************************************
filename    UI.c
author      Marcus Koh Joon Yee
DP email    k.joonyeemarcus@digipen.edu
course      GAM -100B
assignment  3

Brief Description:
  This file contains the function definitions for the printing of the game's
  borders and one simple element displaying the game's torch inventory
******************************************************************************/
#include "UI.h"
#include "Console.h"
#include "Data Storage.h"

const char *UI_torch[3] = {
							{ " \\**/"},
							{ "  || " },
							{ "  || " }
};


/******************************************************************************
   Function: gameborders()

Description: Prints borders for the game.

     Inputs: None.         
    Outputs: None.
******************************************************************************/
void game_borders()
{

	int j;

	/*corners*/
	console_setCursorPosition(0, 1);
	printf("%c", 201);
	console_setCursorPosition(0, console_getConsoleHeight() / 10 * 9);
	printf("%c", 200);
	console_setCursorPosition(console_getConsoleWidth() / 10 * 9, 1);
	printf("%c", 187);
	console_setCursorPosition(console_getConsoleWidth() / 10 * 9, console_getConsoleHeight() / 10 * 9);
	printf("%c", 188);

	/*top border*/
	console_setCursorPosition(1, 1);
	for (j = 0; j < console_getConsoleWidth() / 10 * 9 - 1; j++)
		printf("%c", 205);

	/*Bottom border*/
	console_setCursorPosition(1, console_getConsoleHeight() / 10 * 9);
	for (j = 0; j <= console_getConsoleWidth() / 10 * 9 - 2; j++)
		printf("%c", 205);

	/*Left and right border*/
	for (j = 0; j < console_getConsoleHeight() / 10 * 9 - 2; j++)
	{
		console_setCursorPosition(0, 2 + j);
		printf("%c", 186);

		console_setCursorPosition(console_getConsoleWidth() / 10 * 9, 2 + j);
		printf("%c", 186);
	}

}


/******************************************************************************
   Function: drawUI

Description: Draws the UI border to seperate UI from the game space.
          
	Inputs: None
    Outputs: None.
******************************************************************************/
void drawUI()
{
	int i, j;
	i = console_getConsoleHeight() / 10 * 9;
	for (j = 0; j < (i - 2); j++)
	{
		console_setCursorPosition(30, 2 + j);
		printf("%c", 186);
	}

	console_setCursorPosition(1, 20);
	for (j = 0; j < 29; j++)
		printf("%c", 205);

}








/******************************************************************************
   Function: check_Active_Torch

Description: This function currently only checks that a torch has been placed
              down and greys out the inventory slot accordingly.
          
	Inputs:  None
    Outputs: None
******************************************************************************/
int check_Active_Torch()
{
	int i = 0, j = 0;
	/*grey out torch for every torch placed*/
	int UI_torch_pos = 22;
	for (i = 0; i < 5; i++)
	{
		if (dataStorage_getTorchObj(i)->active)
		{
			
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8, sizeof(UI_torch - 1));
			}
			UI_torch_pos -= 5;
		}

	}
}


/******************************************************************************
   Function: UI_drawtorches

Description: Initializes the default UI element (i.e 5 torches)
          
	Inputs: None
    Outputs: None.
******************************************************************************/
void UI_drawtorches()
{
	int i,j;
	int UI_torch_pos = 2;
	console_setCursorPosition(2, 2);
		printf("Torches:");


		/*Initialize drawing all 5 torches*/
		for (i = 0; i < 5; i++)
		{
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;
		}


		check_Active_Torch();
}


