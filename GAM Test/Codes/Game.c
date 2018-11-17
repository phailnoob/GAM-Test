
#include "Game.h"
#include "Enemy.h"
#include "Console.h"
#include "Array Reader.h"
#include "Data Storage.h"
#include "Input.h"
#include "Torch.h"
#include <time.h>
#include <stdio.h>
#include "GameStateManager.h"
#include "MainMenu.h"
#include "PauseMenu.h"

bool isRunning;

static int playerX, playerY, mapWidth, mapHeight; 
static int torch_counter, trap_counter;
/* TODO Make sure to clear up all these static variables if the player goes back to main menu*/

clock_t begin;
double time_spent, prevTime, timeLapse;
bool isPaused;
static int exitX, exitY;

void game_EnemyUpdate();

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
	torch_counter = trap_counter = 0;
	exitX = exitY = 0;

	begin = clock();
	timeLapse = 0.3;
	time_spent = prevTime = (double)(clock() - begin) / CLOCKS_PER_SEC;
	isPaused = false;
}

bool game_isRunning()
{
	return isRunning;
}

void game_turnOffGame()
{
	isRunning = false;
/*	arrayReader_Destructor();
	enemy_Destructor();*/
}

void game_clearGame()
{
	console_clear();
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
					mainMenu_resetMainMenu();
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
			time_spent = (double)(clock() - begin - prevTime) / CLOCKS_PER_SEC;

			while (time_spent - prevTime >= timeLapse)
			{
				game_EnemyUpdate();
				arrayReader_draw();
				prevTime = time_spent;
			}

			input_checkInput();
			break;
		case state_PauseMenu:

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

	printf("\nexit pos:   %d %d\n", exitX, exitY);
	printf("player pos: %d %d\n", playerX, playerY);

	if (exitX == playerX && exitY == playerY)
		game_loadMap(0);
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
		case 6: /* place trap action */
			if (trap_counter > 4)
				trap_counter -= 5;
			placeTrap(trap_counter, playerX, playerY);
			trap_counter++;
			break;

		case 7: /* pause */
			if (isPaused)
			{
				gsm_returnStateSystem()->next = state_PauseMenu;
				PauseMenu_Init();
			}
			else
			{
				gsm_returnStateSystem()->next = state_Game;
			}
			break;
		case 0:
			break;
	}


	/*Enemies update loop*/
	/*game_EnemyUpdate();*/

	/*Draw Loop*/
	arrayReader_draw();

	if (*dataStorage_getAliveBool() == false)
	{
		/*PLAYER COLLISION*/
		console_clear();
		gsm_returnStateSystem()->next = state_mainMenu;
	}
}

void game_loadMap(int mapNo)
{
	*dataStorage_getAliveBool() = true;
	if (mapNo == 0)
	{
		playerX = 6;
		playerY = 5;

		exitX = 1;
		exitY = 7;

		mapWidth = sizeof(map[0]);
		mapHeight = sizeof(map) / sizeof(map[0]);

		dataStorage_setMapData(*map, mapWidth, mapHeight);
		arrayReader_setMap(sizeof(map));

		dataStorage_EnemyInit(playerX, playerY);

		/***************************************
			-Spawn Enemy locations
			-Set patrol bool
			-Set 2 patrol locations
		***************************************/
		enemy_spawnEnemy(1, 1, 0,true,1,1,8,1);
		enemy_spawnEnemy(1, 5, 1,false,-1,-1,-1,-1);
		enemy_spawnEnemy(1, 8, 2,false,-1,-1,-1,-1);

		dataStorage_TorchInit();
	}

	if (mapNo == 1)
	{

		arrayReader_Destructor();
		playerX = 6;
		playerY = 5;

		exitX = 1;
		exitY = 7;

		mapWidth = sizeof(map2[0]);
		mapHeight = sizeof(map2) / sizeof(map2[0]);

		dataStorage_setMapData(*map2, mapWidth, mapHeight);
		arrayReader_setMap(sizeof(map2));

		dataStorage_EnemyInit(playerX, playerY);
		dataStorage_TorchInit();
	}

	if (mapNo == 2)
	{

		arrayReader_Destructor();
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

	arrayReader_draw();
}



//
//
//void setxy(int x_coord, int y_coord)
//{
//	c.X = x_coord; c.Y = y_coord; 
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
//}
//
//
//void game_borders()
//{
//		COORD c = { 0, 0 };
//		int i, j;
//		
//
//		/*top border*/
//		setxy(0,0);
//		for (j = 0; j < console_getConsoleWidth(); j++)
//			printf("%c", 223);
//
//		/*Bottom border*/ 
//		setxy(0, console_getConsoleHeight());
//		for (j = 0; j <= console_getConsoleWidth(); j++)
//			printf("%c", 223);
//
//		/*Left and right border*/
//		for (j = 0; j < console_getConsoleHeight(); j++)
//		{
//			setxy(0, 0 + j);
//			printf("%c", 219);
//
//			setxy(100, 0 + j);
//			printf("%c", 219);
//		}
//		
//}
//
//void drawUI()
//{
//	int i, j;
//	i = console_getConsoleHeight();
//	for (j = 0; j < (i - 1); j++)
//	{
//		setxy(30, 1 + j);
//		printf("%c", 186);
//	}
//
//
//	setxy(1, 20);
//	for (j = 0, j < 30; j++)
//		printf("%c", 205);
//
//	/*print torches ascii art*/
//	setxy(1, 1);
//	printf("Torches:")
//
//
//	int Inv_Torch = 1;
//
//	While(Inv_Torch)
//	{
//		if (Inv_Torch == 1)
//		{
//			setxy(1, 2);
//			printf("  (\");
//				setxy(1, 3);
//			printf("   '");
//			setxy(1, 4);
//			printf("  |  |");
//			setxy(1, 5);
//			printf("  |  |");
//			setxy(1, 6);
//			printf("  |__|");
//		}
//
//
//		if (Inv_Torch == 2)
//		{
//			setxy(1, 2);
//			printf("  (\");
//				setxy(1, 3);
//			printf("   '");
//			setxy(1, 4);
//			printf("  |  |");
//			setxy(1, 5);
//			printf("  |  |");
//			setxy(1, 6);
//			printf("  |__|");
//
//			setxy(7, 2);
//			printf("  (\");
//				setxy(7, 3);
//			printf("   '");
//			setxy(7, 4);
//			printf("  |  |");
//			setxy(7, 5);
//			printf("  |  |");
//			setxy(7, 6);
//			printf("  |__|");
//
//		}
//
//		if (Inv_Torch == 3)
//		{
//			setxy(1, 2);
//				printf("  (\");
//			setxy(1, 3);
//				printf("   '");
//			setxy(1, 4);
//				printf("  |  |");
//			setxy(1, 5);
//				printf("  |  |");
//			setxy(1, 6);
//				printf("  |__|");
//
//			setxy(7, 2);
//				printf("  (\");
//			setxy(7, 3);
//				printf("   '");
//			setxy(7, 4);
//				printf("  |  |");
//			setxy(7, 5);
//				printf("  |  |");
//			setxy(7, 6);
//				printf("  |__|");
//
//
//			setxy(13, 2);
//				printf("  (\");
//			setxy(13, 3);
//				printf("   '");
//			setxy(13, 4);
//				printf("  |  |");
//			setxy(13, 5);
//				printf("  |  |");
//			setxy(13, 6);
//				printf("  |__|");
//		}
//
//	}
//} 