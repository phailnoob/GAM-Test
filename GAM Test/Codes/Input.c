
#include <conio.h>
#include <stdbool.h>
#include "Input.h"
#include "Game.h"

static int keyPress, keyDown;
static bool keyPressed;

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
			game_playerAction(1);
			keyPressed = false;
			break;
		case 83:
		case 115:
			game_playerAction(2);
			keyPressed = false;
			break;
		case 65:
		case 97:
			game_playerAction(3);
			keyPressed = false;
			break;
		case 68:
		case 100:
			game_playerAction(4);
			keyPressed = false;
			break;
	}
}

void input_arrow(int key)
{
	switch (key)
	{
		case 72:
			game_playerAction(1);
			keyPressed = false;
			break;
		case 80:
			game_playerAction(2);
			keyPressed = false;
			break;
		case 75:
			game_playerAction(3);
			keyPressed = false;
			break;
		case 77:
			game_playerAction(4);
			keyPressed = false;
			break;
	}
}

void input_checkInput()
{
	keyPress = _getch();
	keyDown = _kbhit();

	if (keyDown)
	{
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
