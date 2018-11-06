
#include "Game.h"
#include "Console.h"
#include "Array Reader.h"
#include "Data Storage.h"
#include "Input.h"
#include <stdio.h>

static bool isRunning;

static int playerX, playerY, startX, startY, mapWidth, mapHeight, fogStart, fogEnd;

static char map[10][10] = {	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
							{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							{1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
							{1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
							{1, 1, 1, 1, 0, 1, 0, 1, 1, 1},
							{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							{1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
							{1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
							{1, 1, 0, 0, 0, 1, 0, 0, 0, 1},
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
	mapWidth = -1;
	mapHeight = -1;
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

void game_playerUpdate()
{
	arrayReader_draw(1);
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
			break;
		case 2:
			dataStorage_setPlayerPosition(playerX, ++playerY);
			if (dataStorage_checkWall())
				dataStorage_setPlayerPosition(playerX, --playerY);
			break;
		case 3:
			dataStorage_setPlayerPosition(--playerX, playerY);
			if (dataStorage_checkWall())
				dataStorage_setPlayerPosition(++playerX, playerY);
			break;
		case 4:
			dataStorage_setPlayerPosition(++playerX, playerY);
			if (dataStorage_checkWall())
				dataStorage_setPlayerPosition(--playerX, playerY);
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
	dataStorage_setMapData(map, mapWidth, mapHeight);

	arrayReader_setMap(sizeof(map));

	arrayReader_draw(0);
	arrayReader_draw(1);
}
