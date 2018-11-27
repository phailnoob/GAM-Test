
#include <stdio.h>
#include "Game.h"
#include "Enemy.h"
#include "Console.h"
#include "Array Reader.h"
#include "MainMenu.h"
#include "Data Storage.h"
#include "Input.h"
#include "Torch.h"
#include "Trap.h"
#include <time.h>
#include <stdio.h>
#include "GameStateManager.h"
#include "MainMenu.h"
#include "Options.h"
#include "PauseMenu.h"
#include "Credits.h"
#include "SplashScreens.h"

bool isRunning, mapUsed;

static int playerX, playerY, mapWidth, mapHeight; 
static int torch_counter, trap_counter, changingColor;
/* TODO Make sure to clear up all these static variables if the player goes back to main menu*/

clock_t begin;
double time_spent, prevTime, timeLapse;
int currentMapNum = 0;
bool isPaused;
static int exitX, exitY;


/*edited*/
static char *map;

void game_init()
{
	dataStorage_init();
	console_init();
	console_clear();
	gsm_gameStateInit();
	arrayReader_init();
	input_init();
	mainMenu_Init();
	splashScreen_Init();
	splashScreen_Draw();

	mapUsed = false;
	isRunning = true;
	torch_counter = trap_counter = changingColor = 0;
	exitX = exitY = 1;

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

/*Temp lose screen*/
void game_loseTempScreen()
{
	if (*dataStorage_getAliveBool() == false)
	{
		console_drawString(console_getConsoleWidth() / 2 - 4, console_getConsoleHeight() / 10, "YOU LOSE", changingColor, 8);
		console_drawString(console_getConsoleWidth() / 2 - 10, console_getConsoleHeight() / 10+1, "PRESS ESC TO RESTART", changingColor, 20);


	}
}

/*Temp lose screen*/
void game_winTempScreen()
{
	console_drawString(console_getConsoleWidth() / 2 - 4, console_getConsoleHeight() / 10, "YOU WIN!", changingColor, 8);
	console_drawString(console_getConsoleWidth() / 2 - 10, console_getConsoleHeight() / 10 + 1, "PRESS ESC TO RESTART", changingColor, 20);
}

void game_changeColor()
{
	if (changingColor < 15)
	{
		changingColor++;
	}
	else
	{
		changingColor = 9;
	}
}



void game_EnemyUpdate()
{
	int x, y;
	dataStorage_getPlayerPosition(&x, &y);
	enemy_weightedMapReset();
	enemy_recursiveCheckPath(dataStorage_getMapDataOut(), x, y, 1, 1);
	enemy_setWallWeight(-1, dataStorage_getMapDataOut());
	//enemy_drawDebugWeight();
	for (int i = 0; i < 10; i++)
	{
		enemy_Update(i, dataStorage_getEnemyObject(i));
	}
	/*
		printf("\nexit pos:   %d %d\n", exitX, exitY);
		printf("player pos: %d %d\n", playerX, playerY);
	*/
	if (exitX == playerX && exitY == playerY)
	{
		if (currentMapNum == 0)
		{
			game_loadMap(1);
			currentMapNum++;
		}
		else if(currentMapNum == 1)
		{
			game_winTempScreen();
		}
	}
}

/*
Main Game Update Loop

Scrolls through the different game states

*/
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
					*dataStorage_getAliveBool() = true;
					gsm_returnStateSystem()->next = state_Game;
					game_loadMap(0);

				}
				else if (gsm_returnStateSystem()->next == state_Options)
				{
					options_Init();
				}
				else if (gsm_returnStateSystem()->next == state_Credits)
				{
					credits_Init();
				}
			}
			break;
		case state_Options:
			options_Update();
			if (gsm_IsChanging())
			{
				system("cls");
				mainMenu_resetMainMenu();
			}
			break;
		case state_Credits:
			credits_Update();
			if (gsm_IsChanging())
			{
				system("cls");
				mainMenu_resetMainMenu();
			}
			break;
		case state_Game:
			time_spent = (double)(clock() - begin - prevTime) / CLOCKS_PER_SEC;
			arrayReader_draw();
			while (time_spent - prevTime >= timeLapse)
			{
				game_EnemyUpdate();
				prevTime = time_spent;
				game_changeColor();
				game_loseTempScreen();
			}

			game_borders();
			drawUI();
			UI_draw_torches();
			UI_draw_traps();
			input_checkInput();
			break;
		case state_PauseMenu:
			PauseMenu_Update();
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
		gsm_returnStateSystem()->next = gsm_returnStateSystem()->current;
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
			UI_draw_ResetTorchDrawn();
			if (torch_counter > 4)
				torch_counter -= 5;
			if (dataStorage_torch_counter() <5)
			{
				placeTorch(torch_counter, playerX, playerY);
				torch_counter++;
			}
			break;
		case 6: /* place trap action */

			UI_draw_ResetTrapDrawn();
			if (trap_counter > 4)
				trap_counter -= 5;
			if (dataStorage_trap_counter() <5)
			{
				placeTrap(trap_counter, playerX, playerY);
				trap_counter++;
			}
			break;

		case 7: /* pause */
			if (!isPaused)
			{
				gsm_returnStateSystem()->next = state_PauseMenu;
				PauseMenu_Init();
				isPaused = !isPaused;
			}
			else
			{
				gsm_returnStateSystem()->next = state_Game;
				isPaused = !isPaused;
			}
			break;
		case 0:
			break;
	}


	/*Enemies update loop*/
	/*game_EnemyUpdate();*/

	/*Draw Loop*/
	if(!isPaused)
		arrayReader_draw();
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
			fileName = "Levels/1.txt";
			break;
		case 1:
			fileName = "Levels/2.txt";
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

		game_modifyLoadValue(&exitX, &temp, '/', stream);
		game_modifyLoadValue(&exitY, &temp, '\n', stream);

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
			bool patrol;
			int x1, x2, y1, y2;
			x1 = x2 = y1 = y2 = -1;

			game_modifyLoadValue(&x, &temp, '/', stream);
			game_modifyLoadValue(&y, &temp, '/', stream);

			if (temp == 't' || temp == 'T')
			{
				patrol = true;
				while (temp != '/')
					fread(&temp, sizeof(char), 1, stream);
				fread(&temp, sizeof(char), 1, stream);
				game_modifyLoadValue(&x1, &temp, '/', stream);
				game_modifyLoadValue(&y1, &temp, '/', stream);
				game_modifyLoadValue(&x2, &temp, '/', stream);
				game_modifyLoadValue(&y2, &temp, '\n', stream);
			}
			else
			{
				patrol = false;
				while (temp != '\n')
					fread(&temp, sizeof(char), 1, stream);
				fread(&temp, sizeof(char), 1, stream);
			}

			enemy_spawnEnemy(x, y, counter, patrol, x1, y1, x2, y2);

			counter++;
		}


		fclose(stream);

		dataStorage_TorchInit();
		dataStorage_setPlayerPosition(playerX, playerY);
		dataStorage_setExitPos(exitX, exitY);

		arrayReader_setInitialDraw(true);
		arrayReader_draw();
		arrayReader_setInitialDraw(false);
	}
	else
		game_turnOffGame();
}

char * game_readFile(char * fileName, int *fileWidth, int *fileHeight)
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
		return textstring;
	}
	else
		game_turnOffGame();
}



