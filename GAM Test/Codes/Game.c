
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
#include "SplashScreens.h"
#include "Credits.h"
#include "UI.h"
#include "VictoryScreen.h"
#include "Music.h"

bool isRunning, mapUsed;

static int playerX, playerY, mapWidth, mapHeight; 
static int torch_counter, trap_counter, changingColor;
/* TODO Make sure to clear up all these static variables if the player goes back to main menu*/

clock_t begin;
double time_spent, prevTime, timeLapse;
int currentMapNum, lastMapNum;
int currentMapNum = 0;
bool isPaused;
static int exitX, exitY;


/*edited*/
static char *map;

void game_init()
{
	PauseMenu_Init();
	dataStorage_init();
	console_init();
	console_clear();
	gsm_gameStateInit();
	arrayReader_init();
	input_init();
	mainMenu_Init();
	splashScreen_Init();
	splashScreen_Draw();
	Music_Init();

	mapUsed = false;
	isRunning = true;
	torch_counter = trap_counter = changingColor = 0;
	exitX = exitY = 1;

	begin = clock();
	timeLapse = 0.3;
	time_spent = prevTime = (double)(clock() - begin) / CLOCKS_PER_SEC;
	isPaused = false;

	currentMapNum = 0;
	lastMapNum = 4;
	music_Update();
}

void game_resetClock()
{
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
		console_drawString(console_getConsoleWidth() / 2 - 4, console_getConsoleHeight() / 10, "YOU LOSE", (char)changingColor);
		console_drawString(console_getConsoleWidth() / 2 - 10, console_getConsoleHeight() / 10+1, "PRESS ESC TO RESTART", (char)changingColor);

	}
}

/*Temp lose screen*/
void game_winTempScreen()
{
	*dataStorage_getAliveBool() = false;
	console_drawString(console_getConsoleWidth() / 2 - 4, console_getConsoleHeight() / 10, "YOU WIN!", (char)changingColor);
	console_drawString(console_getConsoleWidth() / 2 - 10, console_getConsoleHeight() / 10 + 1, "PRESS ESC TO RESTART", (char)changingColor);
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
	enemy_recursiveCheckPath(dataStorage_getMapDataOut(), (char)x, (char)y, (char)1, (char)1);
	enemy_setWallWeight(-1, dataStorage_getMapDataOut());
	//enemy_drawDebugWeight();
	for (char i = 0; i < 10; i++)
	{
		enemy_Update(i, dataStorage_getEnemyObject(i));
	}
	/*
		printf("\nexit pos:   %d %d\n", exitX, exitY);
		printf("player pos: %d %d\n", playerX, playerY);
	*/
	if (exitX == playerX && exitY == playerY)
	{
		if(currentMapNum == lastMapNum)
		{
			console_clear();
			gsm_returnStateSystem()->next = state_Victory;
			VictoryScreen_Init();
			/* game_winTempScreen(); */
		}
		else
		{
			currentMapNum++;
			system("cls");
			game_loadMap(currentMapNum);
		}
	}
}

void SetMapNum(int mapNum)
{
	currentMapNum = mapNum;
}

void game_RestartCurrentMap()
{
	game_loadMap(currentMapNum);
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
			music_Update();

			if (gsm_IsChanging())
			{
				if (gsm_returnStateSystem()->next == state_Game)
				{
					mainMenu_resetMainMenu();
					*dataStorage_getLives() = 5;
					UI_clearDraw();
					*dataStorage_getAliveBool() = true;
					gsm_returnStateSystem()->next = state_Game;
					currentMapNum = 0;
					game_loadMap(currentMapNum);
					music_Update();

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
			break;
		case state_Credits:
			credits_Update();
			if (gsm_IsChanging())
			{
				credits_Destructor();
				game_resetClock();
				system("cls");
				mainMenu_resetMainMenu();
			}
			break;
		case state_Game:
			time_spent = (double)(clock() - begin - prevTime) / CLOCKS_PER_SEC;
			arrayReader_draw();

			if (time_spent - prevTime >= timeLapse)
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
			UI_drawSkulls();
			input_checkInput();
			music_Update();
			break;
		case state_PauseMenu:
			PauseMenu_Update();
			break;
		case state_Victory:
			VictoryScreen_Update();
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
			else
				footstep_loop();
			break;
		case 2:
			dataStorage_setPlayerPosition(playerX, ++playerY);
			if (dataStorage_checkWall())
				dataStorage_setPlayerPosition(playerX, --playerY);
			else
				footstep_loop();
			break;
		case 3:
			dataStorage_setPlayerPosition(--playerX, playerY);
			if (dataStorage_checkWall())
				dataStorage_setPlayerPosition(++playerX, playerY);
			else
				footstep_loop();
			break;
		case 4:
			dataStorage_setPlayerPosition(++playerX, playerY);
			if (dataStorage_checkWall())
				dataStorage_setPlayerPosition(--playerX, playerY);
			else
				footstep_loop();
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
				PauseClearScreen();
				PauseMenu_Init();
				isPaused = !isPaused;
			}
			else
			{
				console_clear();
				UI_clearDraw();
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
	for (trap_counter = 5; trap_counter > 0;)
	{
		trap_counter--;
		destroyTrap(trap_counter);
	}

	for (torch_counter = 5; torch_counter > 0;)
	{
		torch_counter--;
		destroyTorch(torch_counter);
	}

	UI_clearDraw();

	FILE *stream;
	bool checkHeight = true;
	bool fileOpen = false;
	char *fileName = (char *)NULL, temp = 0;
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
		case 2:
			fileName = "Levels/3.txt";
			break;
		case 3:
			fileName = "Levels/4.txt";
			break;
		case 4:
			fileName = "Levels/5.txt";
			break;
	}

	fileOpen = (fopen_s(&stream, fileName, "r+t") == 0);

	if (fileOpen)
	{
		mapWidth = 0;
		mapHeight = 1;
		fread(&temp, sizeof(char), 1, stream);

		while (temp != '\n')
			mapWidth += (int)fread(&temp, sizeof(char), 1, stream);

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
				*(map + counter) = (char)atoi(&temp);
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

		dataStorage_EnemyInit((char)playerX, (char)playerY);

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

			enemy_spawnEnemy(x, y, (char)counter, patrol, x1, y1, x2, y2);

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
	char temp = 0;
	int counter = 0;

	fileOpen = (fopen_s(&stream, fileName, "r+t") == 0);

	if (fileOpen)
	{
		*fileWidth = 0;
		*fileHeight = 1;
		fread(&temp, sizeof(char), 1, stream);

		while (temp != '\n')
			*fileWidth += (int)fread(&temp, sizeof(char), 1, stream);

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
	
		fclose(stream);
		*(textstring + *fileWidth * *fileHeight - 1) = '\0';
		return textstring;
	}
	else
	{
		game_turnOffGame();
		return (char*)NULL;
	}
}



