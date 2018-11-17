
#include <stdio.h>
#include "Game.h"
#include "Enemy.h"
#include "Console.h"
#include "Array Reader.h"
#include "Data Storage.h"
#include "Input.h"
#include "Torch.h"
#include "GameStateManager.h"
#include "MainMenu.h"

bool isRunning, mapUsed;

static int playerX, playerY, mapWidth, mapHeight; 
static int torch_counter;
/* TODO Make sure to clear up all these static variables if the player goes back to main menu*/

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

	torch_counter = 0;
}

bool game_isRunning()
{
	return isRunning;
}

void game_turnOffGame()
{
	isRunning = false;
	if (mapUsed)
		free(map);
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

void game_modifyLoadValue(int * value, char * temp, char chara, FILE *stream)
{
	*value = atoi(temp);

	while (*temp != chara)
	{
		fread(temp, sizeof(char), 1, stream);

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

		dataStorage_setMapData(map, mapWidth, mapHeight);
		arrayReader_setMap(mapWidth * mapHeight);

		dataStorage_EnemyInit(playerX, playerY);

		counter = 0;

		while (temp != '\n')
		{
			game_modifyLoadValue(&x, &temp, '/', stream);
			game_modifyLoadValue(&y, &temp, '\n', stream);
			enemy_spawnEnemy(x, y, counter);
			counter++;
		}

		dataStorage_TorchInit();
		dataStorage_setPlayerPosition(playerX, playerY);

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

