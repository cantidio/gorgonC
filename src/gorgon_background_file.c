#include "../include/gorgon_background_file.h"
/**
 * função para salvar o valor de um tile em um arquivo já aberto previamente
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 24/06/2008
 * @final: 25/06/2008
 * @param: FILE *, ponteiro para o arquivo onde os dados serão salvos
 * @param: gorgonTile *, ponteiro para o tile a ser salvo
 * @return: int gorgon_error
 */
int gorgonSaveTile_f(FILE *file, gorgonTile *tile)
{
	if(file!=NULL)
	{
		if(tile!=NULL)
		{
			fwrite(&tile->animationIndex,1,sizeof(short),file);
			fwrite(&tile->number,1,sizeof(short),file);
			fwrite(&tile->posX[0],1,sizeof(short)*tile->number,file);
			fwrite(&tile->posY[0],1,sizeof(short)*tile->number,file);
			return GORGON_OK;
		}
		return GORGON_INVALID_TILE;
	}
	return GORGON_INVALID_FILE;
}
/**
 * função para salvar o valor de um layer em um arquivo já aberto previamente
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 24/06/2008
 * @final: 24/06/2008
 * @param: FILE *, ponteiro para o arquivo onde os dados serão salvos
 * @param: gorgonLayer *, ponteiro para o layer a ser salvo
 * @return: int gorgon_error
 */
int gorgonSaveLayer_f(FILE *file, gorgonLayer *layer)
{
	int i;
	int error;
	if(file!=NULL)
	{
		if(layer!=NULL)
		{
			fwrite(&layer->scrollingSpeedX,1,sizeof(float),file);
			fwrite(&layer->scrollingSpeedY,1,sizeof(float),file);
			fwrite(&layer->tileNumber,1,sizeof(short),file);
			for(i=0; i<layer->tileNumber; i++)
			{
				error=gorgonSaveTile_f(file,&layer->tile[i]);
				if(error!=GORGON_OK) return error;
			}
			return GORGON_OK;
		}
		return GORGON_INVALID_LAYER;
	}
	return GORGON_INVALID_FILE;
}
/**
 * função para salvar o valor de um LayerPack em um arquivo já aberto previamente
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 24/06/2008
 * @final: 24/06/2008
 * @param: FILE *, ponteiro para o arquivo onde os dados serão salvos
 * @param: gorgonLayerPack *, ponteiro para o LayerPack a ser salvo
 * @return: int gorgon_error
 */
int gorgonSaveLayerPack_f(FILE *file,gorgonLayerPack *layerPack)
{
	int i;
	int error;
	if(file!=NULL)
	{
		if(layerPack!=NULL)
		{
			fwrite(&layerPack->layerNumber,1,sizeof(short),file);
			for(i=0; i<layerPack->layerNumber; i++)
			{
				error=gorgonSaveLayer_f(file,&layerPack->layer[i]);
				if(error!=GORGON_OK) return error;
			}
			return GORGON_OK;
		}
		return GORGON_INVALID_LAYERPACK;
	}
	return GORGON_INVALID_FILE;
}

/**
 * função para salvar o valor de um Background em um arquivo já aberto previamente
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 24/06/2008
 * @final: 24/06/2008
 * @param: FILE *, ponteiro para o arquivo onde os dados serão salvos
 * @param: gorgonBackground *, ponteiro para o Background a ser salvo
 * @return: int gorgon_error
 */
int gorgonSaveBackground_f(FILE *file, gorgonBackground *background)
{
	int error;
	char header[55];
	strcpy(header,"Background file - from Gorgon's library");
	if(file!=NULL)
	{
		if(background!=NULL)
		{
			fwrite(&header,1,sizeof(char)*55,file);
			error=gorgonSaveAnimationPack_f(file,&background->animationPack);
			if(error!=GORGON_OK) return error;
		
			error=gorgonSaveSpritePack_f(file,&background->spritePack);
			if(error!=GORGON_OK) return error;

			error=gorgonSaveLayerPack_f(file,&background->layerPack);			
			if(error!=GORGON_OK) return error;

			fwrite(&background->width,1,sizeof(short),file);
			fwrite(&background->height,1,sizeof(short),file);
			fwrite(&background->posX,1,sizeof(short),file);
			fwrite(&background->posY,1,sizeof(short),file);
			fwrite(&background->playerLayer,1,sizeof(short),file);
		}
		return GORGON_INVALID_BACKGROUND;
	}
	return GORGON_INVALID_FILE;
}
/**
 * função para salvar o valor de um Background em um arquivo
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 24/06/2008
 * @final: 24/06/2008
 * @param: char *, string com a localização de onde será salvo o arquivo
 * @param: gorgonBackground *, ponteiro para o Background a ser salvo
 * @return: int gorgon_error
 */
int gorgonSaveBackground(char *filename,gorgonBackground *background)
{
	FILE *file;
	int error;
	if(filename!=NULL)
	{
		file=fopen(filename,"wb");
		if(file!=NULL)
		{
			error=gorgonSaveBackground_f(file,background);
			fclose(file);
			return error;
		}
		return GORGON_FILE_CANNOT_WRITE;
	}
	return GORGON_INVALID_VALUE;
}
/**
 * função para carregar o valor de um tile da memória
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 24/06/2008
 * @final: 24/06/2008
 * @param: gorgonTile *, ponteiro para o tile que será carregado
 * @param: char *, ponteiro para a memória onde se encontra os dados do tile
 * @param: int *, posição na memória cedida onde o tile se encontra
 * @return: int gorgon_error
 */
int gorgonLoadTile_fm(gorgonTile *tile, char *data, int *ofs)
{
	short *animationIndex;
	short *number;
	short *posX;
	short *posY;
	int i;
	if(tile!=NULL)
	{
		if(data!=NULL)
		{
			animationIndex	= (short *)&data[*ofs];	(*ofs)+=sizeof(short);
			number		= (short *)&data[*ofs];	(*ofs)+=sizeof(short);
			posX		= (short *)&data[*ofs];	(*ofs)+=sizeof(short)*(*number);
			posY		= (short *)&data[*ofs];	(*ofs)+=sizeof(short)*(*number);

			tile->animationIndex	= *animationIndex;
			tile->number		= *number;
			tile->posX		= (short *) malloc(sizeof(short)*tile->number);
			tile->posY		= (short *) malloc(sizeof(short)*tile->number); 
			for(i=0; i<tile->number; i++)
			{
				tile->posX[i]=posX[i];
				tile->posY[i]=posY[i];
			}
			return GORGON_OK;
		}
		return GORGON_MEMORY_ERROR;
	}
	return GORGON_INVALID_TILE;
}
/**
 * função para carregar o valor de um Layer da memória
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 24/06/2008
 * @final: 24/06/2008
 * @param: gorgonLayer *, ponteiro para o layer que será carregado
 * @param: char *, ponteiro para a memória onde se encontra os dados do Layer
 * @param: int *, posição na memória cedida onde o Layer se encontra
 * @return: int gorgon_error
 */
int gorgonLoadLayer_fm(gorgonLayer *layer,char *data,int *ofs)
{
	float 	*scrollingSpeedX;
	float 	*scrollingSpeedY;
	short 	*tileNumber;
	int 	i;
	int 	error;
	if(layer!=NULL)
	{
		if(data!=NULL)
		{
			scrollingSpeedX	= (float *)&data[*ofs];	(*ofs)+=sizeof(float);
			scrollingSpeedY	= (float *)&data[*ofs];	(*ofs)+=sizeof(float);
			tileNumber	= (short *)&data[*ofs];	(*ofs)+=sizeof(short);

			layer->scrollingSpeedX	= *scrollingSpeedX;
			layer->scrollingSpeedY	= *scrollingSpeedY;
			layer->tileNumber	= *tileNumber;
			layer->tile		= (gorgonTile *) malloc(sizeof(gorgonTile)*layer->tileNumber);
			
			if(layer->tile!=NULL)
			{
				for(i=0; i<*tileNumber; i++)
				{
					error=gorgonLoadTile_fm(&layer->tile[i],data,ofs);
					if(error!=GORGON_OK) return error;
				}
				return GORGON_OK;
			}
			return GORGON_MEMORY_ERROR;
		}
		return GORGON_MEMORY_ERROR;
	}
	return GORGON_INVALID_LAYER;
}
/**
 * função para carregar o valor de um LayerPack da memória
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 24/06/2008
 * @final: 24/06/2008
 * @param: gorgonLayerPack *, ponteiro para o LayerPack que será carregado
 * @param: char *, ponteiro para a memória onde se encontra os dados do LayerPack
 * @param: int *, posição na memória cedida onde o LayerPack se encontra
 * @return: int gorgon_error
 */
int gorgonLoadLayerPack_fm(gorgonLayerPack *layerPack,char *data,int *ofs)
{
	short *layerNumber;
	int i;
	int error;
	if(layerPack!=NULL)
	{
		if(data!=NULL)
		{
			layerNumber		= (short *)&data[*ofs];	(*ofs)+=sizeof(short);
			layerPack->layerNumber	= *layerNumber;
			layerPack->layer	= (gorgonLayer *)malloc(sizeof(gorgonLayer)*layerPack->layerNumber);
			if(layerPack->layer!=NULL)
			{
				for(i=0; i<*layerNumber; i++)
				{
					error=gorgonLoadLayer_fm(&layerPack->layer[i],data,ofs);
					if(error!=GORGON_OK) return error;
				}
				return GORGON_OK;
			}
			return GORGON_INVALID_LAYER;
		}
		return GORGON_MEMORY_ERROR;
	}
	return GORGON_INVALID_LAYERPACK;
}
/**
 * função para carregar o valor de um Background da memória
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 24/06/2008
 * @final: 24/06/2008
 * @param: gorgonBackground *, ponteiro para o Background que será carregado
 * @param: char *, ponteiro para a memória onde se encontra os dados do Background
 * @param: int *, posição na memória cedida onde o Background se encontra
 * @return: int gorgon_error
 */
int gorgonLoadBackground_fm(gorgonBackground *background,char *data, int *ofs)
{
	char	*header;
	short	*width;
	short	*height;
	short	*posX;
	short	*posY;
	short	*playerLayer;
	int 	error;

	if(background!=NULL)
	{
		if(data!=NULL)
		{
			header=(char *)&data[*ofs];	(*ofs)+=sizeof(char)*55;

			error=gorgonLoadAnimationPack_fm(&background->animationPack,data,ofs);
			if(error!=GORGON_OK) return error;

			error=gorgonLoadSpritePack_fm(&background->spritePack,data,ofs);
			if(error!=GORGON_OK) return error;

			error=gorgonLoadLayerPack_fm(&background->layerPack,data,ofs);
			if(error!=GORGON_OK) return error;

			width		=(short *)&data[*ofs];	(*ofs)+=sizeof(short);
			height		=(short *)&data[*ofs];	(*ofs)+=sizeof(short);
			posX		=(short *)&data[*ofs];	(*ofs)+=sizeof(short);
			posY		=(short *)&data[*ofs];	(*ofs)+=sizeof(short);
			playerLayer	=(short *)&data[*ofs];	(*ofs)+=sizeof(short);
	
			background->width	= *width;
			background->height	= *height;
			background->posX	= *posX;
			background->posY	= *posY;
			background->playerLayer	= *playerLayer;
			return GORGON_OK;
		}

		return GORGON_MEMORY_ERROR;
	}
	return GORGON_INVALID_BACKGROUND;
}
/**
 * função para carregar o valor de um Background de um arquivo
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 24/06/2008
 * @final: 24/06/2008
 * @param: gorgonBackground *, ponteiro para o Background que será carregado
 * @param: char *, nome do arquivo que está os dados do Background
 * @return: int gorgon_error
 */
int gorgonLoadBackground(gorgonBackground *background,char *filename)
{
	FILE *file;
	long size= file_size(filename);
	int error;
	int ofs=0;
	char *data;
	if(size>0)
	{
		file=fopen(filename,"rb");
		data= (char *)malloc(size);
		if(data!=NULL)
		{
			fread(&(data[0]),1,size, file);
			fclose(file);
			error=gorgonLoadBackground_fm(background,&data[0],&ofs);
			free(data);
			return error;
		}
		return GORGON_MEMORY_ERROR;
	}
	return GORGON_FILE_NOT_FOUND;
}
