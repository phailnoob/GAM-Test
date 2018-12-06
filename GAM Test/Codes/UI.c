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
#include <stdio.h>

char *UI_torch[3] = {
							{ " \\**/"},
							{ "  || " },
							{ "  || " }
};

char *UI_traps[3] = {
                            {"<^>"},
	                        {">|<"},
                           {"<v>"}
};

char *UI_Lives[4] = {
						{" _    _  "},
						{"( `\\/' ) "},
						{" \\    /' "},
						{"  `\\/'   "}
};
char mission[] = { "Find the Exit!" };
char mission2[] = { "But beware of monsters..." };

bool skullsDrawn = false;
bool torchDrawn = false;
bool trapDrawn = false;
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
	console_setColor(7);
	if (bordersDrawn == false)
	{
		int j;

		

		/*top border*/
		console_setCursorPosition(1, 1);
		for (j = 0; j < console_getConsoleWidth() ; j++)
			printf("%c", 205);

		/*Bottom border*/
		console_setCursorPosition(0, console_getConsoleHeight()-2);
		for (j = 0; j <= console_getConsoleWidth()-1; j++)
			printf("%c", 205);

		/*Left and right border*/
		for (j = 2; j < console_getConsoleHeight()  - 2; j++)
		{
			console_setCursorPosition(0, j);
			printf("%c", 186);

			console_setCursorPosition(console_getConsoleWidth() -1, j);
			printf("%c", 186);
		}

		/*corners*/
		console_setCursorPosition(0, 1);
		printf("%c", 201);
		console_setCursorPosition(0, console_getConsoleHeight() - 2);
		printf("%c", 200);
		console_setCursorPosition(console_getConsoleWidth()-1, 1);
		printf("%c", 187);
		console_setCursorPosition(console_getConsoleWidth() - 1, console_getConsoleHeight() - 2);
		printf("%c", 188);
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
		i = console_getConsoleHeight();
		for (j = 0; j < (i - 4); j++)
		{
			console_setCursorPosition(30, 2 + j);
			printf("%c", 186);
		}

		console_drawString(15 - (sizeof(mission) - 1)/2, console_getConsoleHeight() / 2-9, mission, 15);
		console_drawString(15 - (sizeof(mission2) - 1)/2, console_getConsoleHeight() / 2+1-9, mission2, 15);

		console_setCursorPosition(1, 20);
		for (j = 0; j < 29; j++)
			printf("%c", 205);

		console_setCursorPosition(30, 20);
			printf("%c", 185);

		console_setCursorPosition(2, 2);
		printf("Torches:");
	
		console_setCursorPosition(console_getConsoleWidth() - 28, 2);
		printf("Traps:");

		UIdrawn = true;
	}
	
}









/******************************************************************************
   Function: UI_drawtorches

Description: Initializes the default UI element and draws torches accordingly.
          
	Inputs: None
    Outputs: None.
******************************************************************************/


void UI_draw_torches()
{
	int torch_inv= 0;
	int UI_torch_pos;

	torch_inv = dataStorage_torch_counter();

	UI_torch_pos = 2;

	if (!torchDrawn)
	{
		int j;
		if (torch_inv == 5)
		{
			UI_torch_pos = 2;

			/*Draw all 5 torches (Greyed Out)*/
			UI_torch_pos = 2;
			/*5th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8);
			}
			UI_torch_pos += 5;

			/*4th grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8);
			}
			UI_torch_pos += 5;

			/*3rd grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8);
			}
			UI_torch_pos += 5;

			/*2nd grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8);
			}
			UI_torch_pos += 5;

			/*1st grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8);
			}
		}

		if (torch_inv == 4)
		{

			UI_torch_pos = 2;
			/*5th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12);
			}
			UI_torch_pos += 5;

			/*4th grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8);
			}
			UI_torch_pos += 5;

			/*3rd grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8);
			}
			UI_torch_pos += 5;

			/*2nd grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8);
			}
			UI_torch_pos += 5;

			/*1st grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8);
			}
		}

		if (torch_inv == 3)
		{
			UI_torch_pos = 2;
			/*5th red */
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12);
			}
			UI_torch_pos += 5;

			/*4th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12);
			}
			UI_torch_pos += 5;
			/*3rd grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8);
			}
			UI_torch_pos += 5;

			/*2nd grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8);
			}
			UI_torch_pos += 5;

			/*1st grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8);
			}
		}

		if (torch_inv == 2)
		{
			UI_torch_pos = 2;
			/*5th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12);
			}
			UI_torch_pos += 5;

			/*4th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12);
			}
			UI_torch_pos += 5;
			/*3rd red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12);
			}
			UI_torch_pos += 5;

			/*2nd grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8);
			}
			UI_torch_pos += 5;

			/*1st grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8);
			}
		}

		if (torch_inv == 1)
		{
			UI_torch_pos = 2;
			/*5th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12);
			}
			UI_torch_pos += 5;

			/*4th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12);
			}
			UI_torch_pos += 5;
			/*3rd red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12);
			}
			UI_torch_pos += 5;

			/*2nd red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12);
			}
			UI_torch_pos += 5;

			/*1st grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 8);
			}
		}

		if (torch_inv == 0)
		{
			UI_torch_pos = 2;
			/*5th red*/

			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12);
			}
			UI_torch_pos += 5;

			/*4th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12);
			}
			UI_torch_pos += 5;
			/*3rd red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12);
			}

			UI_torch_pos += 5;


			/*2nd red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12);
			}


			UI_torch_pos += 5;
			/*1st red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_torch_pos, 4 + j, UI_torch[j], 12);
			}
		}
		torchDrawn = 1;
	}

}


void UI_draw_ResetTorchDrawn()
{
	torchDrawn = 0;
}
void UI_draw_ResetTrapDrawn()
{
	trapDrawn = 0;
}

void UI_drawSkulls()
{
	if (!skullsDrawn)
	{
		char lives = *dataStorage_getLives();
		int x = console_getConsoleWidth(), y = console_getConsoleHeight();

		console_drawString(10, console_getConsoleHeight() / 2 - 3,"Lives left",15);
		console_setCursorPosition(10, console_getConsoleHeight() / 2 - 2);
		for (char j = 0; j < 10; j++)
			printf("%c", 205);

		if (lives >= 0)
		{
			for (int i = 0; i < 5; i++)
			{
				if (i < lives)
				{
					for (int e = 0; e < 4; e++)
						console_drawString(x / 20 - 1, y / 2 + 5 * i + e - 2 + 4, UI_Lives[e], 10);
				}
				else
				{
					for (int e = 0; e < 4; e++)
						console_drawString(x / 20 - 1, y / 2 + 5 * i + e - 2 + 4, UI_Lives[e], 12);
				}
			}
		}
		skullsDrawn = !skullsDrawn;
	}
}

void UI_redrawSkulls()
{
	skullsDrawn = false;
}

void UI_draw_traps()
{
	int traps_inv = 0;
	int UI_trap_pos;
	int j;

	traps_inv = dataStorage_trap_counter();

	if (!trapDrawn)
	{
		if (traps_inv == 5)
		{

			UI_trap_pos = console_getConsoleWidth()-27;
			/*5th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 8);
			}
			UI_trap_pos += 5;

			/*4th grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 8);
			}
			UI_trap_pos += 5;

			/*3rd grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 8);
			}
			UI_trap_pos += 5;

			/*2nd grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 8);
			}
			UI_trap_pos += 5;

			/*1st grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 8);
			}

		}

		if (traps_inv == 4)
		{

			UI_trap_pos = console_getConsoleWidth() -27;
			/*5th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 12);
			}
			UI_trap_pos += 5;

			/*4th grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 8);
			}
			UI_trap_pos += 5;

			/*3rd grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 8);
			}
			UI_trap_pos += 5;

			/*2nd grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 8);
			}
			UI_trap_pos += 5;

			/*1st grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 8);
			}
		}

		if (traps_inv == 3)
		{
			UI_trap_pos = console_getConsoleWidth() - 27;
			/*5th red */
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 12);
			}
			UI_trap_pos += 5;

			/*4th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 12);
			}
			UI_trap_pos += 5;
			/*3rd grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 8);
			}
			UI_trap_pos += 5;

			/*2nd grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 8);
			}
			UI_trap_pos += 5;

			/*1st grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 8);
			}
		}

		if (traps_inv == 2)
		{
			UI_trap_pos = console_getConsoleWidth() - 27;
			/*5th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 12);
			}
			UI_trap_pos += 5;

			/*4th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 12);
			}
			UI_trap_pos += 5;
			/*3rd red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 12);
			}
			UI_trap_pos += 5;

			/*2nd grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 8);
			}
			UI_trap_pos += 5;

			/*1st grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 8);
			}
		}

		if (traps_inv == 1)
		{
			UI_trap_pos = console_getConsoleWidth() - 27;
			/*5th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 12);
			}
			UI_trap_pos += 5;

			/*4th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 12);
			}
			UI_trap_pos += 5;
			/*3rd red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 12);
			}
			UI_trap_pos += 5;

			/*2nd red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 12);
			}
			UI_trap_pos += 5;

			/*1st grey*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 8);
			}
		}

		if (traps_inv == 0)
		{
			UI_trap_pos = console_getConsoleWidth()-27;
			/*5th red*/

			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 12);
			}
			UI_trap_pos += 5;

			/*4th red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 12);
			}
			UI_trap_pos += 5;
			/*3rd red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 12);
			}

			UI_trap_pos += 5;


			/*2nd red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 12);
			}

			UI_trap_pos += 5;
			/*1st red*/
			for (j = 0; j < 3; j++)
			{
				console_drawString(UI_trap_pos, 4 + j, UI_traps[j], 12);
			}
		}

		trapDrawn = true;
	}


}

void UI_clearDraw()
{
	UIdrawn = bordersDrawn = trapDrawn = torchDrawn = skullsDrawn = false;
}
