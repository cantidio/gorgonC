/**
 * seção dedicada aos tratamentos de cenário
 *
 */
#ifndef GORGON_BACKGROUND
#define GORGON_BACKGROUND

#define ALL_LAYERS		-1
#define BACK_LAYERS		-2
#define FRONT_LAYERS	-3
#define PLAYER_LAYER	-4

#include "gorgon_error.h"
#include "gorgon_animation.h"

typedef struct
{
	short 		obstacle;
	float 		friction;
	gorgonClsn 	clsn;
}gorgonBackgroundClsn;

typedef struct
{
	short animationIndex;
	short number;
	short *posX;
	short *posY;
}gorgonTile;

typedef struct
{
	float 		scrollingSpeedX;
	float 		scrollingSpeedY;
	short 		tileNumber;
	gorgonTile 	*tile;
}gorgonLayer;

typedef struct
{
	gorgonAnimationPack animationPack;
	gorgonSpritePack	spritePack;
	short 				width;
	short 				height;
	short 				boundLeft;
	short 				boundRight;
	short 				boundDown;
	short 				boundUp;
	short				posX;
	short 				posY;
	short				playerLayer;//qual layer o jogador é desenhado
	short 				layerNumber;
	gorgonLayer 		*layer;
	//music ?
}gorgonBackground;

int gorgonCreateTile(gorgonTile *tile,short animationIndex,short objNumber);
int gorgonDestroyTile(gorgonTile *tile);
int gorgonSetTilePositionByLayer(gorgonTile *tile, short number,short posX,short posY);
int gorgonCreateLayer(gorgonLayer *layer,float scrollingSpeedX,float scrollingSpeedY,short tileNumber);
int gorgonDestroyLayer(gorgonLayer *layer);
int gorgonCreateBackground(gorgonBackground *background,short width,short height,short boundLeft,short boundRight, short boundUp, short boundDown,short posX,short posY,short playerLayer, short layerNumber);
int gorgonDestroyBackground(gorgonBackground *background);

int gorgonDrawTile(BITMAP *buffer,gorgonBackground *background,short layer,short tile);
int gorgonDrawTile(BITMAP *buffer,gorgonTile *tile,short posX,short posY,gorgonSpritePack *spritePack,gorgonAnimationPack *animationPack);
int gorgonDrawLayer(BITMAP *buffer,gorgonBackground *background,short layerNumber);
int gorgonDrawLayer(BITMAP *buffer,gorgonLayer *layer,short posX,short posY, gorgonSpritePack *spritePack,gorgonAnimationPack *animationPack);
int gorgonDrawBackground(BITMAP *buffer,gorgonBackground *background,short type);
#endif
