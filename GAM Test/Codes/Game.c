
#include "Game.h"
#include "Enemy.h"
#include "Console.h"
#include "Array Reader.h"
#include "Data Storage.h"
#include "Input.h"
#include <stdio.h>

bool isRunning;

static int playerX, playerY, startX, startY, mapWidth, mapHeight, fogStart, fogEnd; 
/* TODO Make sure to clear up all these static variables if the player goes back to main menu*/

/*edited*/
static char map[10][10] = {	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
							{1, 3, 0, 0, 0, 0, 0, 0, 0, 1},
							{1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
							{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							{1, 3, 1, 1, 1, 1, 0, 1, 1, 1},
							{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							{1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
							{1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
							{1, 3, 0, 0, 0, 1, 0, 0, 0, 1},
							{1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };



void game_init()
{
	console_init();
	console_clear();
	arrayReader_init();
	input_init();

	isRunning = true;
	startX = 6;
	startY = 5;
	mapWidth = 10;
	mapHeight = 10;
	fogStart = 5;
	fogEnd = 8;

	game_loadMap(0);

}

bool game_isRunning()
{
	return isRunning;
}

void game_update()
{
	input_checkInput();
}


void game_EnemyUpdate()
{
	for (int i = 0; i < 10; i++)
	{
		enemy_Update(i);
	}
}

void game_playerAction(int action)
{
	arrayReader_clear(1);
	switch (action)
	{
		case 1:
			dataStorage_setPlayerPosition(playerX, --playerY);
			if (dataStorage_checkWall())
				dataStorage_setPlayerPosition(playerX, ++playerY);
			game_EnemyUpdate();
			
			arrayReader_draw(0);
			break;
		case 2:
			dataStorage_setPlayerPosition(playerX, ++playerY);
			if (dataStorage_checkWall())
				dataStorage_setPlayerPosition(playerX, --playerY);
			game_EnemyUpdate();

			arrayReader_draw(0);
			break;
		case 3:
			dataStorage_setPlayerPosition(--playerX, playerY);
			if (dataStorage_checkWall())
				dataStorage_setPlayerPosition(++playerX, playerY);
			game_EnemyUpdate();

			arrayReader_draw(0);
			break;
		case 4:
			dataStorage_setPlayerPosition(++playerX, playerY);
			if (dataStorage_checkWall())
				dataStorage_setPlayerPosition(--playerX, playerY);
			game_EnemyUpdate();

			arrayReader_draw(0);
			break;

		case 0:
			break;
	}

	arrayReader_draw(1);
}

void game_loadMap(int mapNo)
{
	playerX = startX;
	playerY = startY;
	mapWidth = sizeof(map[0]);
	mapHeight = sizeof(map)/sizeof(map[0]);

	dataStorage_setFogDistance(fogStart, fogEnd);
	dataStorage_setPlayerPosition(playerX, playerY);
	dataStorage_setMapData(*map, mapWidth, mapHeight);

	arrayReader_setMap(sizeof(map));

	dataStorage_EnemyInit();
	arrayReader_draw(0);
	arrayReader_draw(1);
}


