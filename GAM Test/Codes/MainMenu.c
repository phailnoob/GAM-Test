/************************************************
Filename: MainMenu.c
Author: Muhammad Adam Bin Mohamad Amin
DP Email: m.muhammadadambin@digipen.edu
Course: GAM100

Brief Description:
Main Menu functions
*************************************************/

#include "Console.h"
#include <windows.h>
#include <stdio.h>
#include "MainMenu.h"
#include <stdbool.h>
#include "GameStateManager.h"


char selected = 1;
int keyPress, keyDown;
bool keyPressed = false;
bool logoDrawn = 0;

const char  *logo[12] = {                                                                                                                                            
                                                                                                                                                                                                        
                                                                                                                                                                                                        
                                                                                                                                                                                                        
                                                                                                                                                                                                        
	{"        .''''''''''''..       .''''''''''''''.      .';:::;,.                  ....           .''''''.      .'''.   .'''''.      .''''.   .''''''''''''''.      .';:::;'.     .'''''''''''''        "},
	{"      lNNNNNNNNNNNNXKkc.   ,0NNNNNNNNNNNNNX:   .:xKNWMMMWNXk;               :0KKd.         .xNNNNNNO,    ;KNNNx.  lXNNNNK:    'ONNN0,  :KNNNNNNNNNNNNN0;   .ckKNWMMMWNKx,  cXNNNNNNNNNNNN0,		  "},
	{"     .OMMMMWNXXNWMMMMMWd.  lWMMMMWNNNNNNNNO' .c0WMMMWXXWMMMMXc             .kMMNl          ;KMMMMMMMO'  .dWMMWl  .OMMMMMMK:   cNMMMx. .dWMMMMWNNNNNNNNk. .lKWMMMNXXWMMMMK;.kMMMMMMMMMMMMWx.	      "},
	{"     :XMMMM0:...:KMMMMMO. .kMMMMNo,'''''''. .xNMMMWk;..lXMMMMO.        .,:,cXMM0l;.        oWMMMMMMMWk. '0MMMK,  :XMMMMMMM0, .xMMMNc  '0MMMMXl''''''''. 'kWMMMNx,..oNMMMMx',::dXMMMMXo:::.          "},
	{"    .dWMMMWk,..'lXMMMMNl  ;XMMMMXd:::::;.  .dWMMMWx.   .d0OOOo.     .;dO0xcxWMNxxXKd'     .OMMMMWWMMMWx.cNMMWx. .dWMMWWMMMWO';KMMM0'  cNMMMMKo:::::;.  .kWMMMNo.   .x0OOOl.   :XMMMWd.              "},
	{"    '0WWWWWNXKXNWWWWN0c. .oNWWWWWWWWWWW0,  :XWWWW0,               .:O0dll:cKMM0lccdXKc    :XWWWWOONWWWXdxNWWX:  '0WWW0kXWWWNkdXWWNo  .xWWWWWWWWWWWWO.  lNWWWWO.              .dWWWWX:               "},
	{"    cXNNNNNXXNNNNNXx;.   'ONNNNXK000000l. .dNNNNNd.              .xKd:ldl;dWMNl,xk:lXK;  .oNNNNXc,kNNNNXXNNNk.  cXNNNd'oXNNNXXNNNK;  ,0NNNNX000000Oc  .xNNNNXl               'ONNNNk.               "},
	{"   .dXXXXKo'c0XXXXKc     :KXXXXx'......   .xXXXXXl    .coolc'   'OXl;do. 'OWWk. .xk;xNl  'kXXXXO' 'kXXXXXXXXl  .dXXX0; .dXXXXXXXXd.  lKXXXXo.......   'kXXXXK:    .lollc.    :KXXXKl                "},
	{"   ,OKKKKk' .dKKKKKx.   .oKKKKKo'........ .oKKKKKx'..,dKKKKx'   ;d:.;c.  .,;,.   ,c':d,  :0KKKKo.  ,OKKKKKKO,  'kKKKx.  .xKKKKKK0:  .dKKKK0l........  .dKKKKKo'..;xKKKKd.   .oKKKKk'                "},
	{"   c00000l.  :O0000O;   'x000000OOOOOOOx,  .d00000OkkO000Ol.            'oddo.          .o000Ox,    ;k00000o.  c0000c    'x00000x'  ,k000000OOOOOOOx'  ,x00000Okk0000kc.    'k0000o.                "},
	{"  .oOkOOx,   .dOOOOOl.  ;kOkOOOOOOOOOOOo.   .:okOOOOOOxo:.             .dWWWk.          'dOOOo;.     :kkOOk;  .oOOOd'     ,xOOOkc.  :kOOOOOOkkOOOOkl.   .cdkO0OOOkxo;.      :kOOkk;                 "},
	{"   ......     .......   ................       .'',,'..                 ';;;.            .....        .....    .....       ......   ................       .',,,'..         ......                  "},
                                                                                                                                                                                                        
                                                                                                                                                                                                        
                                                                                                                                                                                                        
                                                                                                                                                                                                        
                                                                                                                                                                                                        

};

/*Reset main menu variables*/
void mainMenu_Reset()
{
	logoDrawn = 0;
}

/*Handles arrow keys input*/
void mainMenu_arrow(int key,bool * keyPressed)
{
	switch(key)
	{
		case 72:
			if (selected == 1)
			{
				selected = 4;
			}
			else
			{
				selected--;
			}
			*keyPressed = false;
			break;
		case 80:
			if (selected == 4)
			{
				selected = 1;
			}
			else
			{
				selected++;
			}
			*keyPressed = false;
			break;
		case 0:
			switch (selected)
			{
			case 1:/*Changes state to Game*/
				gsm_setNextState(state_Game);
				mainMenu_Reset();
				system("cls");
				break;
			case 2:/*Changes state to Options*/
				break;
			case 3:/*Changes state to Credits*/
				break;
			case 4:/*Changes state to Exit*/
				break;
			}
			break;
	};
}

/*Gets in raw keyboard input*/
void mainMenu_checkInput()
{
	keyPress = _getch();
	keyDown = _kbhit();

	if (keyDown)
	{
		keyPressed = true;
	}
	else
	{
		if (keyPressed)
			mainMenu_arrow(keyPress, &keyPressed);
	}
}

/*Draws main menu buttons*/
void mainMenu_drawButtons()
{
	console_drawString(console_getConsoleWidth() / 2 - 2, console_getConsoleHeight() / 3 * 2,   "Play",    selected == 1 ? 3 : 14,4);
	console_drawString(console_getConsoleWidth() / 2 - 3, console_getConsoleHeight() / 3 * 2+1, "Options", selected == 2 ? 3 : 14,7);
	console_drawString(console_getConsoleWidth() / 2 - 3, console_getConsoleHeight() / 3 * 2+2, "Credits", selected == 3 ? 3 : 14,7);
	console_drawString(console_getConsoleWidth() / 2 - 2, console_getConsoleHeight() / 3 * 2+3, "Exit",    selected == 4 ? 3 : 14,4);
}

/*Draws logo*/
void mainMenu_drawLogo()
{
	for (int i = 0; i < 12; i++)
	{
		console_drawString(console_getConsoleWidth() / 9, console_getConsoleHeight() / 7 + i, logo[i], 7, 196);
	}
}



/*Handles main menu updates. Only call this outside of this function*/
void mainMenu_Update()
{
	if (!logoDrawn)
	{
		mainMenu_drawLogo();
		logoDrawn = 1;
	}
	mainMenu_drawButtons();
	mainMenu_checkInput();

}



























