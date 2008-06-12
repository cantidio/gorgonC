#ifndef GORGON_SFF

#define GORGON_SFF
#define SPRPALTYPE_SHARED 1
#include "gorgon_pcx.h"
#include "gorgon_palette.h"
#include "gorgon_error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro.h>

/*
typedef struct
{
	char magic[12];
	char version[4];
	int  countGroups;
	int  countImages;
	int  offsetFirstSubFile;
	int  sizeOfSubfileHeader;
	char palType;
	char padding[3];
	char comment[476];
}SFFHeader;
typedef struct
{
	int   nextSubFile;
	int   sizeOfData;
	short x;
	short y;
	short group;
	short curIndex;
	short prevIndex;
	char  reusePalette;
	char  comment[13];
	char  pcxData[1];
}SFFSubFileHeader;
typedef struct SFFEntryStruct
{
	short   x, y, group, curIndex, prevIndex;
	char    isLinkedImage;
	RGB*    pal;
	BITMAP* image;
	char    comment[13];
	struct 	SFFEntryStruct *next;
}SFFEntry;
*/

typedef struct
{
    short x;
	short y;
	short group;
	short index;
	char imageLinked;
	char paletteLinked;
	BITMAP *image;
	RGB *pal;
}gorgonSffSprite;

typedef struct
{
    int     spriteNum;
    char    paletteType;
    gorgonSffSprite *sprite;
}gorgonSff;

int gorgonLoadSffPaletteFromMemory(char *data,RGB **pal);
int gorgonLoadSffSpriteFromMemory(gorgonSff *sff,short index,char *data,int *ofs);
int gorgonLoadSffFromMemory(gorgonSff *sff,char *data,int *ofs);
int gorgonLoadSff(gorgonSff *sff,const char *filename);
int gorgonUnloadSff(gorgonSff *sff);
#endif
