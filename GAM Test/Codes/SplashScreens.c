
#include "SplashScreens.h"
#include "Game.h"
#include "windows.h"
#include "Console.h"

AsciiChar digipen, studio;

void splashScreen_Init()
{
	digipen.height = digipen.width = studio.width = studio.height = 0;
	digipen.string = game_readFile("Assets/Digipen.txt", &(digipen.width), &(digipen.height));
	studio.string = game_readFile("Assets/Studio.txt", &(studio.width), &(studio.height));
}

void splashScreen_Draw()
{
	int j, i;
	for (i = 0; i < digipen.height - 1; i++)
	{
		for (j = 0; j < digipen.width; j++)
		{
			if (*(digipen.string + (i * (digipen.width + 1)) + j) != '\n')
			{
				console_draw(console_getConsoleWidth()/2-digipen.width/2 + j, console_getConsoleHeight() / 2 - digipen.height / 2 + i, *(digipen.string + (i * (1 + digipen.width)) + j), 12);
			}
		}
	}
	Sleep(3);
	system("cls");
	for (i = 0; i < studio.height - 1; i++)
	{
		for (j = 0; j < studio.width; j++)
		{
			if (*(studio.string + (i * (studio.width + 1)) + j) != '\n')
			{
				console_draw(console_getConsoleWidth() / 2 - studio.width / 2 + j, console_getConsoleHeight() / 2 - studio.height / 2 + i, *(studio.string + (i * (1 + studio.width)) + j), 15);
			}
		}
	}
	Sleep(3);
	system("cls");
}



























