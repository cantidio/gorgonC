#include "../include/gorgon_sound.h"

/**
 * getDefaultAudioConfig
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 21/11/2007
 * @final: 19/05/2008
 * @param gorgonAudio* : apontador para o sistema sonoro
 * @return: int gorgon_error
 * @abstract: função que pega as configurações default de audio
 */
int gorgonGetDefaultAudioConfig(gorgonAudio *audio)
{
	if(audio!=NULL)
	{
		audio->audio		= 1;
		audio->music		= 1;
		audio->voice		= 1;
		audio->effects		= 1;
		audio->maxChannels	= 32;
		audio->musicVolume	= 0.3;
		audio->voiceVolume	= 0.5;
		audio->effectsVolume	= 0.4;
		return GORGON_OK;
	}
	return GORGON_INVALID_AUDIO;
}
/**
 * função para carregar a configuração de audio binário da memória
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 	15/05/2008
 * @final: 	19/05/2008
 * @param:	gorgonAudio * apontador para um gorgonAudio que deseja-se guardar a configuração
 * @param:	char * ponteiro para a mémoria da configuração
 * @param:	int *ofs posição na memória cedida que se encontra o arquivo desejado
 * @exemple:
 *
 * gorgonAudio audio;
 * char *data;
 * int ofs=0;
 *
 * if(gorgonLoadAudioConfigBinFromMemory(&audio,data,&ofs)!=GORGON_OK)
 *		printf("erro!\n");
 */
int gorgonLoadAudioConfigBin_fm(gorgonAudio *audio,char *data,int *ofs)
{
	float 	*musicVolume;
	float 	*voiceVolume;
	float 	*effectsVolume;
	short 	*maxChannels;
	short 	*audioOn;
	short 	*musicOn;
	short 	*voiceOn;
	short 	*effectsOn;
	if(audio!=NULL)
	{
		if(data!=NULL && ofs!=NULL)
		{
			musicVolume		=(float *)&data[*ofs];	(*ofs)+=sizeof(float);
			voiceVolume		=(float *)&data[*ofs];	(*ofs)+=sizeof(float);
			effectsVolume		=(float *)&data[*ofs];	(*ofs)+=sizeof(float);
			maxChannels		=(short *)&data[*ofs];	(*ofs)+=sizeof(short);
			audioOn			=(short *)&data[*ofs];	(*ofs)+=sizeof(short);
			musicOn			=(short *)&data[*ofs];	(*ofs)+=sizeof(short);
			voiceOn			=(short *)&data[*ofs];	(*ofs)+=sizeof(short);
			effectsOn		=(short *)&data[*ofs];	(*ofs)+=sizeof(short);
			
			audio->musicVolume	=*musicVolume;
			audio->voiceVolume	=*voiceVolume;
			audio->effectsVolume	=*effectsVolume;
			audio->maxChannels	=*maxChannels;
			audio->audio		=*audioOn;
			audio->music		=*musicOn;
			audio->voice		=*voiceOn;
			audio->effects		=*effectsOn;
			return GORGON_OK;
		}
		return GORGON_INVALID_MEMORY;
	}
	return GORGON_INVALID_AUDIO;
}
/**
 * função para carregar a configuração de audio de um arquivo binário
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 	15/05/2008
 * @final: 	15/05/2008
 * @param:	gorgonAudio * apontador para um gorgonAudio que deseja-se guardar a configuração
 * @param:	char * string com o nome do arquivo binário
 * @exemple:
 *
 * gorgonAudio audio;
 *
 * if(gorgonLoadAudioConfigBin(&audio,"audio.bin")!=GORGON_OK)
 *		printf("erro!\n");
 */
int gorgonLoadAudioConfigBin(gorgonAudio *audio, char *filename)
{
	FILE 	*file;
	char 	*data;
	int 	ofs=0,x=0;
	long 	size=file_size(filename);
	int	error;
	if(size>0)
	{
		file=fopen(filename,"rb");
		data=(char *)malloc(size);
		if(data!=NULL)
		{
			
			fread(&(data[0]),1,size, file);
			fclose(file);
			error=gorgonLoadAudioConfigBin_fm(audio,data,&ofs);
			free(data);
			return error;
		}
		fclose(file);
		return GORGON_MEMORY_ERROR;
	}
	gorgonGetDefaultAudioConfig(audio);
	printf("file %s not found.\nCreating other with default values.\n",filename);
	return gorgonSaveAudioConfigBin(audio,filename);
}
/**
 * função para salvar as configurações em um arquivo binário
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 16/05/2008
 * @final: 16/05/2008
 * @param: gorgonAudio *, apontador para o gorgonAudio que possui as confugurações que deseja-se salvar no arquivo
 * @param: char *, string com o nome do arquivo de saída
 * @return: int error
 * @exemple:
 *
 * gorgonAudio audio;
 *
 * if(gorgonSaveAudioConfigBin(&audio,"audioConf.bin")!=GORGON_OK)
 *		printf("erro!\n");
 */
int gorgonSaveAudioConfigBin(gorgonAudio *audio,char * filename)
{
	FILE *f;
	if(audio!=NULL)
	{
		f=fopen(filename,"wb");
		if(f!=NULL)
		{
			fwrite(&audio->musicVolume	,1,sizeof(float),f);
			fwrite(&audio->voiceVolume	,1,sizeof(float),f);
			fwrite(&audio->effectsVolume,1,sizeof(float),f);
			fwrite(&audio->maxChannels	,1,sizeof(short),f);
			fwrite(&audio->audio		,1,sizeof(short),f);
			fwrite(&audio->music		,1,sizeof(short),f);
			fwrite(&audio->voice		,1,sizeof(short),f);
			fwrite(&audio->effects		,1,sizeof(short),f);
			fclose(f);
			return GORGON_OK;
		}
		return GORGON_FILE_CANNOT_WRITE;
	}
	return GORGON_INVALID_AUDIO;
}
/**
 * saveAudioConfig
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 21/11/2007
 * @param gorgonAudio* : apontador para o sistema sonoro
 * @return: int
 * @abstract: função que salva as configurações de audio em um arquivo
 */
/*int saveAudioConfig(gorgonAudio *audio)
{
	FILE *arq;
	arq=fopen("./config/audio.cfg","w");
	if(arq==NULL) return 0;
	fprintf(arq,"Audio\t\t\t= %d\t\t\t; 1 -> ligado, 0-> desligado\n",audio->audio);
	fprintf(arq,"Channels\t\t= %d\t\t; número de canais de audio suportados\n\n",audio->maxChannels);
	
	fprintf(arq,"Music\t\t\t= %d\t\t\t; 1-> ligado, 0-> desligado\n",audio->music);
	fprintf(arq,"Music_Volume\t= %d\t\t;volume de 0 a 100\n\n",(int)(audio->musicVolume*100));
	
	fprintf(arq,"Voice\t\t\t= %d\t\t\t; 1-> ligado, 0-> desligado\n",audio->voice);
	fprintf(arq,"Voice_Volume\t= %d\t\t;volume de 0 a 100\n\n",(int)(audio->voiceVolume*100));
	
	fprintf(arq,"Effects\t\t\t= %d\t\t\t; 1-> ligado, 0-> desligado\n",audio->effects);
	fprintf(arq,"Effects_Volume\t= %d\t\t; volume de 0 a 100\n\n",(int)(audio->effectsVolume*100));
	return 1;
}*/
/**
 * loadAudioConfig
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 21/11/2007
 * @param gorgonAudio* : apontador para o sistema sonoro
 * @return: int
 * @abstract: função que carrega do arquivo as configurações de audio
 */
/*int loadAudioConfig(gorgonAudio *audio)
{
	FILE *arq;
	char *line, *word,**array;
	int number;
	getDefaultAudioConfig(audio);
	if(file_size("./config/audio.cfg")<1)
	{
		printf("file audio.cfg not found.\nCreating other with default values.\n");
		if(!saveAudioConfig(audio)) return 0;
		return 1;
	}
	arq=fopen("./config/audio.cfg","r");
	if(arq==NULL) return 0;
	while(!feof(arq))
	{
		line=readLine(arq);
		takeOut(' ',line); takeOut('\t',line);
		if(line!=NULL)
		{
			if(strncasecmp(line,"audio",5)==0)
			{
				array=explode('=',line,&number);
				if(number>1) audio->audio=atoi(array[1]);
				freeExplodedArray(array,number);
			}
			else if(strncasecmp(line,"channels",8)==0)
			{
				array=explode('=',line,&number);
				if(number>1) audio->maxChannels=atoi(array[1]);
				freeExplodedArray(array,number);
			}
			else if(strncasecmp(line,"music_volume",12)==0)
			{
				array=explode('=',line,&number);
				if(number>1) audio->musicVolume=(float)atoi(array[1])/100;
				freeExplodedArray(array,number);
			}
			else if(strncasecmp(line,"music",5)==0)
			{
				array=explode('=',line,&number);
				if(number>1) audio->music=atoi(array[1]);
				freeExplodedArray(array,number);
			}
			else if(strncasecmp(line,"voice_volume",12)==0)
			{
				array=explode('=',line,&number);
				if(number>1) audio->voiceVolume=(float)atoi(array[1])/100;
				freeExplodedArray(array,number);
			}
			else if(strncasecmp(line,"voice",5)==0)
			{
				array=explode('=',line,&number);
				if(number>1) audio->voice=atoi(array[1]);
				freeExplodedArray(array,number);
			}
			else if(strncasecmp(line,"effects_volume",14)==0)
			{
				array=explode('=',line,&number);
				if(number>1) audio->effectsVolume=(float)atoi(array[1])/100;
				freeExplodedArray(array,number);
			}
			else if(strncasecmp(line,"effects",7)==0)
			{
				array=explode('=',line,&number);
				if(number>1) audio->effects=atoi(array[1]);
				freeExplodedArray(array,number);
			}
			free(line);
		}
	}
	return 1;
}*/
//-------------------------------------------------------------------------------//
/**
 * createSoundSystem
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 20/11/2007
 * @last: 19/05/2008
 * @param FMOD_SYSTEM** : apontador do apontador do systema de audio
 * @param char *  : nome do arquivo de configuração
 * @return: int gorgon_error
 * @abstract: função para iniciar o dispositivo de áudio
 */
//int createSoundSystem(FMOD_SYSTEM **system,short voices)
int gorgonCreateSoundSystem(gorgonAudio *audio,char *filename)
{
	int error;
	FMOD_RESULT result;
	error=gorgonLoadAudioConfigBin(audio,filename);
	if(error!=GORGON_OK)
		return error;
	result=FMOD_System_Create(&audio->system);
	if(result!=FMOD_OK)
	{
		audio->audio=0;
		printf("%s\n",FMOD_ErrorString(result));
		return GORGON_SOUND_SYSTEM_ERROR;
	}
	result=FMOD_System_Init(audio->system, audio->maxChannels, FMOD_INIT_NORMAL, NULL);
	if(result!=FMOD_OK)
	{
		audio->audio=0;
		printf("%s\n",FMOD_ErrorString(result));
		return GORGON_SOUND_SYSTEM_ERROR;
	}
    return GORGON_OK;
}
/**
 * destroySoundSystem
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 20/11/2007
 * @last: 21/11/2007
 * @param FMOD_SYSTEM* :GORGON_SOUND_SYSTEM_ERROR apontador para o sistema sonoro
 * @return: int
 * @abstract: função que destroi o sistema sonoro
 */
int gorgonDestroySoundSystem(gorgonAudio *audio)
{
	if(FMOD_System_Close(audio->system)!=FMOD_OK)		return 0;
    	if(FMOD_System_Release(audio->system)!=FMOD_OK)	return 0;;
	return 1;
}
/**
 * loadSound
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 20/11/2007
 * @last: 19/05/2008
 * @param gorgonSound ** : apontador de apontador para o gorgonSound que receberá o som
 * @param char* : nome do arquivo a ser aberto
 * @param gorgonAudio*: apontador para o audio
 * @return: int gorgon_error
 * @abstract: função que recebe o nome de um arquivo a ser aberto e o systema e retorna o som que foi aberto na memória
 */
int gorgonLoadSound(gorgonSound **sound,char *name,gorgonAudio *audio)
{
	//MOD_SOUND *sound;
	//FMOD_LOOP_NORMAL
	//FMOD_CREATESTREAM
	if(audio->audio)
	{
		if(FMOD_System_CreateSound(audio->system, name, FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, sound)!=FMOD_OK)
			return GORGON_LOAD_SOUND_ERROR;
		return GORGON_OK;
	}
	*sound=NULL;
	return GORGON_SOUND_SYSTEM_ERROR;
}
/**
 * destroySound
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 20/11/2007
 * @param gorgonSound* : ponteiro para o som
 * @return: int
 * @abstract: função que destroi umn determinado som
 */
int gorgonDestroySound(gorgonSound *sound)
{
	if(sound!=NULL)
	{
		if(FMOD_Sound_Release(sound)!=FMOD_OK)	return GORGON_SOUND_SYSTEM_ERROR;
			return GORGON_OK;
	}
	return GORGON_INVALID_SOUND;
}
/**
 * playSound
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 20/11/2007
 * @revised: 28/11/2007
 * @param gorgonSound* : ponteiro para o som que deseja-se tocar
 * @param gorgonAudio* : ponteiro para o sistema de som
 * @param short : tipo de som a tocar: 1-> musica, 2->voz, 3->efeito sonoro
 * @return: int
 * @abstract: função que faz tocar um determinado som, já na memória em um canal de áudio de acordo com o tipo
 */
int gorgonPlaySound(gorgonSound *sound,gorgonAudio *audio,short type)
{
	FMOD_CHANNEL **channel;
	float volume;
	if(sound==NULL || type>3 || type<1 || !audio->audio) return 0;
	switch(type)
	{
		case 1:
			channel=&audio->musicChannel;
			volume=audio->musicVolume;
			break;
		case 2:
			channel=&audio->voiceChannel;
			volume=audio->voiceVolume;
			break;
		case 3:
			channel=&audio->effectsChannel;
			volume=audio->effectsVolume;
			break;
	}
	if(FMOD_System_PlaySound(audio->system, FMOD_CHANNEL_FREE, sound, 0, channel)==FMOD_OK)
	{
		if(FMOD_Channel_SetVolume(*channel,volume)!=FMOD_OK)
			return 0;
	}
	else return 0;
	return 1;
}
/**
 * gorgonToogleSound
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 20/11/2007
 * @param gorgonAudio* : apontador para o sistema de audio
 * @return: int
 * @abstract: função que pausa ou despausa os canais de som
 */
int gorgonToggleSound(gorgonAudio *audio)
{
	int paused;
	if(FMOD_Channel_GetPaused(audio->musicChannel, &paused)!=FMOD_OK) return 0;
	if(FMOD_Channel_SetPaused(audio->musicChannel, !paused)!=FMOD_OK) return 0;
//	if(FMOD_Channel_GetPaused(audio->voiceChannel, &paused)!=FMOD_OK) return 0;
	if(FMOD_Channel_SetPaused(audio->voiceChannel, !paused)!=FMOD_OK) return 0;
//	if(FMOD_Channel_GetPaused(audio->effectsChannel, &paused)!=FMOD_OK) return 0;
	if(FMOD_Channel_SetPaused(audio->effectsChannel, !paused)!=FMOD_OK) return 0;
	printf("ok\n");
	return 1;
}
//----------------------------------------------------------------------------------//
