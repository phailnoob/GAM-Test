#include "UI.h"
#include "Console.h"

const char *UI_torch[3] = {
	                        { "  \\*/" },
                            { "  // " },
                            { " //  " }
                          };


void game_borders()
{

	int j;

	/*corners*/
	console_setCursorPosition(0, 1);
	printf("%c", 201);
	console_setCursorPosition(0 , console_getConsoleHeight()/10*9);
	printf("%c", 200);
	console_setCursorPosition(console_getConsoleWidth()/10*9 , 1);
	printf("%c", 187);
	console_setCursorPosition(console_getConsoleWidth() /10*9, console_getConsoleHeight() /10*9);
	printf("%c", 188);

	/*top border*/
	console_setCursorPosition(1, 1);
	for (j = 0; j < console_getConsoleWidth()/10*9-1 ; j++)
		printf("%c", 205);

	/*Bottom border*/
	console_setCursorPosition(1, console_getConsoleHeight()/10*9);
	for (j = 0; j <= console_getConsoleWidth()/10*9-2; j++)
		printf("%c", 205);

	/*Left and right border*/
	for (j = 0; j < console_getConsoleHeight()/10*9 -2; j++)
	{
		console_setCursorPosition(0, 2 + j);
		printf("%c", 186);

		console_setCursorPosition(console_getConsoleWidth()/10*9, 2 + j);
		printf("%c", 186);
	}

}

void drawUI()
{
	int i, j;
	i = console_getConsoleHeight()/10*9;
	for (j = 0; j < (i - 2); j++)
	{
	console_setCursorPosition(30, 2 + j);
		printf("%c", 186);
	}

	console_setCursorPosition(1, 20);
	for (j = 0; j < 29; j++)
		printf("%c", 205);

} 



//int check_Active_Torch(int *torches[])
//{
//	int numOfTorch = 0;
//	for(numOfTorch = 0; *torch)
//}


void UI_drawtorches()
{
	int i;
	int UI_torch_pos = 2;
	for (i = 0; i < 3; i++)
	{
		console_setCursorPosition(2, 2);
			printf("Torches:");

		console_drawString(UI_torch_pos, 4+i, UI_torch[i], 12, sizeof(UI_torch-1));
		UI_torch_pos += 4;
		console_drawString(UI_torch_pos, 4 + i, UI_torch[i], 12, sizeof(UI_torch - 1));
		

	}
}
















