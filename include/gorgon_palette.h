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

int gorgonSavePalette_f(FILE *f,RGB *palette);
int gorgonSavePalette16_f(FILE *file,RGB *palette);

int gorgonSavePalette(char *filename,RGB *palette);
int gorgonSavePalette16(char *filename,RGB *palette);

int gorgonLoadPalette_fm(RGB **pal,char *data,int *ofs);
int gorgonLoadPalette(RGB **pal,char *filename);

int gorgonDestroyPalette(RGB **palette);
int gorgonCopyPalette(RGB **palette1, RGB *palette2);

int gorgonDrawPalette(BITMAP *layer,RGB *pal);
int gorgonCreatePaletteFromImage(RGB *palette,BITMAP *image,int r,int g,int b);
#endif

