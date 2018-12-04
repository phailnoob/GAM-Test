/************************************************
Filename: Music.c
Author: Koh Joon Yee Marcus
DP Email: k.joonyeemarcus@digipen.edu
Course: GAM100

Brief Description:
FMOD music implementations
*************************************************/
#include "music.h"
#include "fmod.h"
#include "fmod_common.h"
#include "fmod_codec.h"
#include "fmod_dsp.h"
#include "fmod_dsp_effects.h"
#include "fmod_errors.h"
#include "fmod_output.h"
#include "Game.h"
#include "GameStateManager.h"

Music GameMusic;
bool isPlaying, ambience_playing = false;
char footstep_num;


void LoadSound()
{
	FMOD_RESULT result;
	FMOD_SOUND * sound;
	result = FMOD_System_CreateSound(GameMusic.fmodsystem, "Music/MainMenuLoop.wav", FMOD_LOOP_NORMAL, 0,GameMusic.sound + 0);
	if(result!= FMOD_OK)
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	
	result = FMOD_System_CreateSound(GameMusic.fmodsystem, "Music/Ambience.wav", FMOD_LOOP_NORMAL, 0,GameMusic.sound + 1);
	if(result!= FMOD_OK)
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));

	result = FMOD_System_CreateSound(GameMusic.fmodsystem, "Music/Chasing.wav", FMOD_DEFAULT, 0, GameMusic.sound + 2);
	if (result != FMOD_OK)
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));

	result = FMOD_System_CreateSound(GameMusic.fmodsystem, "Music/Step1.wav", FMOD_DEFAULT, 0, GameMusic.sound + 3);
	if (result != FMOD_OK)
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));

	result = FMOD_System_CreateSound(GameMusic.fmodsystem, "Music/Step2.wav", FMOD_DEFAULT, 0, GameMusic.sound + 4);
	if (result != FMOD_OK)
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));

	result = FMOD_System_CreateSound(GameMusic.fmodsystem, "Music/Step3.wav", FMOD_DEFAULT, 0, GameMusic.sound + 5);
	if (result != FMOD_OK)
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));

	result = FMOD_System_CreateSound(GameMusic.fmodsystem, "Music/Step4.wav", FMOD_DEFAULT, 0, GameMusic.sound + 6);
	if (result != FMOD_OK)
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));

}





void Music_Init()
{
	FMOD_RESULT result;

	footstep_num = 3;
	result = FMOD_System_Create(&GameMusic.fmodsystem);

	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = FMOD_System_Init(GameMusic.fmodsystem, 512, FMOD_INIT_NORMAL, 0);  // Initialize FMOD.
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}


	GameMusic.soundOn = true;
	isPlaying = false;
	LoadSound();
}




void music_PlaySound(char index)
{
	FMOD_RESULT result;

	result=	FMOD_System_PlaySound(GameMusic.fmodsystem, GameMusic.sound[index], NULL, 0,&(GameMusic.channel[index]));

	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

}



void music_Update()
{
	/*1) if mainmenu music is not playing, play music and loop(Mainmenuloop already initialised in forward looping mode */
	FMOD_RESULT result;
	FMOD_BOOL pause = true;

		if (!isPlaying)
		{
			music_PlaySound(0); /*plays main menu loop*/
			isPlaying = !isPlaying;
			
		}
		
		if (isPlaying)/*While in main menu wait for state to change to Game, then play */
		{
			if (gsm_returnStateSystem()->next == state_Game)
			{
				
				result = FMOD_Channel_SetPaused(GameMusic.channel[0], true);
				if (result != FMOD_OK)
				{
					printf("FMOD error in music_Update! (%d) %s\n", result, FMOD_ErrorString(result));
					exit(-1);
				}

				if (!ambience_playing)
				{
					music_PlaySound(1);
					ambience_playing = !ambience_playing;
				}
			}
		}

		result = FMOD_System_Update(GameMusic.fmodsystem);
		if (result != FMOD_OK)
		{
			printf("FMOD error in music_Update! (%d) %s\n", result, FMOD_ErrorString(result));
			exit(-1);
		}
}


void footstep_loop()
{
	music_PlaySound(footstep_num);
	footstep_num++;

	if (footstep_num > 6)
		footstep_num = 3;
	
}

void chasing_music()
{
	music_PlaySound(2);
}



