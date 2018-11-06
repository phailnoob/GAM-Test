
/*
This is a simple Test Program.

It's purpose is to make a simple map with a player,
letting the player remain stationary in the center of the screen while the map moves around it as he moves.

Included in this test will be hide cursor, 2D arrays, "collision" detection.

Possibly included will be text file reading and parsing into resizeable array.
*/

#include "Game.h"
#include<stdio.h>
#include<conio.h>

int main()
{
//	int test = 0, test2 = -1;

	game_init();

	while (game_isRunning())
	{
/*		test = _getch();
		test2 = _kbhit();
		printf("YOU PRESSED %c & %d\n", test, test2);
*/		game_update();
	}

    return 0;
}

