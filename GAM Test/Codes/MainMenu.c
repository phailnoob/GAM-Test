/************************************************
Filename: MainMenu.c
Author: Muhammad Adam Bin Mohamad Amin
DP Email: m.muhammadadambin@digipen.edu
Course: GAM100

Brief Description:
Main Menu functions
*************************************************/
#include "Game.h"
#include "Console.h"
#include <windows.h>
#include <stdio.h>
#include "MainMenu.h"
#include <stdbool.h>
#include "GameStateManager.h"


char selected = 1;
int keyPress, keyDown;
bool keyPressed = false;
bool logoDrawn = 0;

bool wasDrawn[4] = { 0,0,0,0 };

AsciiChar logo,play,options,credits,exit1,kenny;


/*Reset main menu variables*/
void mainMenu_Reset()
{
	logoDrawn = 0;
}

void mainMenu_Init()
{
	logo.width= logo.height = play.width = options.width = credits.height = kenny.height = 0;
	exit1.width = credits.width = play.height = options.height = exit1.height = kenny.width = 0;

	logo.string = game_readFile("Assets/Logo.txt",&(logo.width), &(logo.height));
	play.string = game_readFile("Assets/Play.txt", &(play.width), &(play.height));
	options.string = game_readFile("Assets/Options.txt", &(options.width), &(options.height));
	credits.string = game_readFile("Assets/Credits.txt", &(credits.width), &(credits.height));
	exit1.string = game_readFile("Assets/Exit.txt", &(exit1.width), &(exit1.height));
	kenny.string = game_readFile("Assets/kenny.txt", &(kenny.width), &(kenny.height));
}

/*Handles arrow keys input*/
void mainMenu_arrow(int key,bool * keyPressed)
{
	switch(key)
	{
		case 72:
			if (selected == 1)
			{
				selected = 4;
			}
			else
			{
				selected--;
			}
			*keyPressed = false;
			break;
		case 80:
			if (selected == 4)
			{
				selected = 1;
			}
			else
			{
				selected++;
			}
			*keyPressed = false;
			break;
		case 0:
			switch (selected)
			{
			case 1:/*Changes state to Game*/
				gsm_setNextState(state_Game);
				mainMenu_Reset();
				system("cls");
				break;
			case 2:/*Changes state to Options*/
				/*gsm_setNextState(state_Options);
				mainMenu_Reset();
				system("cls");
				REMEMBER TO CHANGE THE COLOR THANKS FUTURE BABY*/
				break;
			case 3:/*Changes state to Credits*/
				break;
			case 4:/*Changes state to Exit*/
				gsm_setNextState(state_Exit);
				break;
			}
			break;
	};
}

/*Gets in raw keyboard input*/
void mainMenu_checkInput()
{
	keyPress = _getch();
	keyDown = _kbhit();

	if (keyDown)
	{
		keyPressed = true;
	}
	else
	{
		if (keyPressed)
			mainMenu_arrow(keyPress, &keyPressed);
	}
}


void mainMenu_draw(int x, int y, AsciiChar * image, char color)
{
	int j, i;
	for (i = 0; i < image->height-1; i++)
	{
		for (j = 0; j < image->width; j++)
		{
			if (*(image->string + (i * (image->width + 1)) + j) != '\n')
			{
				console_draw(x  + j, y + i, *(image->string + (i * (1 + image->width)) + j), color);
			}
		}
	}
}


/*Draws main menu buttons*/
void mainMenu_drawButtons()
{
	int i;
	if (selected == 1)
		wasDrawn[0] = 0;
	if (wasDrawn[0] == 0)
		mainMenu_draw(console_getConsoleWidth() / 12, console_getConsoleHeight() / 8 * 4, &play , selected == 1 ? 14 : 3);
	wasDrawn[0] = 1;
	if (selected == 1)
		wasDrawn[0] = 0;

	
	if (selected == 2)
		wasDrawn[1] = 0;
	if (wasDrawn[1] == 0)
		mainMenu_draw(console_getConsoleWidth() / 12, console_getConsoleHeight() / 8 * 5, &options, selected == 2 ? 8 : 3);
	wasDrawn[1] = 1;
	if (selected == 2)
		wasDrawn[1] = 0;


	if (selected == 3)
		wasDrawn[2] = 0;
	if (wasDrawn[2] == 0)
		mainMenu_draw(console_getConsoleWidth() / 12, console_getConsoleHeight() / 8 * 6, &credits, selected == 3 ? 8 : 3);
	wasDrawn[2] = 1;
	if (selected == 3)
		wasDrawn[2] = 0;

	
	if (selected == 4)
		wasDrawn[3] = 0;
	if (wasDrawn[3] == 0)
		mainMenu_draw(console_getConsoleWidth() / 12, console_getConsoleHeight() /  8 * 7, &exit1, selected == 4 ? 14 : 3);
	wasDrawn[3] = 1;
	if (selected == 4)
		wasDrawn[3] = 0;

}





/*Handles main menu updates. Only call this outside of this function*/
void mainMenu_Update()
{
	if (!logoDrawn)
	{
		mainMenu_draw(console_getConsoleWidth()/2 - logo.width / 2,console_getConsoleHeight()/10,&logo,15);
		mainMenu_draw(console_getConsoleWidth() / 4 * 3 - kenny.width / 2, console_getConsoleHeight() / 2 -3, &kenny, 15);
		logoDrawn = 1;
	}
	mainMenu_drawButtons();
	mainMenu_checkInput();

}

void mainMenu_resetMainMenu()
{
	wasDrawn[0] = 0;
	wasDrawn[1] = 0;
	wasDrawn[2] = 0;
	wasDrawn[3] = 0;
}
