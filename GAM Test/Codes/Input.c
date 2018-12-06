#include <conio.h>
#include <stdbool.h>
#include "Input.h"
#include "Game.h"
#include "Enemy.h"
#include "GameStateManager.h"

static int keyPress, keyDown;
static bool keyPressed;
bool devMode = false;

void input_init()
{
	keyPress = -1;
	keyDown = -1;
	keyPressed = false;
}

void input_wasd(int key)
{
	switch (key)
	{
		case 87:
		case 119:
			if (*dataStorage_getAliveBool() == true)
			{
				game_playerAction(1);
				keyPressed = false;
			}
			break;
		case 83:
		case 115:
			if (*dataStorage_getAliveBool() == true)
			{
				game_playerAction(2);
				keyPressed = false;
			}
			break;
		case 65:
		case 97:
			if (*dataStorage_getAliveBool() == true)
			{
				game_playerAction(3);
				keyPressed = false;
			}
			break;
		case 68:
		case 100:
			if (*dataStorage_getAliveBool() == true)
			{
				game_playerAction(4);
				keyPressed = false;
			}
			break;
		case 84:
		case 116: /* 't' */
			if (*dataStorage_getAliveBool() == true)
			{
				game_playerAction(5);
				keyPressed = false;
			}
			break;
		case 89:
		case 121: /* 'y' */
			if (*dataStorage_getAliveBool() == true)
			{
				game_playerAction(6);
				keyPressed = false;
			}
			break;

		case 27: /* esc */
			if (*dataStorage_getAliveBool() == false)
			{
				console_clear();
				gsm_returnStateSystem()->next = state_mainMenu;
				
			}
			/*else
			{
				game_playerAction(7);
			}*/
			if (*dataStorage_getAliveBool() == true)
			{
				game_playerAction(7);
			}
			else
			{
				console_clear();
				gsm_returnStateSystem()->next = state_mainMenu;
			}
			keyPressed = false;
			break;

		case 96:
			devMode = !devMode;
			break;

		case 49:
			if (devMode)
			{
				SetMapNum(0);
				console_clear();
				game_loadMap(0);
			}
			break;

		case 50:
			if (devMode)
			{
				SetMapNum(1);
				console_clear();
				game_loadMap(1);
			}
			break;

		case 51:
			if (devMode)
			{
				SetMapNum(2);
				console_clear();
				game_loadMap(2);
			}
			break;

		case 52:
			if (devMode)
			{
				SetMapNum(3);
				console_clear();
				game_loadMap(3);
			}
			break;

		case 53:
			if (devMode)
			{
				SetMapNum(4);
				console_clear();
				game_loadMap(4);
			}
			break;
	}
}

void input_arrow(int key)
{
	switch (key)
	{
		case 72:
			if (*dataStorage_getAliveBool() == true)
			{
				game_playerAction(1);
				keyPressed = false;
			}
			break;
		case 80:
			if (*dataStorage_getAliveBool() == true)
			{
				game_playerAction(2);
				keyPressed = false;
			}
			break;
		case 75:
			if (*dataStorage_getAliveBool() == true)
			{
				game_playerAction(3);
				keyPressed = false;
			}
			break;
		case 77:
			if (*dataStorage_getAliveBool() == true)
			{
				game_playerAction(4);
				keyPressed = false;
			}
			break;

	}
}

void input_checkInput()
{
	keyDown = _kbhit();

	if (keyDown)
	{
		keyPress = _getch();
		keyPressed = true;
		input_wasd(keyPress);
	}
	else
	{
		if (keyPressed)
			input_arrow(keyPress);
		input_wasd(keyPress);
	}
}
