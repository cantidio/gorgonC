#include "../include/gorgon_background.h"
/**
 * função para criar um tile
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 26/05/2008
 * @final: 26/05/2008
 * @param: gorgonTile *, apontador para o tile a ser criado
 * @param: short, indice da animação que o tile irá usar
 * @param: short, número de tiles
 * @return: int gorgon_error
 */
int gorgonCreateTile(gorgonTile *tile,short animationIndex,short objNumber)
{
	if(tile!=NULL)
	{
		if(objNumber>0)
		{
			tile->animationIndex= animationIndex;
			tile->number		= objNumber;
			tile->posX			= (short *)malloc(sizeof(short)*objNumber);
			tile->posY			= (short *)malloc(sizeof(short)*objNumber);
			if(tile->posX !=NULL && tile->posY!=NULL)
				return GORGON_OK;
			return GORGON_MEMORY_ERROR;
		}
		return GORGON_INVALID_INDEX;
	}
	return GORGON_INVALID_TILE;
}

/**
 * função para setar as posições de um determinado tile
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 26/05/2008
 * @final: 26/05/2008
 * @param: gorgonTile *, apontador para o tile
 * @param: short, número do tile a ser passado os arqumentos
 * @param: short, posição no eixo X
 * @param: short, posição no eixo Y
 * @return: int gorgon_error
 */
int gorgonSetTilePositionByLayer(gorgonTile *tile,short number,short posX,short posY)
{
	if(tile!=NULL)
	{
		if(number<tile->number)
		{
			tile->posX[number]=posX;
			tile->posY[number]=posY;
			return GORGON_OK;
		}
		return GORGON_INVALID_INDEX;
	}
	return GORGON_INVALID_TILE;
}
/**
 * função para criar um layer
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 26/05/2008
 * @final: 26/05/2008
 * @param: float, proporção de deslocamento do cenário, 1 ->normal
 * @param: short, número de tiles diferente que constituirão o cenário
 * @return: int gorgon_error
 */
int gorgonCreateLayer(gorgonLayer *layer,float scrollingSpeedX,float scrollingSpeedY,short tileNumber)
{
	short i;
	if(layer!=NULL)
	{
		layer->scrollingSpeedX	= scrollingSpeedX;
		layer->scrollingSpeedY	= scrollingSpeedY;
		layer->tileNumber		= tileNumber;
		layer->tile				= (gorgonTile *)malloc(sizeof(gorgonTile)*tileNumber);
		if(layer->tile!=NULL)
		{
			for(i=0; i<tileNumber; layer->tile[i].number=0,i++);
			return GORGON_OK;
		}
		return GORGON_MEMORY_ERROR;
	}
	return GORGON_INVALID_LAYER;
}
/**
 * função para criar um cenário, alocando a sua devida memória
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 26/05/2008 
 * @final: 06/06/2008
 * @param: gorgonBackGround *, ponteiro para o cenário que deseja ser criado/alocado
 * @param: short, largura do cenário
 * @param: short, altura do cenário
 * @param: short, limite a esquerda
 * @param: short, limite a direita
 * @param: short, limite a cima
 * @param: short, limite a baixo
 * @param: short, posição inicial em x
 * @param: short, posição inicial em y
 * @param: short, o número da camada em que o personagem será exibido
 * @param: short, número de camadas que o cenário terá
 * @return: int gorgon_error
 * @exemple:
 * 
 * gorgonBackground bg;
 * 
 * if(gorgonCreateBackground(&bg,320,240,0,320,0,240,0,0,2,3)!=GORGON_OK)
 *		printf("erro\n");
 */
int gorgonCreateBackground(gorgonBackground *background,short width,short height,short boundLeft,short boundRight, short boundUp, short boundDown,short posX,short posY,short playerLayer, short layerNumber)
{
	if(background!=NULL)
	{
		if(layerNumber>0 && playerLayer>=0)
		{
			background->width							= width;
			background->height							= height;
			background->posX							= posX;
			background->posY							= posY;
			background->boundLeft						= boundLeft;
			background->boundRight						= boundRight;
			background->boundUp							= boundUp;
			background->boundDown						= boundDown;
			background->playerLayer						= playerLayer;
			background->layerNumber						= layerNumber;
			background->animationPack.animationNumber	= 0;
			
			background->layer=(gorgonLayer *)malloc(layerNumber*sizeof(gorgonLayer));
			if(background->layer!=NULL)
				return GORGON_OK;
			return GORGON_MEMORY_ERROR;
		}
		return GORGON_INVALID_INDEX;
	}
	return GORGON_INVALID_BACKGROUND;
}
/**
 * função para desenhar um tile do cenário
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 26/05/2008 
 * @final: 28/05/2008
 * @param: BITMAP *, ponteiro para a superfície onde o tile será desenhado
 * @param: gorgonBackground *, ponteiro para o cenário que deseja desenhar um tile
 * @param: short, número da camada que está o tile
 * @param: short, numero do tile a ser desenhado
 * @return: int gorgon_error
 * @exemple:
 * 
 * BITMAP *buffer;
 * gorgonBackground bg;
 * 
 * if(gorgonDrawTile(buffer,&bg,0,0)!=GORGON_OK)
 *		printf("erro\n");
 */
int gorgonDrawTile(BITMAP *buffer,gorgonBackground *background,short layer,short tile)
{
	int i, error;
	if(background!=NULL)
	{
		for(i=0; i<background->layer[layer].tile[tile].number; i++)
		{
			error=gorgonShowAnimation(&background->animationPack.animation[background->layer[layer].tile[tile].animationIndex],&background->spritePack,buffer,NULL,(short)((background->posX + background->layer[layer].tile[tile].posX[i])*background->layer[layer].scrollingSpeedX),(short)((background->posY + background->layer[layer].tile[tile].posY[i])*background->layer[layer].scrollingSpeedY));
			if(error!=GORGON_OK)	return error;
		}
		return GORGON_OK;
	}
	return GORGON_INVALID_BACKGROUND;
}
/**
 * função para desenhar um tile do cenário
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 28/05/2008 
 * @final: 28/05/2008
 * @param: BITMAP *, ponteiro para a superfície onde o tile será desenhado
 * @param: gorgonTile *, ponteiro para o tile se que deseja desenhar
 * @param: short, posição no eixo x que o tile deve ser desenhado
 * @param: short, posição no eixo y que o tile deve ser desenhado
 * @param: gorgonSpritePack *, ponteiro para o pacote de sprites do tile
 * @param: gorgonAnimationPack *, ponteiro para o pacote de animações do tile
 * @return: int gorgon_error
 * @exemple:
 * 
 * BITMAP *buffer;
 * gorgonTile tile;
 * gorgonAnimationPack animationPack;
 * gorgonSpritePack spritePack;
 *
 * if(gorgonDrawTile(buffer,&tile,0,0,&spritePack,&animationPack)!=GORGON_OK)
 *		printf("erro\n");
 */
int gorgonDrawTile(BITMAP *buffer,gorgonTile *tile,short posX,short posY,gorgonSpritePack *spritePack,gorgonAnimationPack *animationPack)
{
	int i,error;
	if(tile!=NULL)
	{
		for(i=0; i<tile->number; i++)
		{
			error=gorgonShowAnimation(&animationPack->animation[tile->animationIndex],spritePack,buffer,NULL,posX+tile->posX[i],posY+tile->posY[i]);
			if(error!=GORGON_OK)
				return error;
		}
		return GORGON_OK;
	}
	return GORGON_INVALID_TILE;
}

/**
 * função para desenhar uma camada do cenário
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 26/05/2008 
 * @final: 28/05/2008
 * @param: BITMAP *, ponteiro para a superfície onde a camada será desenhada
 * @param: gorgonBackground *, ponteiro para o cenário que deseja desenhar uma camada
 * @param: short, número da camada a ser desenhada
 * @return: int gorgon_error
 * @exemple:
 * 
 * BITMAP *buffer;
 * gorgonBackground bg;
 * 
 * if(gorgonDrawLayer(buffer,&bg,0)!=GORGON_OK)
 *		printf("erro\n");
 */
int gorgonDrawLayer(BITMAP *buffer,gorgonBackground *background,short layerNumber)
{
	int i,error;
	if(background!=NULL)
	{
		if(layerNumber<background->layerNumber)
		{
			for(i=0; i<background->layer[layerNumber].tileNumber; i++)
			{
				error=gorgonDrawTile(buffer,background,layerNumber,i);
				if(error!=GORGON_OK)	return error;
			}
			return GORGON_OK;
		}
		return GORGON_INVALID_INDEX;
	}
	return GORGON_INVALID_BACKGROUND;
}
/**
 * função para desenhar uma camada do cenário
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 26/05/2008 
 * @final: 28/05/2008
 * @param: BITMAP *, ponteiro para a superfície onde a camada será desenhada
 * @param: gorgonLayer *, ponteiro para a camada se que deseja desenhar
 * @param: short, posição no eixo x que a camada deve ser desenhada
 * @param: short, posição no eixo y que a camada deve ser desenhada
 * @param: gorgonSpritePack *, ponteiro para o pacote de sprites da camada
 * @param: gorgonAnimationPack *, ponteiro para o pacote de animações da camada
 * @return: int gorgon_error
 * @exemple:
 * 
 * BITMAP *buffer;
 * gorgonLayer layer;
 * gorgonAnimationPack animationPack;
 * gorgonSpritePack spritePack;
 *
 * if(gorgonDrawLayer(buffer,&layer,0,0,&spritePack,&animationPack)!=GORGON_OK)
 *		printf("erro\n");
 */
int gorgonDrawLayer(BITMAP *buffer,gorgonLayer *layer,short posX,short posY, gorgonSpritePack *spritePack,gorgonAnimationPack *animationPack)
{
	int i,error;
	float x;
	float y;
	if(layer!=NULL)
	{
		for(i=0; i<layer->tileNumber; i++)
		{
			x=
			y=
			error=gorgonDrawTile(buffer,&layer->tile[i],(short)(posX*layer->scrollingSpeedX),(short)(posY*layer->scrollingSpeedY),spritePack,animationPack);
			if(error!=GORGON_OK) return error;
		}
		return GORGON_OK;
	}
	return GORGON_INVALID_LAYER;
}

/**
 * função para desenhar um cenário
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 26/05/2008 
 * @final: 28/05/2008
 * @param: BITMAP *, ponteiro para a superfície onde a camada será desenhada
 * @param: gorgonBackground *, ponteiro para o cenário que se deseja desenhar
 * @param: short, tipo do desenho:
 * 		ALL_LAYERS	-> desenha todas camadas;
 *		BACK_LAYERS	-> desenha as camadas de traz do personagem;
 *		FRONT_LAYERS-> desenha as camadas a frente do personagem;
 *		PLAYER_LAYER-> desenha a camada em que o personagem fica;
 *		Qualquer outro valor positivo, imprime a camada indicada, se existir.
 * @return: int gorgon_error
 * @exemple:
 * 
 * BITMAP *buffer;
 * gorgonBackground bg;
 * 
 * if(gorgonDrawBackground(buffer,&bg,ALL_LAYERS)!=GORGON_OK)
 *		printf("erro\n");
 */
int gorgonDrawBackground(BITMAP *buffer,gorgonBackground *background,short type)
{
	short i;
	int error;
	switch(type)
	{
		case ALL_LAYERS:
			for(i=0; i<background->layerNumber; i++)
			{
				error=gorgonDrawLayer(buffer,background,i);
				if(error!=GORGON_OK)
					return error;
			}
			return GORGON_OK;
		break;

		case BACK_LAYERS:
			for(i=0; i<=background->playerLayer; i++)
			{
				error=gorgonDrawLayer(buffer,background,i);
				if(error!=GORGON_OK)
					return error;
			}
			return GORGON_OK;
		break;

		case FRONT_LAYERS:
			for(i=background->playerLayer+1; i<background->layerNumber; i++)
			{
				error=gorgonDrawLayer(buffer,background,i);
				if(error!=GORGON_OK)
					return error;
			}
			return GORGON_OK;
		break;

		case PLAYER_LAYER:
			return error=gorgonDrawLayer(buffer,background,background->playerLayer);
		break;

		default:
			if(type>=0)
				return error=gorgonDrawLayer(buffer,background,type);
			return GORGON_INVALID_INDEX;
		break;
	}
}

/**
 * função para desalocar um tile da memória
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 26/05/2008 
 * @final: 28/05/2008
 * @param: gorgonTile *, ponteiro para o tile que será desalocado
 * @return: int gorgon_error
 * @exemple:
 * 
 * gorgonTile tile;
 * 
 * if(gorgonDestroyTile(&tile)!=GORGON_OK)
 *		printf("erro\n");
 */
int gorgonDestroyTile(gorgonTile *tile)
{
	if(tile!=NULL)
	{
		if(tile->posX!=NULL)
		{
			free(tile->posX);
			tile->posX=NULL;
		}
		if(tile->posY!=NULL)
		{
			free(tile->posY);
			tile->posY=NULL;
		}
		return GORGON_OK;
	}
	return GORGON_INVALID_TILE;
}
/**
 * função para desalocar uma camada da memória
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 26/05/2008 
 * @final: 28/05/2008
 * @param: gorgonLayer *, ponteiro para a camada que se deseja desalocar
 * @return: int gorgon_error
 * @exemple:
 * 
 * gorgonLayer layer;
 * 
 * if(gorgonDestroyLayer(&layer)!=GORGON_OK)
 *		printf("erro\n");
 */
int gorgonDestroyLayer(gorgonLayer *layer)
{
	int i,error;
	if(layer!=NULL)
	{
		for(i=0; i<layer->tileNumber; i++)
		{
			error=gorgonDestroyTile(&layer->tile[i]);
			if(error!=GORGON_OK) return error;
		}
		free(layer->tile);
		layer->tile=NULL;
		return GORGON_OK;
	}
	return GORGON_INVALID_LAYER;
}
/**
 * função para desalocar um cenário da memória
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 26/05/2008 
 * @final: 28/05/2008
 * @param: gorgonBackGround *, ponteiro para o cenário que deseja se desalocar
 * @return: int gorgon_error
 * @exemple:
 * 
 * gorgonBackground bg;
 * 
 * if(gorgonDestroyBackground(&bg)!=GORGON_OK)
 *		printf("erro\n");
 */
int gorgonDestroyBackground(gorgonBackground *background)
{
	int i, error;
	if(background!=NULL)
	{
		for(i=0; i<background->layerNumber; i++)
		{
			error=gorgonDestroyLayer(&background->layer[i]);
			if(error!=GORGON_OK) return error;
		}
		free(background->layer);
		background->layer=NULL;
		background->width		= 0;
		background->height		= 0;
		background->boundLeft	= 0;
		background->boundRight	= 0;
		background->boundUp		= 0;
		background->boundDown	= 0;
		background->posX		= 0;
		background->posY		= 0;
		background->playerLayer	= 0;
		error=gorgonDestroySpritePack(&background->spritePack);
		if(error!=GORGON_OK) return error;
		error=gorgonDestroyAnimationPack(&background->animationPack);
		if(error!=GORGON_OK) return error;
		return GORGON_OK;
	}
	return GORGON_INVALID_BACKGROUND;
}



