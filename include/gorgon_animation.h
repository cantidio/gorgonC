/**
 * lib que lida com a criação destruição e função para animações
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 01/05/2008
 * @final: 09/05/2008
*/
#ifndef GORGON_ANIMATION
#define GORGON_ANIMATION
#include<allegro.h>
#include "gorgon_error.h"
#include "gorgon_sprite.h"

#define CLSN_GREEN  0
#define CLSN_BLUE   1
#define CLSN_RED    2
typedef struct
{
	short *x1;
	short *x2;
	short *y1;
	short *y2;
	unsigned short boxNumber;
}gorgonClsn;

typedef struct
{
	gorgonClsn clsnRed; //ataque
	gorgonClsn clsnBlue;//dano
	gorgonClsn clsnUp;  //cima
	gorgonClsn clsnLeft;//esquerda
	gorgonClsn clsnDown;//baixo
	gorgonClsn clsnRight;//direita
	short group;
	short spr;
	short index;
	short x;
	short y;
	short time;
	short effect;		// NORMAL, H_FLIP,V_FLIP,HV_FLIP
	short angle;		//angulo de rotação desse sprite
	short trans;		//valor de transparencia desse sprite
}gorgonFrame;

typedef struct
{
	short action;
	gorgonFrame *frame;
	short looping;
	short frames;
	short frameOn;
	short timeOn;
}gorgonAnimation;

typedef struct
{
	gorgonAnimation *animation;
	short animationNumber;
}gorgonAnimationPack;



int gorgonCreateClsn(gorgonClsn *clsn,short number);
int gorgonSetClsnValues(gorgonClsn *clsn,short index,short x1,short x2,short y1, short y2);
int gorgonCreateFrame(gorgonFrame *a, short group,short spr,short x, short y,short time, short effect);
int gorgonCreateAnimation(gorgonAnimation *a,short action,short frames,short looping);
int gorgonCreateAnimationPack(gorgonAnimationPack *pack,short animation);
int gorgonMakeAnimationIndexes(gorgonAnimation *anim, gorgonSpritePack *sprites);
int gorgonMakeAnimationPackIndexes(gorgonAnimationPack *animationPack,gorgonSpritePack *spritePack);
int gorgonDrawClsn(BITMAP *layer, gorgonClsn *clsn,int color,short posX,short posY,short direction);
int gorgonDrawAnimationClsn(BITMAP *layer, gorgonAnimation *animation,short posX, short posY, short direction);

int gorgonShowAnimation(BITMAP *layer,gorgonAnimation *anim,gorgonSpritePack *sprites,RGB *pal,char type,short posX,short posY);
int gorgonDestroyClsn(gorgonClsn *clsn);
int gorgonDestroyFrame(gorgonFrame *frame);
int gorgonDestroyAnimation(gorgonAnimation *animation);
int gorgonDestroyAnimationPack(gorgonAnimationPack *animationPack);
void gorgonPrintAnimationPackValues(gorgonAnimationPack *pk);
int gorgonAnimationFinished(gorgonAnimation *animation);

int gorgonAnimationClsn(gorgonAnimation *animation1, int x1, int y1, short clsn1, short direction1,gorgonAnimation *animation2, int x2, int y2, short clsn2,short direction2);
#endif
