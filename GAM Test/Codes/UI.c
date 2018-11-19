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

const char *UI_traps[3] = {
                            {"/<^>\\"},
	                        {"|>|<|"},
                           {"\\<v>/"}
};

bool torchDrawn[5] = { 0,0,0,0,0 };
bool trapDrawn[5] = { 0,0,0,0,0 };
bool UIdrawn = false;
bool bordersDrawn = false;

/******************************************************************************
   Function: gameborders()

Description: Prints borders for the game.

     Inputs: None.         
    Outputs: None.
******************************************************************************/
void game_borders()
{
	if (bordersDrawn == false)
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

		bordersDrawn = true;
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
	if (UIdrawn == false)
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

		console_setCursorPosition(2, 2);
		printf("Torches:");
	
		console_setCursorPosition(2, 11);
		printf("Traps:");

		UIdrawn = true;
	}
	
}








/******************************************************************************
   Function: check_Active_Torch

Description: This function currently only checks that a torch has been placed
              down and greys out the inventory slot accordingly.
          
	Inputs:  None
    Outputs: None
******************************************************************************/
//int check_Active_Torch()
//{
//	int i = 0, j = 0;
//	/*grey out torch for every torch placed*/
//	int UI_torch_pos = 2;
//	for (i = 0; i < 5; i++)
//	{
//		if (dataStorage_getTorchObj(i)->active)
//		{
//			
//			for (j = 0; j < 3; j++)
//			{
//				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8, sizeof(UI_torch - 1));
//			}
//			UI_torch_pos -= 5;
//		}
//
//	}
//}

/*if bool is false then draw, after draw change to 1*/
/******************************************************************************
   Function: UI_drawtorches

Description: Initializes the default UI element (i.e 5 torches)
          
	Inputs: None
    Outputs: None.
******************************************************************************/
//void UI_drawtorches()
//{
//	int i,j;
//	int UI_torch_pos = 2;
//	console_setCursorPosition(2, 2);
//		printf("Torches:");
//
//		
//		/*Initialize drawing all 5 torches*/
//		for (i = 0; i < 5; i++)
//		{
//			for (j = 0; j < 3; j++)
//			{
//				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12, sizeof(UI_torch - 1));
//			}
//			UI_torch_pos += 5;
//		}
//
//
//		check_Active_Torch();
//}



void UI_draw_torches()
{
	int torch_inv= 0;
	int UI_torch_pos;
	int j;

	torch_inv = dataStorage_torch_counter();

	UI_torch_pos = 2;

		if (torch_inv == 5)
		{
			int i, j;
			int UI_torch_pos = 2;
			
			/*Draw all 5 torches (Greyed Out)*/
			UI_torch_pos = 2;
			/*5th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;

			/*4th grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;

			/*3rd grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;

			/*2nd grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;

			/*1st grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8, sizeof(UI_torch - 1));
			}
		}

		if(torch_inv == 4)
		{

			UI_torch_pos = 2;
			/*5th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;

			/*4th grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;

			/*3rd grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;

			/*2nd grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;

			/*1st grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8, sizeof(UI_torch - 1));
			}
		}

		if(torch_inv == 3)
		{
			UI_torch_pos = 2;
			/*5th red */
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;

			/*4th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;
			 /*3rd grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;
			
			/*2nd grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;
			
			/*1st grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8, sizeof(UI_torch - 1));
			}
		}

		if (torch_inv == 2)
		{
			UI_torch_pos = 2;
			/*5th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;

			/*4th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;
			/*3rd red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;

			/*2nd grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;

			/*1st grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8, sizeof(UI_torch - 1));
			}
		}

		if (torch_inv == 1)
		{
			UI_torch_pos = 2;
			/*5th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;

			/*4th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;
			/*3rd red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;

			/*2nd red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;

			/*1st grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8, sizeof(UI_torch - 1));
			}
		}

		if (torch_inv == 0)
		{
			UI_torch_pos = 2;
			/*5th red*/

			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;

			/*4th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12, sizeof(UI_torch - 1));
			}
			UI_torch_pos += 5;
			/*3rd red*/
			if(torchDrawn[2]==0)
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12, sizeof(UI_torch - 1));
			}
		
			UI_torch_pos += 5;

			
			/*2nd red*/
			if (torchDrawn[1] == 0)
			{
				for (j = 0; j < 3; j++)
				{
					console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12, sizeof(UI_torch - 1));
				}
				torchDrawn[1] = 1;
		
			}

			UI_torch_pos += 5;
			/*1st red*/
			if (torchDrawn[0] == 0)
			{
				for (j = 0; j < 3; j++)
				{
					console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12, sizeof(UI_torch - 1));
				}
				torchDrawn[0] = 1;
			}
		}


}

void UI_draw_traps()
{
	int traps_inv = 0;
	int UI_trap_pos;
	int j;

	traps_inv = dataStorage_trap_counter();


	if (traps_inv == 5)
	{

		UI_trap_pos = 2;
		/*5th red*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 8, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;

		/*4th grey*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 8, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;

		/*3rd grey*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 8, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;

		/*2nd grey*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 8, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;

		/*1st grey*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 8, sizeof(UI_traps - 1));
		}

	}

	if (traps_inv == 4)
	{

		UI_trap_pos = 2;
		/*5th red*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 12, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;

		/*4th grey*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 8, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;

		/*3rd grey*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 8, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;

		/*2nd grey*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 8, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;

		/*1st grey*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 8, sizeof(UI_traps - 1));
		}
	}

	if (traps_inv == 3)
	{
		UI_trap_pos = 2;
		/*5th red */
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 12, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;

		/*4th red*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 12, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;
		/*3rd grey*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 8, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;

		/*2nd grey*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 8, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;

		/*1st grey*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 8, sizeof(UI_traps - 1));
		}
	}

	if (traps_inv == 2)
	{
		UI_trap_pos = 2;
		/*5th red*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 12, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;

		/*4th red*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 12, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;
		/*3rd red*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 12, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;

		/*2nd grey*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 8, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;

		/*1st grey*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 8, sizeof(UI_traps - 1));
		}
	}

	if (traps_inv == 1)
	{
		UI_trap_pos = 2;
		/*5th red*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 12, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;

		/*4th red*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 12, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;
		/*3rd red*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 12, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;

		/*2nd red*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 12, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;

		/*1st grey*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 8, sizeof(UI_traps - 1));
		}
	}

	if (traps_inv == 0)
	{
		UI_trap_pos = 2;
		/*5th red*/

		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 12, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;

		/*4th red*/
		for (j = 0; j < 3; j++)
		{
			console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 12, sizeof(UI_traps - 1));
		}
		UI_trap_pos += 5;
		/*3rd red*/
		if (trapDrawn[2] == 0)
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 12, sizeof(UI_traps - 1));
			}

		UI_trap_pos += 5;


		/*2nd red*/
		if (trapDrawn[1] == 0)
		{
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 12, sizeof(UI_traps - 1));
			}
			trapDrawn[1] = 1;

		}

		UI_trap_pos += 5;
		/*1st red*/
		if (trapDrawn[0] == 0)
		{
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 12 + j, UI_traps[j], 12, sizeof(UI_traps - 1));
			}
			trapDrawn[0] = 1;
		}
	}


}
