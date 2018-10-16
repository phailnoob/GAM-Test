
#include <conio.h>
#include "Input.h"
#include "Game.h"

static int keyPress, keyDown;

void input_init()
{
	keyPress = -1;
	keyDown = -1;
}

void input_checkInput()
{
	keyPress = _getch();
	keyDown = _kbhit();

	if (keyDown)
	{
		switch (keyPress)
		{
			case 87:
			case 119:
				game_playerAction(1);
				break;
			case 83:
			case 115:
				game_playerAction(2);
				break;
			case 65:
			case 97:
				game_playerAction(3);
				break;
			case 68:
			case 100:
				game_playerAction(4);
				break;
		}
	}
	else
	{
		switch (keyPress)
		{
			case 72:
				game_playerAction(1);
				break;
			case 80:
				game_playerAction(2);
				break;
			case 75:
				game_playerAction(3);
				break;
			case 77:
				game_playerAction(4);
				break;
		}
	}
}
