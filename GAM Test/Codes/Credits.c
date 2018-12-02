
#include "Credits.h"
#include "Console.h"
#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "MainMenu.h"
#include "Game.h"
#include <conio.h>
#include "GameStateManager.h"

bool staticDrawn,faceDrawn;
short consoleWidth, consoleHeight;
int keyDown, keyPress,selected;

clock_t begin;
double time_spent, prevTime, timeLapse;

AsciiChar adam, kailiang, edwin, marcus,clear;
char* adamName, *kailiangName, *edwinName, *marcusName;
char* adamJob, *kailiangJob, *edwinJob, *marcusJob;



void credits_Init()
{
	staticDrawn = false;
	consoleWidth = (short)console_getConsoleWidth();
	consoleHeight = (short)console_getConsoleHeight();

	adamName = "Adam Amin";
	kailiangName = "Toh Kai Liang";
	edwinName = "Edwin Khoo";
	marcusName = "Marcus Koh";
	adamJob = "Producer & AI Engineer";
	kailiangJob = "Gameplay Programmer";
	edwinJob = "Lead Engine Developer";
	marcusJob = "UI & SFX Engineer";

	selected = 1;
	faceDrawn = 0;
	begin = clock();
	timeLapse = 2;
	time_spent = prevTime = (double)(clock() - begin) / CLOCKS_PER_SEC;


	adam.width = adam.height = marcus.width = kailiang.width = marcus.height = kailiang.height = 0;
	edwin.width = edwin.height = clear.width = clear.height = 0;

	adam.string = game_readFile("Assets/adam.txt", &(adam.width), &(adam.height));
	marcus.string = game_readFile("Assets/marcus.txt", &(marcus.width), &(marcus.height));
	edwin.string = game_readFile("Assets/edwin.txt", &(edwin.width), &(edwin.height));
	kailiang.string = game_readFile("Assets/kailiang.txt", &(kailiang.width), &(kailiang.height));
	clear.string = game_readFile("Assets/clear.txt", &(clear.width), &(clear.height));

}

void credits_DrawUIBox(short boxWidth, short boxHeight, short boxX, short boxY, char color)
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

	mainMenu_draw(console_getConsoleWidth() / 2 - mainMenu_getCredits()->width / 2, (int)(console_getConsoleHeight() / 8 * 1.5), mainMenu_getCredits(), 15);
	console_drawString(console_getConsoleWidth() / 2 - 17, (int)(console_getConsoleHeight() / 8 * 7), "Press Escape to return to main menu", 15);
}
void credits_draw(int x, int y, AsciiChar * image, char color)
{
	int j, i;
	for (i = 0; i < image->height - 1; i++)
	{
		for (j = 0; j < image->width; j++)
		{
			if (*(image->string + (i * (image->width + 1)) + j) != '\n')
			{
				console_draw(x + j, y + i, *(image->string + (i * (1 + image->width)) + j), color);
			}
		}
	}
}


void credits_slideShow()
{
	time_spent = (double)(clock() - begin - prevTime) / CLOCKS_PER_SEC;
	
	if (time_spent - prevTime >= timeLapse)
	{
		if (selected < 4)
		{
			selected++;
		}
		else
		{
			selected = 1;
		}
		faceDrawn = 0;
		prevTime = time_spent;
		staticDrawn = 0;
		credits_draw(consoleWidth / 10 * 4, consoleHeight / 10 * 4, &clear, 15);
	}
}
void credits_Update()
{
	credits_slideShow();
	if (!staticDrawn)
	{
		credits_DrawUIBox(consoleWidth / 10 *9, consoleHeight / 10 * 8, consoleWidth / 20 , consoleHeight / 10, 15);

		staticDrawn = !staticDrawn;
	}

	if (!faceDrawn)
	{
		switch (selected)
		{
		case 1:
			credits_draw(consoleWidth / 10 * 4, consoleHeight / 10 * 4, &adam, 15);
			console_drawString(consoleWidth / 2 - (int)strlen(adamName)/2, consoleHeight / 10 * 7, adamName, 14);
			console_drawString(consoleWidth / 2 - (int)strlen(adamJob) / 2, consoleHeight / 10 * 7+1, adamJob, 14);
			break;
		case 2:
			credits_draw(consoleWidth / 10 * 4, consoleHeight / 10 * 4, &edwin, 15);
			console_drawString(consoleWidth / 2 - (int)strlen(edwinName) / 2, consoleHeight / 10 * 7, edwinName, 14);
			console_drawString(consoleWidth / 2 - (int)strlen(edwinJob) / 2, consoleHeight / 10 * 7 + 1, edwinJob, 14);
			break;
		case 3:
			credits_draw(consoleWidth / 10 * 4, consoleHeight / 10 * 4, &marcus, 15);
			console_drawString(consoleWidth / 2 - (int)strlen(marcusName) / 2, consoleHeight / 10 * 7, marcusName, 14);
			console_drawString(consoleWidth / 2 - (int)strlen(marcusJob) / 2, consoleHeight / 10 * 7 + 1, marcusJob, 14);
			break;
		case 4:
			credits_draw(consoleWidth / 10 * 4, consoleHeight / 10 * 4, &kailiang, 15);
			console_drawString(consoleWidth / 2 - (int)strlen(kailiangName) / 2, consoleHeight / 10 * 7, kailiangName, 14);
			console_drawString(consoleWidth / 2 - (int)strlen(kailiangJob) / 2, consoleHeight / 10 * 7 + 1, kailiangJob, 14);
			break;
		}
		faceDrawn = 1;
	}

	keyDown = _kbhit();
	if (keyDown)
	{
		keyPress = _getch();
		if (keyPress == 27)
		{
			gsm_returnStateSystem()->next = state_mainMenu;
		}
	}
}

void credits_Destructor()
{
	free(adam.string);
	free(marcus.string);
	free(kailiang.string);
	free(edwin.string);
	free(clear.string);
}