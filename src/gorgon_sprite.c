#include "../include/gorgon_sprite.h"

/**
 * fun�ao para convertar um arquivo sff para um arquivo gorgonSpritePack
 *
 * @author: Cant�dio Oliveira Fontes
 * @since: 30/04/2008
 * @final: 15/06/2008
 * @param: gorgonSpritePack *, ponteiro para uma gorgonSpritePack
 * @param: SFFEntry, ponteiro para um arquivo sff
 * @example:
 *
 * gorgonSff sff;
 * gorgonSpritePack spritePack;
 *
 *  if(gorgonConvertSffToSpritePack(&spritePack,&sff)!=GORGON_OK)
 *	  printf("erro\n");
 */
int gorgonConvertSffToSpritePack(gorgonSpritePack *spritePack, gorgonSff *sff)
{
	int i;
	int error;
	if(spritePack!=NULL)
	{
		if(sff!=NULL)
		{
			spritePack->spriteNumber=sff->spriteNum;
			spritePack->sprite=(gorgonSprite *)malloc(sizeof(gorgonSprite)*spritePack->spriteNumber);
			if(spritePack->sprite!=NULL)
			{
				for(i=0; i<spritePack->spriteNumber; i++)
				{
					spritePack->sprite[i].image	=create_bitmap_ex(8,sff->sprite[i].image->w,sff->sprite[i].image->h);
					blit(sff->sprite[i].image,spritePack->sprite[i].image,0,0,0,0,sff->sprite[i].image->w,sff->sprite[i].image->h);
					spritePack->sprite[i].x		=sff->sprite[i].x;
					spritePack->sprite[i].y		=sff->sprite[i].y;
					spritePack->sprite[i].group	=sff->sprite[i].group;
					spritePack->sprite[i].index	=sff->sprite[i].index;
//					gorgonSavePalette("1.act",sff->sprite[i].pal);
					error=gorgonCopyPalette(&spritePack->sprite[i].pal,sff->sprite[i].pal);
//					gorgonSavePalette("2.act",spritePack->sprite[i].pal);
//exit(1);
					if(error!=GORGON_OK)	return error;
				}
				return GORGON_OK;
			}
			return GORGON_MEMORY_ERROR;
		}
		return GORGON_INVALID_SFF;
   	}
	return GORGON_INVALID_SPRITEPACK;
}
/**
 * fun�ao para carregar um srquivo sff em um spritePack
 *
 * @author: Cant�dio Oliveira Fontes
 * @since: 12/05/2008
 * @final: 12/05/2008
 * @param: gorgonSpritePack *, ponteiro para uma gorgonSpritePack
 * @param: char *, nome do arquivo a ser aberto
 * @return: int gorgon_error
 * @example:
 *
 * gorgonSpritePack spritePack;
 *
 *  if(gorgonLoadSpritePackFromSff(&spritePack,"teste.sff")!=GORGON_OK)
 *	  printf("erro\n");
 */
int gorgonLoadSpritePackFromSff(gorgonSpritePack *spritePack,char *filename)
{
	gorgonSff sff;
	int error;
	error=gorgonLoadSff(&sff,filename);
	if(error!=GORGON_OK) return error;
	error=gorgonConvertSffToSpritePack(spritePack,&sff);
	if(error!=GORGON_OK) return error;
	error=gorgonUnloadSff(&sff);
	if(error!=GORGON_OK) return error;
	return GORGON_OK;
}
/**
 * fun��o para descarregar um sprite da mem�ria
 *
 * @author: Cant�dio Oliveira Fontes
 * @since: 27/05/2008
 * @final: 27/05/2008
 * @param: gorgonSprite *, apontador para um gorgonSprite, cujos dados ser�o desalocados
 * @return: int gorgon_error
 * @example:
 *
 * gorgonSprite sprite;
 *
 * if(gorgonUnloadSprite(&sprite)!=GORGON_OK)
 *		printf("erro\n");
 */
int gorgonDestroySprite(gorgonSprite *sprite)
{
	if(sprite!=NULL)
	{
		if(sprite->image!=NULL) destroy_bitmap(sprite->image);
		return gorgonDestroyPalette(&sprite->pal);
	}
	return GORGON_INVALID_SPRITE;
}
/**
 * fun��o para descarregar um spritePack da mem�ria
 *
 * @author: Cant�dio Oliveira Fontes
 * @since: 27/05/2008
 * @final: 27/05/2008
 * @param: gorgonSpritePack *, apontador para um gorgonSpritePack, cujos dados ser�o desalocados
 * @return: int gorgon_error
 * @example:
 *
 * gorgonSpritePack spritePack;
 *
 * if(gorgonUnloadSpritePack(&spritePack)!=GORGON_OK)
 *	Sprintf("erro\n");
 */
int gorgonDestroySpritePack(gorgonSpritePack *spritePack)
{
	int i,error;
	if(spritePack!=NULL)
	{
		for(i=0; i<spritePack->spriteNumber; i++)
		{
			error=gorgonDestroySprite(&spritePack->sprite[i]);
			if(error!=GORGON_OK) return error;
		}
		free(spritePack->sprite);
		spritePack->sprite=NULL;
		return GORGON_OK;
	}
	return GORGON_INVALID_SPRITEPACK;
}
/**
 * fun�ao para desenhar um sprite de um spritePack atrav�s de um index
 *
 * @author: Cant�dio Oliveira Fontes
 * @since: 01/05/2008
 * @final: 28/05/2008
 * @param: gorgonSpritePack *, ponteiro para um gorgonSpritePack
 * @param: BITMAP *, apontador para um superf�cie onde o sprite ser� desenhado
 * @param: RGB *, apontador para um palheta de cores
 * @param: short, o indice do frame
 * @param: char, op��o de desenho, NORMAL, H_FLIP, V_FLIP, HV_FLIP
 * @param: short, posi��o x que ser� desenhado na superf�cie
 * @param: short, posi��o y que ser� desenhado na superf�cie
 * @return: int gorgon_error
 * @example:
 *
 * short index=0,posX=10,posY=23;
 * BITMAP *buffer;
 * RGB *pal;
 * gorgonSpritePack a;
 *
 *  if(gorgonDrawSpriteByIndex(&a,buffer,pal,index,NORMAL,posX,posY)!=GORGON_OK)
 *	  printf("erro\n");
 */
int gorgonDrawSpriteByIndex(BITMAP *layer,gorgonSpritePack *a,RGB *pal,short index,char type,short posX,short posY)
{
	RGB trans = { 63 , 0 , 63 };
	BITMAP *sprite;
	if(index<a->spriteNumber)
	{
		if(&a->sprite[index]!=NULL)
		{
			if(a->sprite[index].image!=NULL && layer!=NULL)
			{
				sprite=create_bitmap(a->sprite[index].image->w,a->sprite[index].image->h);
				if(pal!=NULL)
					set_palette(pal);
				else if(a->sprite[index].pal!=NULL)
					set_palette(a->sprite[index].pal);
				//set_color(0,&trans);
				//set_color_conversion(COLORCONV_NONE);
				blit(a->sprite[index].image,sprite,0,0,0,0,sprite->w,sprite->h);
				switch(type)
				{
					case NORMAL:
						posX-=a->sprite[index].x;
						posY-=a->sprite[index].y;
						draw_sprite(layer,sprite,posX,posY);
						break;
					case H_FLIP:
						posX-=a->sprite[index].image->w - a->sprite[index].x;
						posY-=a->sprite[index].y;
						draw_sprite_h_flip(layer,sprite,posX,posY);
						break;
					case V_FLIP:
						posX-=a->sprite[index].x;
						posY-=a->sprite[index].image->h - a->sprite[index].y;
						draw_sprite_v_flip(layer,sprite,posX,posY);
						break;
					case HV_FLIP:
						posX-=a->sprite[index].image->w - a->sprite[index].x;
						posY-=a->sprite[index].image->h - a->sprite[index].y;
						draw_sprite_vh_flip(layer,sprite,posX,posY);
						break;
				}
				destroy_bitmap(sprite);
				return GORGON_OK;
			}
			return GORGON_INVALID_IMAGE;
		}
		return GORGON_INVALID_SPRITE;
	}
	return GORGON_INVALID_INDEX;
}
/**
 * fun�ao para desenhar um sprite de um spritePack atrav�s de um index, em um determinado �ngulo
 *
 * @author: Cant�dio Oliveira Fontes
 * @since: 01/05/2008
 * @final: 27/05/2008
 * @param: gorgonSpritePack *, ponteiro para um gorgonSpritePack
 * @param: BITMAP *, apontador para um superf�cie onde o sprite ser� desenhado
 * @param: RGB *, apontador para um palheta de cores
 * @param: short, o indice do frame
 * @param: char, op��o de desenho, NORMAL, H_FLIP, V_FLIP, HV_FLIP
 * @param: short, o �ngulo que o sprite dever� ser desenhado
 * @param: short, posi��o x que ser� desenhado na superf�cie
 * @param: short, posi��o y que ser� desenhado na superf�cie
 * @return: int gorgon_error
 * @example:
 *
 * short index=0,posX=10,posY=23;
 * BITMAP *buffer;
 * RGB *pal;
 * gorgonSpritePack a;
 *
 *  if(gorgonDrawRotatedSpriteByIndex(&a,buffer,pal,index,NORMAL,60,posX,posY)!=GORGON_OK)
 *	  printf("erro\n");
 */
int gorgonDrawRotatedSpriteByIndex(BITMAP *layer,gorgonSpritePack *a,RGB *pal,short index,char type,short angle, short posX,short posY)
{
	RGB trans = { 63 , 0 , 63 };
	BITMAP *sprite;
	if(index<a->spriteNumber)
	{
		if(&a->sprite[index]!=NULL)
		{
			if(a->sprite[index].image!=NULL && layer!=NULL)
			{
				sprite=create_bitmap(a->sprite[index].image->w,a->sprite[index].image->h);
				if(pal!=NULL)
					set_palette(pal);
				else if(a->sprite[index].pal!=NULL)
					set_palette(a->sprite[index].pal);
				blit(a->sprite[index].image,sprite,0,0,0,0,sprite->w,sprite->h);
				switch(type)
				{
					case NORMAL:
						pivot_sprite(layer,sprite,posX,posY,a->sprite[index].x,a->sprite[index].y, itofix(angle));
						break;
					case H_FLIP:
						pivot_sprite_v_flip(layer,sprite,posX,posY,a->sprite[index].x, a->sprite[index].image->h - a->sprite[index].y, itofix(angle+128));
						break;
					case V_FLIP:
						pivot_sprite_v_flip(layer,sprite,posX,posY,a->sprite[index].x, a->sprite[index].image->h - a->sprite[index].y, itofix(angle));
						break;
					case HV_FLIP:						pivot_sprite(layer,sprite,posX,posY,a->sprite[index].x,a->sprite[index].y, itofix(angle+128));
						break;
				}
				destroy_bitmap(sprite);
				return GORGON_OK;
			}
			return GORGON_INVALID_IMAGE;
		}
		return GORGON_INVALID_SPRITE;
	}
	return GORGON_INVALID_INDEX;
}

/**
 * fun�ao para desenhar um sprite de um spritePack atrav�s de um index
 *
 * @author: Cant�dio Oliveira Fontes
 * @since: 01/05/2008
 * @final: 28/05/2008
 * @param: gorgonSpritePack *, ponteiro para um gorgonSpritePack
 * @param: BITMAP *, apontador para um superf�cie onde o sprite ser� desenhado
 * @param: RGB *, apontador para um palheta de cores
 * @param: short, op��o de desenho, NORMAL, H_FLIP, V_FLIP, HV_FLIP
 * @param: short, o indice do frame
 * @param: short, posi��o x que ser� desenhado na superf�cie
 * @param: short, posi��o y que ser� desenhado na superf�cie
 * @return: int gorgon_erro
 * @example:
 *
 * short index=0,posX=10,posY=23;
 * BITMAP *buffer;
 * RGB *pal;
 * gorgonSpritePack a;
 *
 *  if(gorgonDrawSpriteByIndex(&a,buffer,pal,NORMAL,index,posX,posY)!=GORGON_OK)
 *	  printf("erro\n");
 */
int gorgonDrawSpriteByGroup(BITMAP *layer,gorgonSpritePack *a,RGB *pal,short group,short spr,char type,short posX,short posY)
{
	RGB trans = { 63 , 0 , 63 };
	short i;
	BITMAP *sprite;
	if(a!=NULL)
	{
		if(layer!=NULL)
		{
			for(i=0; (i<a->spriteNumber) && (a->sprite[i].group!=group || a->sprite[i].index!=spr); i++);

			if(i<a->spriteNumber)
			{
				sprite=create_bitmap(a->sprite[i].image->w,a->sprite[i].image->h);
				if(pal!=NULL)
					set_palette(pal);
				else if(a->sprite[i].pal!=NULL)
					set_palette(a->sprite[i].pal);
				blit(a->sprite[i].image,sprite,0,0,0,0,sprite->w,sprite->h);
				switch(type)
				{
					case NORMAL:
						posX-=a->sprite[i].x;
						posY-=a->sprite[i].y;
						draw_sprite(layer,sprite,posX,posY);
						break;
					case H_FLIP:
						posX-=a->sprite[i].image->w - a->sprite[i].x;
						posY-=a->sprite[i].y;
						draw_sprite_h_flip(layer,sprite,posX,posY);
						break;
					case V_FLIP:
						posX-=a->sprite[i].x;
						posY-=a->sprite[i].image->h - a->sprite[i].y;
						draw_sprite_v_flip(layer,sprite,posX,posY);
						break;
					case HV_FLIP:
						posX-=a->sprite[i].image->w - a->sprite[i].x;
						posY-=a->sprite[i].image->h - a->sprite[i].y;
						draw_sprite_vh_flip(layer,sprite,posX,posY);
						break;
				}
				destroy_bitmap(sprite);
				return GORGON_OK;
			}
			return GORGON_INVALID_INDEX;
		}
		return GORGON_INVALID_IMAGE;
	}
	return GORGON_INVALID_SPRITEPACK;
}
/**
 * fun�ao para desenhar um sprite de um spritePack atrav�s de um index, com um corte
 *
 * @author: Cant�dio Oliveira Fontes
 * @since: 02/07/2008
 * @final: 02/07/2008
 * @param: BITMAP *, apontador para um superf�cie onde o sprite ser� desenhado
 * @param: gorgonSpritePack *, ponteiro para um gorgonSpritePack
 * @param: RGB *, apontador para um palheta de cores
 * @param: short, o indice do frame
 * @param: short, posi��o x que ser� desenhado na superf�cie
 * @param: short, posi��o y que ser� desenhado na superf�cie
 * @param: short, ponto X de inicio de corte na imagem de origem
 * @param: short, ponto Y de inicio de corte na imagem de origem
 * @param: short, ponto X de inicio de desenho na imagem de destino
 * @param: short, ponto Y de inicio de desenho na imagem de destino
 * @param: short, largura a ser desenhada
 * @param: short, altura a ser desenhada
 * @return: int gorgon_erro
 * @example:
 *
 * short index=0,posX=10,posY=23;
 * BITMAP *buffer;
 * RGB *pal;
 * gorgonSpritePack spritePack;
 *
 *  if(gorgonBlitSpriteByIndex(&spritePack,buffer,pal,index,posX,posY,0,0,0,0,5,5)!=GORGON_OK)
 *	  printf("erro\n");
 */
int gorgonBlitSpriteByIndex(BITMAP *layer,gorgonSpritePack *a,RGB *pal,short index,short posX,short posY,short sourceX,short sourceY,short destX,short destY,short width,short height)
{
	RGB trans = { 63 , 0 , 63 };
	BITMAP *sprite;
	if(index<a->spriteNumber)
	{
		if(&a->sprite[index]!=NULL)
		{
			if(a->sprite[index].image!=NULL && layer!=NULL)
			{
				sprite=create_bitmap(a->sprite[index].image->w,a->sprite[index].image->h);
				clear_to_color(sprite,makecol(255,0,255));
				if(pal!=NULL)
					set_palette(pal);
				else if(a->sprite[index].pal!=NULL)
					set_palette(a->sprite[index].pal);
				blit(a->sprite[index].image,sprite,sourceX,sourceY,destX,destY,width,height);
				draw_sprite(layer,sprite,posX-a->sprite[index].x,posY-a->sprite[index].y);
				destroy_bitmap(sprite);
				return GORGON_OK;
			}
			return GORGON_INVALID_IMAGE;
		}
		return GORGON_INVALID_SPRITE;
	}
	return GORGON_INVALID_INDEX;
}

