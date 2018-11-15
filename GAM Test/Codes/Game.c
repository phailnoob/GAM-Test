
#include "Game.h"
#include "Enemy.h"
#include "Console.h"
#include "Array Reader.h"
#include "Data Storage.h"
#include "Input.h"
#include "Torch.h"
#include <stdio.h>
#include "GameStateManager.h"
#include "MainMenu.h"

bool isRunning;

static int playerX, playerY, mapWidth, mapHeight; 
static int torch_counter;
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

static char map2[10][10] = { {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
							{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							{1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
							{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							{1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
							{1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
							{1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
							{1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };

static char map3[10][10] = { {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
							{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							{1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
							{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							{1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
							{1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
							{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
							{1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };

void game_init()
{
	console_init();
	console_clear();
	gsm_gameStateInit();
	arrayReader_init();
	input_init();

	isRunning = true;


	torch_counter = 0;
}

bool game_isRunning()
{
	return isRunning;
}

void game_turnOffGame()
{
	isRunning = false;
	arrayReader_Destructor();
	enemy_Destructor();
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
				if (gsm_returnStateSystem()->next == state_Game)
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
		}
	}
	else
	{
		switch (gsm_returnCurrentState())
		{
		case state_Exit:
			game_turnOffGame();
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

	int x, y;
	dataStorage_getPlayerPosition(&x, &y);
	enemy_weightedMapReset();
	enemy_recursiveCheckPath(dataStorage_getMapDataOut(), x, y, 1, 1);
	enemy_setWallWeight(-1, dataStorage_getMapDataOut());
	enemy_drawDebugWeight();
	for (int i = 0; i < 10; i++)
	{
		enemy_Update(i,dataStorage_getEnemyObject(i));
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
		case 5: /* place torch action */
			if (torch_counter > 4)
				torch_counter -= 5;
			placeTorch(torch_counter, playerX, playerY);
			torch_counter++;
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

		dataStorage_TorchInit();
	}

	if (mapNo == 1)
	{
		playerX = 6;
		playerY = 5;

		mapWidth = sizeof(map2[0]);
		mapHeight = sizeof(map2) / sizeof(map2[0]);

		dataStorage_setMapData(*map2, mapWidth, mapHeight);
		arrayReader_setMap(sizeof(map2));

		dataStorage_EnemyInit(playerX, playerY);
		dataStorage_TorchInit();
	}

	if (mapNo == 2)
	{
		playerX = 6;
		playerY = 5;

		mapWidth = sizeof(map3[0]);
		mapHeight = sizeof(map) / sizeof(map[0]);

		dataStorage_setMapData(*map3, mapWidth, mapHeight);
		arrayReader_setMap(sizeof(map3));

		dataStorage_EnemyInit(playerX, playerY);
		dataStorage_TorchInit();
	}

	dataStorage_setPlayerPosition(playerX, playerY);

	arrayReader_draw() ;
}



void setxy(int x_coord, int y_coord)
{
	COORD c = { 0, 0 };
	c.X = x_coord; c.Y = y_coord; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


void game_borders()
{
		
		int j;
		
		/*Print corners*/
		setxy(0, 0);           
			printf("%c", 201);
		setxy(0, console_getConsoleHeight());
			printf("%c", 200);
		setxy(console_getConsoleWidth(), 0);
			printf("%c", 187);
		setxy(console_getConsoleWidth(), console_getConsoleHeight());
			printf("%c", 188);


		/*top border*/
		setxy(1,0);
		for (j = 0; j < console_getConsoleWidth()-1; j++)
			printf("%c", 205);

		/*Bottom border*/ 
		setxy(1, console_getConsoleHeight());
		for (j = 0; j <= console_getConsoleWidth()-1; j++)
			printf("%c", 205);

		/*Left and right border*/
		for (j = 0; j < console_getConsoleHeight()-1; j++)
		{
			setxy(0, 0 + j);
			printf("%c", 186);

			setxy(100, 0 + j);
			printf("%c", 186);
		}
		
}

void drawUI()
{
	int i, j;
	i = console_getConsoleHeight();
	for (j = 0; j < (i - 1); j++)
	{
		setxy(30, 1 + j);
		printf("%c", 186);
	}

	setxy(1, 20);
	for (j = 0, j < 30; j++)
		printf("%c", 205);
}

