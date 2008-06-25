#include "../include/gorgon_animation.h"
/**
 * funçao para criar uma colisao
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 01/05/2008
 * @final: 01/05/2008
 * @param: gorgonClsn *, ponteiro para uma gorgonClsn que deseja ser criada
 * @param: short, numero de retangulos de colisoes a serem criados
 * @return: int gorgon_error
 * @exemple:
 *
 * short number=1;
 * gorgonClsn Clsn;
 *
 *  if(gorgonCreateClsn(&Clsn,number)!=GORGON_OK)
 *	  printf("erro\n");
 */
int gorgonCreateClsn(gorgonClsn *clsn,short number)
{
	if(clsn!=NULL)
	{
		if(number>0)
		{
			clsn->boxNumber=number;
			clsn->x1=(short *)calloc(number,sizeof(short));
			clsn->x2=(short *)calloc(number,sizeof(short));
			clsn->y1=(short *)calloc(number,sizeof(short));
			clsn->y2=(short *)calloc(number,sizeof(short));
			if(clsn->x1==NULL || clsn->x2==NULL || clsn->y1==NULL || clsn->y2==NULL)
				return GORGON_MEMORY_ERROR;
			return GORGON_OK;
		}
		return GORGON_INVALID_INDEX;
	}
	return GORGON_INVALID_CLSN;
}
/**
 * funçao para setar os valores de uma Colisão
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 01/05/2008
 * @final: 01/05/2008
 * @param: gorgonClsn *, ponteiro para um gorgonClsn que deseja setar os valores
 * @param: short, identificador do retangulo de colisão
 * @param: short, posicao x1 do retangulo de colisao
 * @param: short, posicao x2 do retangulo de colisao
 * @param: short, posicao y1 do retangulo de colisao
 * @param: short, posicao y2 do retangulo de colisao
 * @return: int gorgon_error
 * @exemple:
 *
 * short index=1, x1=0, x2=10, y1=3, y2=-5;
 * gorgonClsn Clsn;
 *
 *  if(gorgonSetClsnValues(&Clsn,index,x1,x2,y1,y2)!=GORGON_OK)
 *	  printf("erro\n");
 */
int gorgonSetClsnValues(gorgonClsn *clsn,short index,short x1,short x2,short y1, short y2)
{
	if(clsn!=NULL)
	{
		if(index<clsn->boxNumber)
		{
			clsn->x1[index]=x1;
			clsn->x2[index]=x2;
			clsn->y1[index]=y1;
			clsn->y2[index]=y2;
			return GORGON_OK;
		}
		return GORGON_INVALID_INDEX;
	}
	return GORGON_INVALID_CLSN;
}
/**
 * funçao para criar um frame de uma animação
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 01/05/2008
 * @final: 01/05/2008
 * @param: gorgonFrame *, ponteiro para um gorgonFrame que deseja ser criado
 * @param: short, grupo do sprite
 * @param: short, indice so sprite
 * @param: short, deslocamento no eixo x
 * @param: short, deslocamento no eixo y
 * @param: short, tempo que o frame será exibido
 * @param: short, efeito usado no frame
 * @return: int gorgon_error
 * @exemple:
 *
 * short group=1,sprite=0,x=0,y=0,time=10,effect=0;
 * gorgonFrame frame;
 *
 *  if(gorgonCreateFrame(&frame,group,sprite,x,y,time,effect)!=GORGON_OK)
 *	  printf("erro\n");
 */
int gorgonCreateFrame(gorgonFrame *frame, short group,short spr,short x, short y,short time, short effect)
{
	if(frame!=NULL)
	{
		frame->group			= group;
		frame->spr			= spr;
		frame->index			= -1;
		frame->x			= x;
		frame->y			= y;
		frame->time			= time;
		frame->effect			= effect;
		frame->clsnBlue.boxNumber	= 0;
		frame->clsnRed.boxNumber	= 0;
		frame->clsnUp.boxNumber		= 0;
		frame->clsnLeft.boxNumber	= 0;
		frame->clsnDown.boxNumber	= 0;
		frame->clsnRight.boxNumber	= 0;
		return GORGON_OK;
	}
	return GORGON_INVALID_FRAME;
}
/**
 * funçao para criar uma animacao
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 01/05/2008
 * @final: 15/06/2008
 * @param: gorgonAnimation *, ponteiro para um gorgonAnimation que deseja ser criado
 * @param: short, identificador da animacao
 * @param: short, numero de frames da animacao
 * @return: int gorgon_error
 * @exemple:
 *
 * short action=1001,frames=10;
 * gorgonAnimation animation;
 *
 *  if(gorgonCreateAnimation(&animation,action,frames)!=GORGON_OK)
 *	  printf("erro\n");
 */
int gorgonCreateAnimation(gorgonAnimation *animation,short action,short frames,short looping)
{
	if(animation!=NULL)
	{
		if(frames>0)
		{
			animation->frame=(gorgonFrame *)calloc(frames,sizeof(gorgonFrame));
			if(animation->frame!=NULL)
			{
				animation->action	= action;
				animation->frames	= frames;
				animation->frameOn	= 0;
				animation->timeOn	= 0;
				animation->looping	= looping;
				return GORGON_OK;
			}
			return GORGON_MEMORY_ERROR;
		}
		return GORGON_INVALID_INDEX;
	}
	return GORGON_INVALID_ANIMATION;
}

/**
 * função para criar um pacote de animações
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 08/05/2008
 * @final: 06/06/2008
 * @param: gorgonAnimationPack *, ponteiro para um pacote de animações a ser criado
 * @param: short, número de animações que esse pacote terá
 * @return: int gorgon_error
 * @exemple:
 *
 * gorgonAnimationPack pack;
 * short x=10;
 * if(gorgonCreateAnimationPack(&pack,x)!=GORGON_OK)
 *	  printf("erro\n");
 */
int gorgonCreateAnimationPack(gorgonAnimationPack *pack,short animation)
{
	int i;
	if(pack!=NULL)
	{
		if(animation>0)
		{
			pack->animationNumber=animation;
			pack->animation=(gorgonAnimation *)malloc(sizeof(gorgonAnimation)*animation);
			for(i=0; i<animation; pack->animation[i].frames=0, i++);
			if(pack->animation!=NULL)
				return GORGON_OK;
			return GORGON_MEMORY_ERROR;
		}
		return GORGON_INVALID_INDEX;
	}
	return GORGON_INVALID_ANIMATIONPACK;
}
/**
 * função para otimizar a localização dos sprites pelas animações
 *
 * @autor: Cantidio Oliveira Fontes
 * @since: 02/05/2008
 * @final: 02/05/2008
 * @param: gorgonAnimation *, ponteiro para um gorgonAnimation que deseja-se otimizar
 * @param: gorgonSpritePack *, ponteiro para um gorgonSpritePack
 * @return: int gorgon_error
 * @exemple:
 *
 * gorgonAnimation anim;
 * gorgonSpritePack sprites;
 *
 * if(gorgonMakeAnimationIndexes(&anim,&sprites)!=GORGON_OK)
 *	  printf("erro");
 */
int gorgonMakeAnimationIndexes(gorgonAnimation *anim, gorgonSpritePack *sprites)
{
	short i,j;
	if(anim!=NULL)
	{
		if(sprites!=NULL)
		{
			for(i=0; i<anim->frames; i++)
				for(j=0; j<sprites->spriteNumber; j++)
				{
					if(anim->frame[i].group==sprites->sprite[j].group && anim->frame[i].spr==sprites->sprite[j].index)
					{
						anim->frame[i].index=j;
						break;
					}
				}
			return GORGON_OK;
		}
		return GORGON_INVALID_SPRITEPACK;
	}
	return GORGON_INVALID_ANIMATION;
}
/**
 * função para otimizar a localização dos sprites pelas animações
 *
 * @autor: Cantidio Oliveira Fontes
 * @since: 09/05/2008
 * @final: 06/06/2008
 * @param: gorgonAnimationPack *, ponteiro para um gorgonAnimationPack que deseja-se otimizar
 * @param: gorgonSpritePack *, ponteiro para um gorgonSpritePack
 * @return: int gorgon_error
 * @exemple:
 *
 * gorgonAnimationPack animationPack;
 * gorgonSpritePack spritePack;
 *
 * if(gorgonMakeAnimationPackIndexes(&animationPack,&spritePack)!=GORGON_OK)
 *	  printf("erro");
 */
int gorgonMakeAnimationPackIndexes(gorgonAnimationPack *animationPack,gorgonSpritePack *spritePack)
{
	int i;
	int error;
	if(animationPack!=NULL)
	{
		for(i=0; i<animationPack->animationNumber; i++)
		{
			error=gorgonMakeAnimationIndexes(&animationPack->animation[i],spritePack);
			if(error!=GORGON_OK) return error;
		}
		return GORGON_OK;
	}
	return GORGON_INVALID_ANIMATIONPACK;
}
/**
 * funçao para desenhar uma colisao
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 02/05/2008
 * @final: 02/05/2008
 * @param: BITMAP *, ponteiro para uma superficie
 * @param: gorgonClsn *, ponteiro para um gorgonClsn que deseja ser desenhado
 * @param: short, tipo de colisao a ser desenhada, CLSN_RED, CLSN_BLUE, CLSN_GREEN
 * @param: short, posicao x de onde será desenhada a colisão
 * @param: short, posicao y de de onde será desenhada a colisão
 * @return: int gorgon_error
 * @exemple:
 *
 * short posX=20,posY=10;
 * gorgonClsn Clsn;
 * BITMAP *layer;
 *
 *  if(gorgonDrawClsn(layer,&Clsn,CLSN_BLUE,posX,posY)!=GORGON_OK)
 *	  printf("erro\n");
 */
int gorgonDrawClsn(BITMAP *layer, gorgonClsn *clsn,short type,short posX,short posY)
{
	short i;
	int col;
	if(clsn!=NULL)
	{
		switch(type)
		{
			case CLSN_GREEN:	col=makecol(0,255,0);		break;
			case CLSN_BLUE:	col=makecol(0,0,255);		break;
			case CLSN_RED:		col=makecol(255,0,0);		break;
			default:		col=makecol(200,200,200);	break;
		}
		for(i=0; i<clsn->boxNumber; rect(layer,posX + clsn->x1[i],posY+ clsn->y1[i],posX+clsn->x2[i],posY+clsn->y2[i],col),i++);
		return GORGON_OK;
	}
	return GORGON_INVALID_CLSN;
}

/**
 * função para imprimir uma animacao
 *
 * @autor: Cantidio Oliveira Fontes
 * @since: 01/05/2008
 * @final: 22/06/2008
 * @param: gorgonAnimation *, ponteiro para um gorgonAnimation que deseja-se otimizar
 * @param: gorgonSpritePack *, ponteiro para um gorgonSpritePack
 * @param: BITMAP *, ponteiro para a superfície onde será desenhada a animacao
 * @param: RGB *, ponteiro para a palheta de cores
 * @param: char, tipo de orientação da animação: NORMAL, H_FLIP, V_FLIP, HV_FLIP
 * @param: short, posiçao que será desenhada no eixoX
 * @param: short, posição que será desenhada no eixoY
 * @return: int gorgon_error
 * @exemple:
 *
 * gorgonAnimation anim;
 * gorgonSpritePack sprites;
 * RGB *pal;
 * BITMAP *layer;
 * short posX=10,posY=10;
 *
 * if(gorgonShowAnimation(&anim,&sprites,layer,pal,posX,posY)!=GORGON_OK)
 *	  printf("erro");
 */
int gorgonShowAnimation(BITMAP *layer,gorgonAnimation *anim,gorgonSpritePack *sprites,RGB *pal,char type,short posX,short posY)
{
	short error;
	if(anim->frame[anim->frameOn].index>(-1))
	{
		switch(type)
		{
			case NORMAL:
				error=gorgonDrawSpriteByIndex(layer,sprites,pal,anim->frame[anim->frameOn].index,anim->frame[anim->frameOn].effect,posX,posY);
				break;
			case H_FLIP:
				switch(anim->frame[anim->frameOn].effect)
				{
					case NORMAL:
						error=gorgonDrawSpriteByIndex(layer,sprites,pal,anim->frame[anim->frameOn].index,H_FLIP,posX,posY);
						break;
					case H_FLIP:
						error=gorgonDrawSpriteByIndex(layer,sprites,pal,anim->frame[anim->frameOn].index,NORMAL,posX,posY);
						break;
					case V_FLIP:
						error=gorgonDrawSpriteByIndex(layer,sprites,pal,anim->frame[anim->frameOn].index,HV_FLIP,posX,posY);
						break;
					case HV_FLIP:
						error=gorgonDrawSpriteByIndex(layer,sprites,pal,anim->frame[anim->frameOn].index,V_FLIP,posX,posY);
						break;
				}
				break;
			case V_FLIP:
				switch(anim->frame[anim->frameOn].effect)
				{
					case NORMAL:
						error=gorgonDrawSpriteByIndex(layer,sprites,pal,anim->frame[anim->frameOn].index,V_FLIP,posX,posY);
						break;
					case H_FLIP:
						error=gorgonDrawSpriteByIndex(layer,sprites,pal,anim->frame[anim->frameOn].index,HV_FLIP,posX,posY);
						break;
					case V_FLIP:
						error=gorgonDrawSpriteByIndex(layer,sprites,pal,anim->frame[anim->frameOn].index,NORMAL,posX,posY);
						break;
					case HV_FLIP:
						error=gorgonDrawSpriteByIndex(layer,sprites,pal,anim->frame[anim->frameOn].index,H_FLIP,posX,posY);
						break;
				}
				break;
			case HV_FLIP:
				switch(anim->frame[anim->frameOn].effect)
				{
					case NORMAL:
						error=gorgonDrawSpriteByIndex(layer,sprites,pal,anim->frame[anim->frameOn].index,HV_FLIP,posX,posY);
						break;
					case H_FLIP:
						error=gorgonDrawSpriteByIndex(layer,sprites,pal,anim->frame[anim->frameOn].index,V_FLIP,posX,posY);
						break;
					case V_FLIP:
						error=gorgonDrawSpriteByIndex(layer,sprites,pal,anim->frame[anim->frameOn].index,H_FLIP,posX,posY);
						break;
					case HV_FLIP:
						error=gorgonDrawSpriteByIndex(layer,sprites,pal,anim->frame[anim->frameOn].index,NORMAL,posX,posY);
						break;
				}
				break;

		}
		if(error!=GORGON_OK) return error;
	}
	else
	{
		switch(type)
		{
			case NORMAL:
				error=gorgonDrawSpriteByGroup(layer,sprites,pal,anim->frame[anim->frameOn].group,anim->frame[anim->frameOn].spr,anim->frame[anim->frameOn].effect,posX,posY);
				break;
			case H_FLIP:
				switch(anim->frame[anim->frameOn].effect)
				{
					case NORMAL:
						error=gorgonDrawSpriteByGroup(layer,sprites,pal,anim->frame[anim->frameOn].group,anim->frame[anim->frameOn].spr,H_FLIP,posX,posY);
						break;
					case H_FLIP:
						error=gorgonDrawSpriteByGroup(layer,sprites,pal,anim->frame[anim->frameOn].group,anim->frame[anim->frameOn].spr,NORMAL,posX,posY);
						break;
					case V_FLIP:
						error=gorgonDrawSpriteByGroup(layer,sprites,pal,anim->frame[anim->frameOn].group,anim->frame[anim->frameOn].spr,HV_FLIP,posX,posY);
						break;
					case HV_FLIP:
						error=gorgonDrawSpriteByGroup(layer,sprites,pal,anim->frame[anim->frameOn].group,anim->frame[anim->frameOn].spr,V_FLIP,posX,posY);
						break;
				}
				break;
			case V_FLIP:
				switch(anim->frame[anim->frameOn].effect)
				{
					case NORMAL:
						error=gorgonDrawSpriteByGroup(layer,sprites,pal,anim->frame[anim->frameOn].group,anim->frame[anim->frameOn].spr,V_FLIP,posX,posY);
						break;
					case H_FLIP:
						error=gorgonDrawSpriteByGroup(layer,sprites,pal,anim->frame[anim->frameOn].group,anim->frame[anim->frameOn].spr,HV_FLIP,posX,posY);
						break;
					case V_FLIP:
						error=gorgonDrawSpriteByGroup(layer,sprites,pal,anim->frame[anim->frameOn].group,anim->frame[anim->frameOn].spr,NORMAL,posX,posY);
						break;
					case HV_FLIP:
						error=gorgonDrawSpriteByGroup(layer,sprites,pal,anim->frame[anim->frameOn].group,anim->frame[anim->frameOn].spr,H_FLIP,posX,posY);
						break;
				}
				break;
			case HV_FLIP:
				switch(anim->frame[anim->frameOn].effect)
				{
					case NORMAL:
						error=gorgonDrawSpriteByGroup(layer,sprites,pal,anim->frame[anim->frameOn].group,anim->frame[anim->frameOn].spr,HV_FLIP,posX,posY);
						break;
					case H_FLIP:
						error=gorgonDrawSpriteByGroup(layer,sprites,pal,anim->frame[anim->frameOn].group,anim->frame[anim->frameOn].spr,V_FLIP,posX,posY);
						break;
					case V_FLIP:
						error=gorgonDrawSpriteByGroup(layer,sprites,pal,anim->frame[anim->frameOn].group,anim->frame[anim->frameOn].spr,H_FLIP,posX,posY);
						break;
					case HV_FLIP:
						error=gorgonDrawSpriteByGroup(layer,sprites,pal,anim->frame[anim->frameOn].group,anim->frame[anim->frameOn].spr,NORMAL,posX,posY);
						break;
				}
				break;
		}
		if(error!=GORGON_OK) return error;
	}
  /*  gorgonDrawClsn(layer,&anim->frame[anim->frameOn].clsnBlue,  CLSN_BLUE,  posX,posY);
	gorgonDrawClsn(layer,&anim->frame[anim->frameOn].clsnRed,   CLSN_RED,   posX,posY);
	gorgonDrawClsn(layer,&anim->frame[anim->frameOn].clsnUp,	CLSN_GREEN, posX,posY);
	gorgonDrawClsn(layer,&anim->frame[anim->frameOn].clsnLeft,  CLSN_GREEN, posX,posY);
	gorgonDrawClsn(layer,&anim->frame[anim->frameOn].clsnDown,  CLSN_GREEN, posX,posY);
	gorgonDrawClsn(layer,&anim->frame[anim->frameOn].clsnRight, CLSN_GREEN, posX,posY);*/
	anim->timeOn++;
	if(anim->timeOn>=anim->frame[anim->frameOn].time && anim->frame[anim->frameOn].time>-1)
	{
		anim->frameOn++;
		anim->timeOn=0;
	}
	if(anim->frameOn>=anim->frames)
		anim->frameOn=anim->looping;
	return GORGON_OK;
}

/**
 * função para destruir uma colisão
 *
 * @author:	Cantídio Oliveira Fontes
 * @since:	15/05/2008
 * @final: 	06/06/2008
 * @param: 	gorgonClsn *, ponteiro para uma colisão
 * @return:	int gorgon_error
 * @example:
 */
int gorgonDestroyClsn(gorgonClsn *clsn)
{
	if(clsn!=NULL)
	{
		if(clsn->boxNumber>0)
		{
			free(clsn->x1);
			free(clsn->x2);
			free(clsn->y1);
			free(clsn->y2);
			clsn->boxNumber=0;
		}
		return GORGON_OK;
	}
	return GORGON_INVALID_CLSN;
}
/**
 * função para destruir um frame
 *
 * @author:	Cantídio Oliveira Fontes
 * @since:	15/05/2008
 * @final: 	06/06/2008
 * @param: 	gorgonAnimationPack *, ponteiro para um frame
 * @return:	int gorgon_error
 * @example:
 */
int gorgonDestroyFrame(gorgonFrame *frame)
{
	if(frame!=NULL)
	{
		gorgonDestroyClsn(&frame->clsnRed);
		gorgonDestroyClsn(&frame->clsnBlue);
		gorgonDestroyClsn(&frame->clsnUp);
		gorgonDestroyClsn(&frame->clsnLeft);
		gorgonDestroyClsn(&frame->clsnDown);
		gorgonDestroyClsn(&frame->clsnRight);
		frame->group	= 0;
		frame->spr	= 0;
		frame->index	= 0;
		frame->x	= 0;
		frame->y	= 0;
		frame->time	= 0;
		frame->effect	= 0;
		frame->angle	= 0;		
		frame->trans	= 0;	
		return GORGON_OK;
	}
	return GORGON_INVALID_FRAME;
}
/**
 * função para destruir uma animação
 *
 * @author:	Cantídio Oliveira Fontes
 * @since:	15/05/2008
 * @final: 	06/06/2008
 * @param: 	gorgonAnimationPack *, ponteiro para uma animação
 * @return:	int gorgon_error
 * @example:
 *
 * gorgonAnimation animation;
 *
 * if(gorgonDestroyAnimation(&animation)!=GORGON_OK)
 *	printf("erro");
 */
int gorgonDestroyAnimation(gorgonAnimation *animation)
{
	int i,error;
	if(animation!=NULL)
	{
		for(i=0; i<animation->frames; i++)
		{
			error=gorgonDestroyFrame(&animation->frame[i]);
			if(error!=GORGON_OK) return error;
		}
		free(animation->frame);
		animation->frame=NULL;
		return GORGON_OK;
	}
	return GORGON_INVALID_ANIMATION;
}
/**
 * função para destruir um pacote de animações
 *
 * @author:	Cantídio Oliveira Fontes
 * @since:	15/05/2008
 * @final: 	06/06/2008
 * @param: 	gorgonAnimationPack *, ponteiro para um pacote de animações a ser apagado
 * @return:	int gorgon_error
 * @example:
 *
 * gorgonAnimationPack animationPack;
 * if(gorgonDestroyAnimationPack(&animationPack)!=GORGON_OK)
 *	printf("erro");
 */
int gorgonDestroyAnimationPack(gorgonAnimationPack *animationPack)
{
	int i,error;
	if(animationPack!=NULL)
	{
		for(i=0; i<animationPack->animationNumber; i++)
		{
			error=gorgonDestroyAnimation(&animationPack->animation[i]);
			if(error!=GORGON_OK) return error;
		}
		free(animationPack->animation);
		animationPack->animationNumber=0;
		return GORGON_OK;
	}
	return GORGON_INVALID_ANIMATIONPACK;
}

/**
 * função para imprimir os dados de um animationpack 
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 06/06/2008
 * @final: 06/06/2008
 * @param: gorgonAnimationPack *, ponteiro para um pacote de animações
 */
void gorgonPrintAnimationPackValues(gorgonAnimationPack *pk)
{
	int i,j;
	printf("numero de animações no pacote: %d\n",pk->animationNumber);
	for(i=0; i<pk->animationNumber; i++)
	{
		printf("animacao: %d\n",i+1);
		printf("action:%d\n",pk->animation[i].action);
		printf("Numero de frames:%d\n",pk->animation[i].frames);
		printf("looping: %d\n",pk->animation[i].looping);
		printf("time: %d\n",pk->animation[i].timeOn);
		
		for(j=0; j<pk->animation[i].frames; j++)
		{
			printf("frame %d:\n",j+1);
			printf("grupo: %d\n",pk->animation[i].frame[j].group);
			printf("spr: %d\n",pk->animation[i].frame[j].spr);
			printf("index: %d\n",pk->animation[i].frame[j].index);
			printf("x: %d\n",pk->animation[i].frame[j].x);
			printf("y: %d\n",pk->animation[i].frame[j].y);
			printf("time: %d\n",pk->animation[i].frame[j].time);
			printf("effect: %d\n",pk->animation[i].frame[j].effect);
			printf("angle: %d\n",pk->animation[i].frame[j].angle);
			printf("trans: %d\n\n",pk->animation[i].frame[j].trans);
		}
	}
}
