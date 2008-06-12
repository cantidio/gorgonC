/**
 * lib que lida com as funções de acesso de arquivos das animações, como salvar as animações em arquivos e ler dos mesmos
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 08/05/2008
 * @final: 09/05/2008
 */
#ifndef GORGON_ANIMATION_FILE
#define GORGON_ANIMATION_FILE
#include<allegro.h>
#include "gorgon_animation.h"
int gorgonLoadClsnFromMemory(gorgonClsn *clsn,char *data,int *ofs);
int gorgonLoadFrameFromMemory(gorgonFrame *frame,char *data,int *ofs);
int gorgonLoadAnimationFromMemory(gorgonAnimation *animation,char *data,int *ofs);

int gorgonLoadAnimationPackFromMemory(gorgonAnimationPack *animationPack,char *data,int *ofs);
int gorgonLoadAnimationPack(gorgonAnimationPack *anim,char *filename);

int gorgonSaveClsn_f(FILE *f, gorgonClsn *Clsn);
int gorgonSaveFrame_f(FILE *f, gorgonFrame *frame);
int gorgonSaveAnimation_f(FILE *f, gorgonAnimation *anim);
int gorgonSaveAnimationPack_f(FILE *f, gorgonAnimationPack *anim);

int gorgonSaveAnimationPack(char *filename, gorgonAnimationPack *anim);
#endif
