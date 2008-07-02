/**
 * lib que possui funções para lidar com sprites
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 30/04/2008
 * @final: 09/05/2008
 */
#ifndef GORGON_SPRITE
#define GORGON_SPRITE
#include <allegro.h>
#include "gorgon_sff.h"
#include "gorgon_palette.h"
#define NORMAL   0
#define H_FLIP   1
#define V_FLIP   2
#define HV_FLIP  3
typedef struct
{
	short	x;
	short	y;
	short	group;
	short	index;
	RGB *pal;
	BITMAP* image;
}gorgonSprite;

typedef struct
{
	gorgonSprite *sprite;
	short spriteNumber;
}gorgonSpritePack;

int gorgonConvertSffToSpritePack(gorgonSpritePack *spritePack, gorgonSff *sff);
int gorgonLoadSpritePackFromSff(gorgonSpritePack *spritePack,char *filename);
int gorgonDestroySprite(gorgonSprite *sprite);
int gorgonDestroySpritePack(gorgonSpritePack *spritePack);
int gorgonDrawSpriteByIndex(BITMAP *layer,gorgonSpritePack *a,RGB *pal,short index,char type,short posX,short posY);
int gorgonDrawRotatedSpriteByIndex(BITMAP *layer,gorgonSpritePack *a,RGB *pal,short index,char type,short angle, short posX,short posY);
int gorgonDrawSpriteByGroup(BITMAP *layer,gorgonSpritePack *a,RGB *pal,short group,short spr,char type,short posX,short posY);
int gorgonBlitSpriteByIndex(BITMAP *layer,gorgonSpritePack *a,RGB *pal,short index,short posX,short posY,short sourceX,short sourceY,short destX,short destY,short width,short height);
#endif
