#pragma once


#include "Data Storage.h"

typedef enum State
{
	state_splashScreen,
	state_mainMenu,
	state_Options,
	state_Credits,
	state_Game,
	state_Exit = -1,
	state_Transition = -2,

}State;

typedef struct
{
	State	current;	/* Index of the current game state. */
	State	previous;	/* Index of the previous game state. */
	State	next;		/* Index of the next game state. */

} GameState;

void gsm_gameStateInit();
State gsm_returnCurrentState();
GameState* gsm_returnStateSystem();

bool gsm_IsValid(State state);
bool gsm_IsChanging();
void gsm_setNextState(State state);

