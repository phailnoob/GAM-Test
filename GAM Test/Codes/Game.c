
#include "Game.h"
#include "Enemy.h"
#include "Console.h"
#include "Array Reader.h"
#include "Data Storage.h"
#include "Input.h"
#include <stdio.h>
#include "GameStateManager.h"
#include "MainMenu.h"

bool isRunning;

static int playerX, playerY, mapWidth, mapHeight; 
/* TODO Make sure to clear up all these static variables if the player goes back to main menu*/



/*edited*/
static char map[10][10] = {	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
							{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							{1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
							{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							{1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
							{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							{1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
							{1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
							{1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
							{1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };



void game_init()
{
	console_init();
	console_clear();
	gsm_gameStateInit();
	arrayReader_init();
	input_init();

	isRunning = true;


}

bool game_isRunning()
{
	return isRunning;
}

void game_update()
{

	
	if (gsm_IsValid(gsm_returnCurrentState()))
	{

		switch (gsm_returnCurrentState())
		{
		case state_splashScreen:
			break;
		case state_mainMenu:
			mainMenu_Update();

			if (gsm_IsChanging())
			{
				if (gsm_returnStateSystem()->next = state_Game)
				{
					game_loadMap(0);

					gsm_returnStateSystem()->next = state_Game;
				}
			}
			break;
		case state_Options:
			break;
		case state_Credits:
			break;
		case state_Game:
			
			input_checkInput();
			break;
		case state_Exit:
			break;
		}
	}
	if (gsm_IsChanging())
	{
		gsm_returnStateSystem()->previous = gsm_returnStateSystem()->current;
		gsm_returnStateSystem()->current = gsm_returnStateSystem()->next;
	}

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

	game_EnemyUpdate();
	arrayReader_draw();
}

void game_loadMap(int mapNo)
{
	if (mapNo == 0)
	{
		playerX = 6;
		playerY = 5;

		mapWidth = sizeof(map[0]);
		mapHeight = sizeof(map) / sizeof(map[0]);

		dataStorage_setMapData(*map, mapWidth, mapHeight);
		arrayReader_setMap(sizeof(map));

		dataStorage_EnemyInit(playerX, playerY);

		enemy_spawnEnemy(1, 1, 0);
		enemy_spawnEnemy(1, 5, 1);
		enemy_spawnEnemy(1, 8, 2);
	}

	dataStorage_setPlayerPosition(playerX, playerY);

	arrayReader_draw();
}


