#ifndef GORGON_SPRITE_FILE
#define GORGON_SPRITE_FILE
#include<stdlib.h>
#include "gorgon_error.h"
#include "gorgon_sprite.h"
#define GORGON_SPRITEPACK_FILE 32
#define GORGON_SPRITEPACK_FILE_LOCK 123

int gorgonSaveSprite_f(FILE *file,gorgonSprite *sprite);
int gorgonSaveSpritePack_f(FILE *file, gorgonSpritePack *spritePack);

int gorgonSaveSprite(char *filename,gorgonSprite *sprite);
int gorgonSaveSpritePack(char *filename,gorgonSpritePack *spritePack);

int gorgonLoadSprite_fm(gorgonSprite *sprite, char *data, int *ofs);
int gorgonLoadSpritePack_fm(gorgonSpritePack *spritePack, char *data, int *ofs);

int gorgonLoadSprite(gorgonSprite *sprite,char *filename);
int gorgonLoadSpritePack(gorgonSpritePack *spritePack,char *filename);
#endif
