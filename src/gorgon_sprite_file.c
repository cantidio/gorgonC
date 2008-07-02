#include "../include/gorgon_sprite_file.h"

/**
 * função para salvar um sprite em um arquivo
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 13/06/2008
 * @final: 14/06/2008
 * @param: FILE *, ponteiro para o arquivo onde o sprite será salvo
 * @param: gorgonSprite *, ponteiro para o sprite
 * @return: int gorgon_error
 * @example:
 *
 * FILE *file;
 * gorgonSprite sprite;
 *
 * if(gorgonSaveSprite_f(file,&sprite)!=GORGON_OK)
 *	printf("erro\n");
 */
int gorgonSaveSprite_f(FILE *file,gorgonSprite *sprite)
{
	if(file!=NULL)
	{
		if(sprite!=NULL)
		{
			fwrite(&sprite->x,1,sizeof(short),file);
			fwrite(&sprite->y,1,sizeof(short),file);
			fwrite(&sprite->group,1,sizeof(short),file);
			fwrite(&sprite->index,1,sizeof(short),file);
			return gorgonSavePcx_f(file,sprite->image,sprite->pal);
		}
		return GORGON_INVALID_SPRITE;
	}
	return GORGON_INVALID_FILE;
}

/**
 * função para salvar um spritepack em um arquivo
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 13/06/2008
 * @final: 14/06/2008
 * @param: FILE *, ponteiro para o arquivo onde o pacote de imagens será salvo
 * @param: gorgonSpritePack *, ponteiro para um pacote de sprites
 * @return: int gorgon_error
 * @example:
 *
 * FILE *file;
 * gorgonSpritePack spritePack;
 *
 * if(gorgonSaveSpritePack_f(file,&spritePack)!=GORGON_OK)
 *	printf("erro\n");
 */
int gorgonSaveSpritePack_f(FILE *file, gorgonSpritePack *spritePack)
{
	int error;
	int i;
	char fileType	= GORGON_SPRITEPACK_FILE;	
	char version	= 1;
	char byteLock	= GORGON_SPRITEPACK_FILE_LOCK;
	char comment[55];
	char offset[70];
	strcpy(comment,"SpritePack file - from Gorgon's library");
	if(file!=NULL)
	{
		if(spritePack!=NULL)
		{
			fwrite(&fileType,1,sizeof(char),file);
			fwrite(&version,1,sizeof(char),file);
			fwrite(&byteLock,1,sizeof(char),file);
			fwrite(&comment[0],1,sizeof(char)*55,file);
			fwrite(&offset[0],1,sizeof(char)*70,file);//lixo, marcando lugar para possiveis novos campos
			fwrite(&spritePack->spriteNumber,1,sizeof(short),file);
			for(i=0; i<spritePack->spriteNumber; i++)
			{
				error=gorgonSaveSprite_f(file,&spritePack->sprite[i]);
				if(error!=GORGON_OK) return error;
			}
			return GORGON_OK;
		}
		return GORGON_INVALID_SPRITEPACK;
	}
	return GORGON_INVALID_FILE;
}

/**
 * função para salvar um spritepack em um arquivo
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 13/06/2008
 * @final: 14/06/2008
 * @param: char *, string com o nome do arquivo a ser salvo
 * @param: gorgonSpritePack *, ponteiro para um pacote de sprites
 * @return: int gorgon_error
 * @example:
 *
 * gorgonSpritePack spritePack;
 *
 * if(gorgonSaveSpritePack("teste.spk",&spritePack)!=GORGON_OK)
 *	printf("erro\n");
 */
int gorgonSaveSprite(char *filename,gorgonSprite *sprite)
{
	FILE *file;
	int error;
	if(filename!=NULL)
	{
		if(sprite!=NULL)
		{
			file	= fopen(filename,"wb");
			if(file!=NULL)
			{
				error	= gorgonSaveSprite_f(file,sprite);
				fclose(file);
				return error;
			}
			return GORGON_MEMORY_ERROR;
		}
		return GORGON_INVALID_SPRITEPACK;
	}
	return GORGON_INVALID_VALUE;
}

/**
 * função para salvar um spritepack em um arquivo
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 13/06/2008
 * @final: 14/06/2008
 * @param: char *, string com o nome do arquivo a ser salvo
 * @param: gorgonSpritePack *, ponteiro para um pacote de sprites
 * @return: int gorgon_error
 * @example:
 *
 * gorgonSpritePack spritePack;
 *
 * if(gorgonSaveSpritePack("teste.spk",&spritePack)!=GORGON_OK)
 *	printf("erro\n");
 */
int gorgonSaveSpritePack(char *filename,gorgonSpritePack *spritePack)
{
	FILE *file;
	int error;
	if(filename!=NULL)
	{
		if(spritePack!=NULL)
		{
			file	= fopen(filename,"wb");
			if(file!=NULL)
			{
				error	= gorgonSaveSpritePack_f(file,spritePack);
				fclose(file);
				return error;
			}
			return GORGON_MEMORY_ERROR;
		}
		return GORGON_INVALID_SPRITEPACK;
	}
	return GORGON_INVALID_VALUE;
}

/**
 * função para carregar um sprite da memória
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 13/06/2008
 * @final: 14/06/2008
 * @param: gorgonSprite *, ponteiro para um sprite
 * @param: char *, memória onde os dados do sprite encontram-se
 * @param: int *, ponteiro com a posição inicial de leitura das informações cedidas
 * @return: int gorgon_error
 * @example:
 *
 * gorgonSprite sprite;
 * char data;
 * int ofs=0;
 *
 * if(gorgonLoadSprite_fm(&sprite,&data,&ofs)!=GORGON_OK)
 *	printf("erro");
 */
int gorgonLoadSprite_fm(gorgonSprite *sprite, char *data, int *ofs)
{
	int error;
	short *x;
	short *y;
	short *group;
	short *index;

	if(sprite!=NULL)
	{
		if(data!=NULL)
		{
			if(ofs!=NULL)
			{
				x		= (short *)&data[*ofs];	(*ofs)+=(sizeof(short));
				y		= (short *)&data[*ofs];	(*ofs)+=(sizeof(short));
				group		= (short *)&data[*ofs];	(*ofs)+=(sizeof(short));
				index		= (short *)&data[*ofs];	(*ofs)+=(sizeof(short));
				sprite->x	= *x;
				sprite->y	= *y;
				sprite->group	= *group;
				sprite->index	= *index;

				error=gorgonLoadPcxFromMemory(&sprite->image,data,ofs);
				if(error!=GORGON_OK) return error;
				(*ofs)+=sizeof(char);
				return gorgonLoadPalette_fm(&sprite->pal,data,ofs);
			}
			return GORGON_INVALID_MEMORY_OFFSET;
		}
		return GORGON_INVALID_MEMORY;
	}
	return GORGON_INVALID_SPRITE;
}
/**
 * função para carregar um pacote de sprites da memória
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 13/06/2008
 * @final: 14/06/2008
 * @param: gorgonSpritePack *, ponteiro para um pacote de sprites
 * @param: char *, memória com os dados do pacote de sprites
 * @param: int *, ponteiro com a posição inicial de leitura das informações cedidas
 * @return: int gorgon_error
 * @example:
 *
 * gorgonSpritePack spritePack;
 * char data;
 * int ofs=0;
 * 
 * if(gorgonLoadSpritePack_fm(&spritePack,&data,&ofs)!=GORGON_OK)
 *	printf("erro");
 */
int gorgonLoadSpritePack_fm(gorgonSpritePack *spritePack, char *data, int *ofs)
{
	int 	error;
	int 	i;
	char 	*fileType;	
	char 	*version;
	char 	*byteLock;
	char 	*comment;
	char	*offset;
	short	*sprite;
	if(spritePack!=NULL)
	{
		if(data!=NULL)
		{
			if(ofs!=NULL)
			{
				fileType=(char *)&data[*ofs];	(*ofs)+=(sizeof(char));
				version	=(char *)&data[*ofs];	(*ofs)+=(sizeof(char));
				byteLock=(char *)&data[*ofs];	(*ofs)+=(sizeof(char));
				comment	=(char *)&data[*ofs];	(*ofs)+=(sizeof(char)*55);
				offset	=(char *)&data[*ofs];	(*ofs)+=(sizeof(char)*70);
				sprite	=(short*)&data[*ofs];	(*ofs)+=(sizeof(short));
				spritePack->spriteNumber= *sprite;
				spritePack->sprite	= (gorgonSprite *)malloc(sizeof(gorgonSprite)*spritePack->spriteNumber);

				if(spritePack->sprite!=NULL)
				{
					for(i=0; i<spritePack->spriteNumber; i++)
					{

						error=gorgonLoadSprite_fm(&spritePack->sprite[i],data,ofs);
						if(error!=GORGON_OK) return error;
					}			
					return GORGON_OK;
				}
				return GORGON_MEMORY_ERROR;
			}
			return GORGON_INVALID_MEMORY_OFFSET;
		}
		return GORGON_INVALID_MEMORY;
	}
	return GORGON_INVALID_SPRITEPACK;
}
/**
 * função para carregar um sprites do arquivo
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 13/06/2008
 * @final: 14/06/2008
 * @param: gorgonSprite *, ponteiro para um sprites
 * @param: char *, string com o nome do arquivo a ser aberto
 * @return: int gorgon_error
 * @example:
 *
 * gorgonSprite sprite;
 * 
 * if(gorgonLoadSprite(&sprite,"teste.spk")!=GORGON_OK)
 *	printf("erro");
 */
int gorgonLoadSprite(gorgonSprite *sprite,char *filename)
{
	FILE *file;
	long size=file_size(filename);
	int ofs=0;
	int error;
	char *data;

	if(sprite!=NULL)
	{
		if(size>0)
		{
			file=fopen(filename,"rb");
			data=(char *)malloc(size);

			fread(&(data[0]),1,size, file);

			fclose(file);

			error=gorgonLoadSprite_fm(sprite,data,&ofs);
			free(data);
			return error;
		}
		return GORGON_FILE_NOT_FOUND;
	}
	return GORGON_INVALID_SPRITEPACK;
}
/**
 * função para carregar um pacote de sprites do arquivo
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 13/06/2008
 * @final: 14/06/2008
 * @param: gorgonSpritePack *, ponteiro para um pacote de sprites
 * @param: char *, string com o nome do arquivo a ser aberto
 * @return: int gorgon_error
 * @example:
 *
 * gorgonSpritePack spritePack;
 * 
 * if(gorgonLoadSpritePack(&spritePack,"teste.spk")!=GORGON_OK)
 *	printf("erro");
 */
int gorgonLoadSpritePack(gorgonSpritePack *spritePack,char *filename)
{
	FILE *file;
	long size=file_size(filename);
	int ofs=0;
	int error;
	char *data;

	if(spritePack!=NULL)
	{
		if(size>0)
		{

			file=fopen(filename,"rb");
			data=(char *)malloc(size);
			fread(&(data[0]),1,size, file);
			fclose(file);
			error=gorgonLoadSpritePack_fm(spritePack,data,&ofs);
			free(data);
			return error;
		}
		return GORGON_FILE_NOT_FOUND;
	}
	return GORGON_INVALID_SPRITEPACK;
}
