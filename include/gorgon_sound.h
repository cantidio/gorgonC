#ifndef SOUND
#define SOUND
#include <stdio.h>
#include <stdlib.h>
#include "../fmod/include/fmod.h"
#include "../fmod/include/fmod_errors.h"
#include "gorgon_error.h"
#include <allegro.h>
#define gorgonSound FMOD_SOUND
#define GORGON_MUSIC	1
#define GORGON_VOICE	2
#define GORGON_EFFECT	3
typedef struct
{
	FMOD_SYSTEM *system;			//o sistema de audio
	FMOD_CHANNEL *musicChannel;		//o canal de músicas
	FMOD_CHANNEL *voiceChannel;		//o canal de voz
	FMOD_CHANNEL *effectsChannel;		//o canal de efeitos
	float musicVolume;			//o volume do canal de músicas
	float voiceVolume;			//o volume do canal de voz
	float effectsVolume;			//o volume do canal de efeitos
	short maxChannels;			//o número máximo de sons tocados ao mesmo tempo
	short audio;				//se o audio está ligado ao nao
	short music;				//se o canal de música está ligado ou não
	short voice;				//se o canal de voz está ligado ou não
	short effects;				//se o canal de efeitos está ligado ou não
}gorgonAudio;


int gorgonGetDefaultAudioConfig(gorgonAudio *audio);
int gorgonLoadAudioConfigBin(gorgonAudio *audio,char *filename);
int gorgonSaveAudioConfigBin(gorgonAudio *audio,char * filename);
//int saveAudioConfig(gorgonAudio *audio);
//int loadAudioConfig(gorgonAudio *audio);
int gorgonCreateSoundSystem(gorgonAudio *audio,char *filename);
int gorgonDestroySoundSystem(gorgonAudio *audio);
int gorgonLoadSound(gorgonSound **sound,char *name,gorgonAudio *audio);
int gorgonDestroySound(gorgonSound *sound);
int gorgonPlaySound(gorgonSound *sound,gorgonAudio *audio,short type);
int gorgonStopChannel(gorgonAudio *audio,int channel);
int gorgonToggleSound(gorgonAudio *audio);


#endif
