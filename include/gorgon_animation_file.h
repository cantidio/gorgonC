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

int gorgonSaveClsn_f(FILE *f, gorgonClsn *Clsn);
int gorgonSaveFrame_f(FILE *f, gorgonFrame *frame);
int gorgonSaveAnimation_f(FILE *f, gorgonAnimation *animation);
int gorgonSaveAnimationPack_f(FILE *f, gorgonAnimationPack *animationPack);


int gorgonSaveClsn(char *filename, gorgonClsn *Clsn);
int gorgonSaveFrame(char *filename, gorgonFrame *frame);
int gorgonSaveAnimation(char *filename, gorgonAnimation *animation);
int gorgonSaveAnimationPack(char *filename, gorgonAnimationPack *animationPack);



int gorgonLoadClsn_fm(gorgonClsn *clsn,char *data,int *ofs);
int gorgonLoadFrame_fm(gorgonFrame *frame,char *data,int *ofs);
int gorgonLoadAnimation_fm(gorgonAnimation *animation,char *data,int *ofs);

int gorgonLoadAnimationPack_fm(gorgonAnimationPack *animationPack,char *data,int *ofs);
int gorgonLoadAnimationPack(gorgonAnimationPack *anim,char *filename);


#endif
