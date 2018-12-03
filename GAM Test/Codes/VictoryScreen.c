#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include "VictoryScreen.h"
#include "GameStateManager.h"
#include "Console.h"

/* input variables */
static int keyPress, keyDown;
static bool keyPressed;

const char * youWin[6] = 
{

{"_____.___.                      .__        "},
{"\\__  |   | ____  __ __  __  _  _|__| ____  "},
{" /   |   |/  _ \\|  |  \\ \\ \\/ \\/ /  |/    \\ "},
{" \\____   (  <_> )  |  /  \\     /|  |   |  \\"},
{" / ______|\\____/|____/    \\/\\_/ |__|___|  /"},
{" \\/                                     \\/ "}

};

void VictoryScreen_Init()
{
	DrawVictory();
}

void VictoryScreen_Update()
{
	Victory_CheckInput();
}

void DrawVictory()
{
	int i;
	
	for (i = 0; i < 6; i++)
	{
		console_setCursorPosition(console_getConsoleWidth()/2 - 22, console_getConsoleHeight()/3 + i);
		printf("%s", youWin[i]);
	}
}

/* input action */
void Victory_InputAction(int key)
{
	switch (key)
	{
	case 27: /* esc */
		console_clear();
		gsm_returnStateSystem()->next = state_mainMenu;
		keyPressed = false;
		break;
	}
}

/* input manager */
void Victory_CheckInput()
{
	keyDown = _kbhit();

	if (keyDown)
	{
		keyPress = _getch();
		keyPressed = true;
		Victory_InputAction(keyPress);
	}
}