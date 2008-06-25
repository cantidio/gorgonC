/**
 * Arquivo com funções que lidam com o armazenamento de Backgrounds assim como o carregamento dos mesmos
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 24/26/2008
 * @final: 25/06/2008
 */
#ifndef GORGON_BACKGROUND_FILE
#define GORGON_BACKGROUND_FILE

#include "gorgon_background.h"

int gorgonSaveTile_f(FILE *file, gorgonTile *tile);
int gorgonSaveLayer_f(FILE *file, gorgonLayer *layer);
int gorgonSaveLayerPack_f(FILE *file,gorgonLayerPack *layerPack);
int gorgonSaveBackground_f(FILE *file, gorgonBackground *background);
int gorgonSaveBackground(char *filename,gorgonBackground *background);

int gorgonLoadTile_fm(gorgonTile *tile,char *data, int *ofs);
int gorgonLoadLayer_fm(gorgonLayer *layer,char *data, int *ofs);
int gorgonLoadLayerPack_fm(gorgonLayerPack *layerPack, char *data, int *ofs);
int gorgonLoadBackground_fm(gorgonBackground *background, char *data, int *ofs);
int gorgonLoadBackground(gorgonBackground *background,char *filename);
#endif
