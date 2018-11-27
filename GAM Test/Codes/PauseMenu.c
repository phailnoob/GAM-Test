/************************************************
Filename: PauseMenu.c
Author: Toh Kai Liang
DP Email: toh.k@digipen.edu
Course: GAM100

Brief Description:
PauseMenu functions
*************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include "PauseMenu.h"
#include "GameStateManager.h"

/* input variables */
static int keyPress, keyDown;
static bool keyPressed;

bool isPaused;

/* border, padding, margin variables */
static int borderWidth, borderHeight;
static int vertiPadding, horizPadding;
static int lineSpace;
static int dividerPaddingLeft;
static int dividerPaddingTop;
static int toolTipHeight;

/* option variables */
int pointingAt;
int optionPtrX, optionPtrY;
int prevPosX, prevPosY;

/* initialize pause menu */
void PauseMenu_Init()
{
	keyPress = -1, keyDown = -1;
	keyPressed = false;

	isPaused = 0;

	borderWidth = 80;
	borderHeight = 24;
	vertiPadding = 2;
	horizPadding = 4;
	lineSpace = 2;
	dividerPaddingLeft = 16;
	dividerPaddingTop = 15;
	toolTipHeight = 3;

	pointingAt = 1;
	optionPtrX = (console_getConsoleWidth() - borderWidth) / 2 + horizPadding + 9;
	optionPtrY = (console_getConsoleHeight() - borderHeight) / 2 + vertiPadding;
	prevPosX = optionPtrX;
	prevPosY = optionPtrY;

	MoveBichGetOutTheWay();
	DrawBorder();
	DrawOptions();
	DrawToolTips(3);
}

/* pause menu update call */
void PauseMenu_Update()
{
	PauseMenu_CheckInput();
}

/* clear area behind pause menu */
void MoveBichGetOutTheWay()
{
	int i, j;

	for (i = 0; i < borderWidth; i++)
	{
		for (j = 0; j < borderHeight; j++)
		{
			console_setCursorPosition((console_getConsoleWidth() - borderWidth) / 2 + i,
				(console_getConsoleHeight() - borderHeight) / 2 + j);
			printf("%c", 32);
		}
	}
}

/* draw pause menu border */
void DrawBorder()
{
	int i = 0;
	int offsetX = 10;

	/* border */
	console_setCursorPosition((console_getConsoleWidth() - borderWidth) / 2,
		(console_getConsoleHeight() - borderHeight) / 2);

	printf("%c", 201);

	for (i = 0; i < borderWidth - 2; ++i)
		printf("%c", 205);

	printf("%c", 187);

	for (i = 0; i < borderHeight - 2; ++i)
	{
		console_setCursorPosition((console_getConsoleWidth() - borderWidth) / 2,
			(console_getConsoleHeight() - borderHeight) / 2 + (i + 1));
		printf("%c", 186);

		console_setCursorPosition((console_getConsoleWidth() - borderWidth) / 2 + (borderWidth - 1),
			(console_getConsoleHeight() - borderHeight) / 2 + (i + 1));
		printf("%c", 186);
	}

	console_setCursorPosition((console_getConsoleWidth() - borderWidth) / 2,
		(console_getConsoleHeight() - borderHeight) / 2 + (borderHeight - 1));

	printf("%c", 200);

	for (i = 0; i < borderWidth - 2; ++i)
		printf("%c", 205);

	printf("%c", 188);

	/* horizontal divider */
	console_setCursorPosition((console_getConsoleWidth() - borderWidth) / 2,
		(console_getConsoleHeight() - borderHeight) / 2 + dividerPaddingTop);
	printf("%c", 204);

	for (i = 0; i < borderWidth - 2; ++i)
	{
		console_setCursorPosition((console_getConsoleWidth() - borderWidth) / 2 + (i + 1),
			(console_getConsoleHeight() - borderHeight) / 2 + dividerPaddingTop);
		printf("%c", 205);
	}

	printf("%c", 185);

	/* vertical divider */
	console_setCursorPosition((console_getConsoleWidth() - borderWidth) / 2 + dividerPaddingLeft,
		(console_getConsoleHeight() - borderHeight) / 2);
	printf("%c", 203);

	for (i = 0; i < borderHeight - (borderHeight - dividerPaddingTop); ++i)
	{
		console_setCursorPosition((console_getConsoleWidth() - borderWidth) / 2 + dividerPaddingLeft,
			(console_getConsoleHeight() - borderHeight) / 2 + (i + 1));
		printf("%c", 186);
	}

	console_setCursorPosition((console_getConsoleWidth() - borderWidth) / 2 + dividerPaddingLeft,
		(console_getConsoleHeight() - borderHeight) / 2 + borderHeight - (borderHeight - dividerPaddingTop));
	printf("%c", 202);
}

/* draw options */
void DrawOptions()
{
	console_setCursorPosition(prevPosX, prevPosY);
	printf(" ");

	prevPosX = optionPtrX;
	prevPosY = optionPtrY;

	console_setCursorPosition(optionPtrX, optionPtrY);
	printf("%c", 60);

	console_setCursorPosition((console_getConsoleWidth() - borderWidth) / 2 + horizPadding,
		(console_getConsoleHeight() - borderHeight) / 2 + vertiPadding);
	printf("Resume");

	console_setCursorPosition((console_getConsoleWidth() - borderWidth) / 2 + horizPadding,
		(console_getConsoleHeight() - borderHeight) / 2 + vertiPadding + lineSpace);
	printf("Options");

	console_setCursorPosition((console_getConsoleWidth() - borderWidth) / 2 + horizPadding,
		(console_getConsoleHeight() - borderHeight) / 2 + vertiPadding + 2 * lineSpace);
	printf("Exit");
}

/* draw tool tips */
void DrawToolTips(int state)
{
	switch (state)
	{
	case 3:
		console_setCursorPosition((console_getConsoleWidth() - borderWidth) / 2 + horizPadding + dividerPaddingLeft,
			(console_getConsoleHeight() - borderHeight) / 2 + vertiPadding + 2 * toolTipHeight);
		printf("Lala (l)");

		console_setCursorPosition((console_getConsoleWidth() - borderWidth) / 2 + horizPadding + dividerPaddingLeft,
			(console_getConsoleHeight() - borderHeight) / 2 + vertiPadding + 1 + 2 * toolTipHeight);
		printf(" - Hai");

	case 2:
		console_setCursorPosition((console_getConsoleWidth() - borderWidth) / 2 + horizPadding + dividerPaddingLeft,
			(console_getConsoleHeight() - borderHeight) / 2 + vertiPadding + toolTipHeight);
		printf("Trap (y)");

		console_setCursorPosition((console_getConsoleWidth() - borderWidth) / 2 + horizPadding + dividerPaddingLeft,
			(console_getConsoleHeight() - borderHeight) / 2 + vertiPadding + 1 + toolTipHeight);
		printf(" - Hey");

	case 1:
		console_setCursorPosition((console_getConsoleWidth() - borderWidth) / 2 + horizPadding + dividerPaddingLeft,
			(console_getConsoleHeight() - borderHeight) / 2 + vertiPadding);
		printf("Torch (t)");

		console_setCursorPosition((console_getConsoleWidth() - borderWidth) / 2 + horizPadding + dividerPaddingLeft,
			(console_getConsoleHeight() - borderHeight) / 2 + vertiPadding + 1);
		printf(" - Brighten up your life <3");
		break;

	default:
		break;
	}
}

/* draw option pointer */
void PointAtOption(int key)
{
	switch (key)
	{
	case 72: /* up */
		if (pointingAt > 1)
		{
			optionPtrY -= 2;
			--pointingAt;
			DrawOptions();
		}
		keyPressed = false;
		break;
	case 80: /* down */
		if (pointingAt < 3)
		{
			optionPtrY += 2;
			++pointingAt;
			DrawOptions();
		}
		keyPressed = false;
		break;

	case 27: /* esc */
		game_playerAction(7);
		keyPressed = false;
		break;

	case 13: /* enter */
		switch (pointingAt)
		{
		case 1:
			game_playerAction(7);
			break;

		case 2:
			break;

		case 3:
			break;

		default:
			break;
		}
		break;
	}
}

/* check for input for pause menu */
void PauseMenu_CheckInput()
{
	keyDown = _kbhit();

	if (keyDown)
	{
		keyPress = _getch();
		keyPressed = true;
		PointAtOption(keyPress);
		printf("%d", keyPress);
	}
}