#include "GameStateManager.h"


static GameState gsm_GS;


void gsm_gameStateInit()
{
	gsm_GS.current = state_mainMenu;
	gsm_GS.next = state_mainMenu;
	gsm_GS.previous = state_mainMenu;

}

State gsm_returnCurrentState()
{
	return gsm_GS.current;
}
GameState * gsm_returnStateSystem()
{
	return &gsm_GS;
}

bool gsm_IsChanging()
{
	return (gsm_GS.current != gsm_GS.next);
}


bool gsm_IsValid(State state)
{
	return (state >= 0 && state <= 5);
}

void gsm_setNextState(State state)
{
	gsm_GS.next = state;
}






