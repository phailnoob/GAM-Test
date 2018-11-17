
#include <stdio.h>
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

bool isRunning, mapUsed;

static int playerX, playerY, mapWidth, mapHeight; 
static int torch_counter, trap_counter;
/* TODO Make sure to clear up all these static variables if the player goes back to main menu*/

clock_t begin;
double time_spent, prevTime, timeLapse;
bool isPaused;
static int exitX, exitY;

void game_EnemyUpdate();

/*edited*/
static char *map;

void game_init()
{
	console_init();
	console_clear();
	gsm_gameStateInit();
	arrayReader_init();
	input_init();

	mapUsed = false;
	isRunning = true;
	torch_counter = trap_counter = 0;
	exitX = exitY = 1;

	torch_counter = 0;
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
	if (mapUsed)
	{
		free(map);
		arrayReader_Destructor();
		enemy_Destructor();
	}
}

void game_clearGame()
{
	console_clear();
	if (mapUsed)
	{
		free(map);
		arrayReader_Destructor();
		enemy_Destructor();
	}
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
//		console_clear();
//		gsm_returnStateSystem()->next = state_mainMenu;
	}
}

void game_modifyLoadValue(int * value, char * temp, char chara, FILE *stream)
{
	*value = atoi(temp);

	while (*temp != chara)
	{
		fread(temp, sizeof(char), 1, stream);
/*	*dataStorage_getAliveBool() = true;
	if (mapNo == 0)
	{
		playerX = 6;
		playerY = 5;

		exitX = 1;
		exitY = 7;
		dataStorage_setExitPos(exitX, exitY);

		mapWidth = sizeof(map[0]);
		mapHeight = sizeof(map) / sizeof(map[0]);
*/
		if (*temp != chara)
		{
			*value *= 10;
			*value += atoi(temp);
		}
	}

	fread(temp, sizeof(char), 1, stream);
}

void game_loadMap(int mapNo)
{
	FILE *stream;
	bool checkHeight = true;
	bool fileOpen = false;
	char *fileName = NULL, temp = NULL;
	int counter = 0, x = 0, y = 0;
		/***************************************
			-Spawn Enemy locations
			-Set patrol bool
			-Set 2 patrol locations
		***************************************/
/*		enemy_spawnEnemy(1, 1, 0,true,1,1,8,1);
		enemy_spawnEnemy(1, 5, 1,false,-1,-1,-1,-1);
		enemy_spawnEnemy(1, 8, 2,false,-1,-1,-1,-1);
*/
	switch (mapNo)
	{
		case 0:
			fileName = "Levels/0.txt";
			break;
	}

	fileOpen = (fopen_s(&stream, fileName, "r+t") == 0);

	if (fileOpen)
	{
		mapWidth = 0;
		mapHeight = 1;
		fread(&temp, sizeof(char), 1, stream);

		while (temp != '\n')
			mapWidth += fread(&temp, sizeof(char), 1, stream);

		while (checkHeight)
		{
			fread(&temp, sizeof(char), 1, stream);
			if (temp == '\n')
			{
				mapHeight++;
				fread(&temp, sizeof(char), 1, stream);
				if (temp == '\n')
					checkHeight = false;
			}
		}

		if (mapUsed)
			free(map);

		map = NULL;

		map = malloc(mapWidth * mapHeight);
		mapUsed = true;

		fclose(stream);
		fileOpen = (fopen_s(&stream, fileName, "r+t") == 0);

		while (counter < mapWidth * mapHeight)
		{
			fread(&temp, sizeof(char), 1, stream);
			if (temp != '\n')
			{
				*(map + counter) = atoi(&temp);
				/****************************************************************

				this here changes the the current map loaded into their int form.
				
				this is solely assuming that the map is based on the old system
				of using the conversion of the sprite reference c file

				****************************************************************/
				counter++;
			}
		}

		fread(&temp, sizeof(char), 1, stream);

		while (temp == '\n')
			fread(&temp, sizeof(char), 1, stream);

		game_modifyLoadValue(&playerX, &temp, '/', stream);
		game_modifyLoadValue(&playerY, &temp, '\n', stream);

		while (temp == '\n')
			fread(&temp, sizeof(char), 1, stream);

/*		arrayReader_Destructor();
		playerX = 6;
		playerY = 5;

		exitX = 1;
		exitY = 7;

		mapWidth = sizeof(map2[0]);
		mapHeight = sizeof(map2) / sizeof(map2[0]);
*/
		dataStorage_setMapData(map, mapWidth, mapHeight);
		arrayReader_setMap(mapWidth * mapHeight);

		dataStorage_EnemyInit(playerX, playerY);

		counter = 0;

		while (temp != '\n')
		{
			game_modifyLoadValue(&x, &temp, '/', stream);
			game_modifyLoadValue(&y, &temp, '\n', stream);
//			enemy_spawnEnemy(x, y, counter);
			counter++;
		}

		dataStorage_TorchInit();
		dataStorage_setPlayerPosition(playerX, playerY);
		dataStorage_setExitPos(exitX, exitY);

		arrayReader_draw();
	}
	else
		game_turnOffGame();
}

char *game_readFile(char * fileName, int *fileWidth, int *fileHeight)
{
	char *textstring;
	FILE *stream;
	bool checkHeight = true;
	bool fileOpen = false;
	char temp = NULL;
	int counter = 0;

	fileOpen = (fopen_s(&stream, fileName, "r+t") == 0);

	if (fileOpen)
	{
		*fileWidth = 0;
		*fileHeight = 1;
		fread(&temp, sizeof(char), 1, stream);

		while (temp != '\n')
			*fileWidth += fread(&temp, sizeof(char), 1, stream);

		while (checkHeight)
		{
			fread(&temp, sizeof(char), 1, stream);
			if (temp == '\n')
			{
				*fileHeight += 1;
				if(!fread(&temp, sizeof(char), 1, stream))
					checkHeight = false;
				else if (temp == '\n')
					*fileHeight += 1;
			}
		}

		textstring = malloc(*fileWidth * *fileHeight);
		
		fclose(stream);
		fileOpen = (fopen_s(&stream, fileName, "r+t") == 0);

		while (counter < *fileWidth * *fileHeight)
		{
			fread(&temp, sizeof(char), 1, stream);
			*(textstring + counter) = temp;
			counter++;
		}
	

		*(textstring + *fileWidth * *fileHeight - 1) = '\0';
	}
	else
		game_turnOffGame();
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
