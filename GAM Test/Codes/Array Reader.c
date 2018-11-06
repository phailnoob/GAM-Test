
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

void arrayReader_setMap(short size)
{
	free(array);
	array = malloc(size);
}

void arrayReader_draw(int drawOrder)
{
	switch (drawOrder)
	{
	case 0:
		dataStorage_getMapData(&width, &height);

		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				console_draw((console_getConsoleWidth() - width) / 2 + j,
							(console_getConsoleHeight() - height) / 2 + i,
							spriteReference_getSprite(dataStorage_getMapValue(j, i)),
							7);
			}
		}
		break;

	case 1:
		dataStorage_getPlayerPosition(&playerX, &playerY);

		console_draw((console_getConsoleWidth() - width) / 2 + playerX,
					(console_getConsoleHeight() - height) / 2 + playerY,
					spriteReference_getSprite(2),
					7);
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

void arrayReader_clear(int drawOrder)
{
	switch (drawOrder)
	{
	case 0:
		break;

	case 1:
		dataStorage_getPlayerPosition(&playerX, &playerY);

		console_draw((console_getConsoleWidth() - width) / 2 + playerX,
					(console_getConsoleHeight() - height) / 2 + playerY,
					spriteReference_getSprite(0),
					7);
		break;

	case 2:
		break;

	case 3:
		break;

	case 4:
		break;
	}
}
