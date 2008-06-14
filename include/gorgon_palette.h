/**
 * lib que trata as funções de paletas de cores
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 29/04/2008
 * @final: 08/05/2008
 */
#ifndef GORGON_PALETTE
#define GORGON_PALETTE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro.h>
#include "gorgon_error.h"

int gorgonLoadPalette_fm(RGB **pal,char *data,int *ofs);
int gorgonLoadPaletteFromMemory(char *data,RGB **pal);
int gorgonLoadInversedPaletteFromMemory(char *data,RGB **pal);
int gorgonUnloadPalette(RGB **pal);
int gorgonLoadPaletteFromFile(char *filename,RGB **pal);
int gorgonDrawPalette(RGB *pal,BITMAP *layer);
int gorgonSavePaletteInFile(RGB *pal,char *filename);
int gorgonSavePalette(RGB *pal,FILE *f);
int gorgonSavePalette16(RGB *pal,FILE *f);
int copyPalette(RGB **a, RGB *b);
void gorgonCreatePaletteFromImage(BITMAP *a, RGB *pal,int r,int g,int b);
#endif

