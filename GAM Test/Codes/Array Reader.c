
#include "Array Reader.h"
#include "Console.h"
#include "SpriteReference.h"
#include "Data Storage.h"
#include "Enemy.h"

static char *array;
static int width, height, i ,j, playerX, playerY, fogStart, fogEnd, distance, g, f;

void arrayReader_init()
{
	width = height = -1;
	i = j = g = f = -1;
	playerX = playerY = -1;
	fogStart = fogEnd = distance = -1;
}

void arrayReader_draw(int drawOrder, char *arr)
{
	switch (drawOrder)
	{
	case 0:
		dataStorage_getMapSize(&width, &height);
		dataStorage_getPlayerPosition(&playerX, &playerY);
		dataStorage_getFogDistance(&fogStart, &fogEnd);

		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				distance = (j - playerX) * (j - playerX) + (i - playerY) * (i - playerY);
				if (distance < fogStart * fogStart)
					console_draw(console_getConsoleWidth() / 2 + j - playerX,
								console_getConsoleHeight() / 2 + i - playerY,
								spriteReference_getSprite(arr[i * width + j]));
				else if (distance > fogStart * fogStart && distance < fogEnd * fogEnd)
					console_draw(console_getConsoleWidth() / 2 + j - playerX,
								console_getConsoleHeight() / 2 + i - playerY,
								88);
			}
		}

		console_draw(console_getConsoleWidth() / 2, console_getConsoleHeight() / 2, spriteReference_getSprite(2));
		break;

	case 1:
		break;

	case 2:
		break;

	case 3:
/*
		dataStorage_getMapSize(&width, &height);
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				console_draw(i, j, enemy_getWeightMap()->mapArray[i + j * width]);
			}
		}*/
		break;

	case 4:
		break;
	}
}

void arrayReader_clear(int drawOrder, int *arr)
{
	switch (drawOrder)
	{
	case 0:
		dataStorage_getMapSize(&width, &height);
		dataStorage_getPlayerPosition(&playerX, &playerY);

		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
				console_draw(console_getConsoleWidth() / 2 + j - playerX,
							console_getConsoleHeight() / 2 + i - playerY,
							0);
		}
		break;

	case 1:
		break;

	case 2:
		break;

	case 3:
		break;

	case 4:
		break;
	}
}
