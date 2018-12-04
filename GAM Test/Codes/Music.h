/************************************************
Filename: Music.h
Author: Koh Joon Yee Marcus
DP Email: k.joonyeemarcus@digipen.edu
Course: GAM100

Brief Description:
FMOD music header includes and struct definintion
*************************************************/


#include "fmod.h" //FMOD Ex
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "enemy.h"
/*struct*/
/********STRUCT DEFINITION ********/

typedef struct Music {
	bool soundOn; //is sound on?
	bool soundPossible; //is it possible to play sound?
	char * currentSound; //currently played sound
	bool menuLoopPlaying;


	//FMOD-specific stuff
	FMOD_SYSTEM * fmodsystem;
	FMOD_SOUND * sound[10];
	FMOD_CHANNEL * channel[10];
	FMOD_CHANNELGROUP * group;
	FMOD_RESULT* result;
	
	

}Music;

void Music_Init();
void music_Update();


/*
---Sound list---
00 - MainMenuLoop.wav
01 - Ambience.wav
02 - Chasing.wav
03 - Step1.wav
04 - Step2.wav
05 - Step3.wav
06 - Step4.wav
*/
void music_PlaySound(char index);
void footstep_loop();
void chasing_music();
void LoadSound();

