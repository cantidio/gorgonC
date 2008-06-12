#include "../include/gorgon_animation_file.h"

/**
 * função para carregar uma gorgonClsn da memória
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 08/05/2008
 * @final: 09/05/2008
 * @param: gorgonClsn * ponteiro para colisão
 * @param: char * ponteiro para a memória referente à gorgonClsn
 * @param: int * ponteiro para a posição de memória que começará a ser lida
 * @return: int gorgon_error
 * @exemple:
 *
 * char *data;
 * gorgonClsn clsn;
 * int ofs=0;
 * if(gorgonLoadClsnFromMemory(&clsn,data,&ofs)!=GORGON_OK)
 *      printf("erro!\n");
 */
int gorgonLoadClsnFromMemory(gorgonClsn *clsn,char *data,int *ofs)
{
    unsigned short *clsnNumber;
    short *x1;
	short *x2;
	short *y1;
	short *y2;
	short i;
	int error;
	if(data!=NULL)
	{
        clsnNumber=(unsigned short *) &data[*ofs];
        (*ofs)+=sizeof(unsigned short);
        gorgonCreateClsn(clsn,*clsnNumber);
        if(clsnNumber>0)
        {
            for(i=0; i<*clsnNumber; i++)
            {
                x1=(short *) &data[*ofs];
                (*ofs)+=sizeof(short);
                y1=(short *) &data[*ofs];
                (*ofs)+=sizeof(short);
                x2=(short *) &data[*ofs];
                (*ofs)+=sizeof(short);
                y2=(short *) &data[*ofs];
                (*ofs)+=sizeof(short);
                error=gorgonSetClsnValues(clsn,i,*x1,*x2,*y1,*y2);
                if(error!=GORGON_OK) return error;
            }
        }
        return GORGON_OK;
	}
	return GORGON_INVALID_MEMORY;
}
/**
 * função para carregar um gorgonFrame da memória
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 08/05/2008
 * @final: 09/05/2008
 * @param: gorgonFrame * ponteiro para o frame a ser carregado
 * @param: char * ponteiro para a memória referente ao gorgonFrame
 * @param: int * ponteiro para a posição de memória que começará a ser lida
 * @return: int gorgon_error
 * @exemple:
 *
 * char *data;
 * gorgonFrame frame;
 * int ofs=0;
 * if(gorgonLoadFrameFromMemory(&frame,data,&ofs)!=GORGON_OK)
 *      printf("erro!\n");
 */
int gorgonLoadFrameFromMemory(gorgonFrame *frame,char *data,int *ofs)
{
    short *group;
	short *spr;
	//short *index;
	short *x;
	short *y;
	short *time;
	short *effect;
	short error;
    if(data!=NULL)
	{
	    if(frame!=NULL)
	    {
            group=(short *) &data[*ofs];
            (*ofs)+=sizeof(short);
            spr=(short *) &data[*ofs];
            (*ofs)+=sizeof(short);
            /*index=(short *) &data[*ofs];
            (*ofs)+=sizeof(short);*/
            x=(short *) &data[*ofs];
            (*ofs)+=sizeof(short);
            y=(short *) &data[*ofs];
            (*ofs)+=sizeof(short);
            time=(short *) &data[*ofs];
            (*ofs)+=sizeof(short);
            effect=(short *) &data[*ofs];
            (*ofs)+=sizeof(short);

            error=gorgonCreateFrame(frame,*group,*spr,*x,*y,*time,*effect);
            if(error!=GORGON_OK) return error;
            error=gorgonLoadClsnFromMemory(&frame->clsnRed,data,ofs);
            if(error!=GORGON_OK) return error;
            error=gorgonLoadClsnFromMemory(&frame->clsnBlue,data,ofs);
            if(error!=GORGON_OK) return error;
            error=gorgonLoadClsnFromMemory(&frame->clsnUp,data,ofs);
            if(error!=GORGON_OK) return error;
            error=gorgonLoadClsnFromMemory(&frame->clsnLeft,data,ofs);
            if(error!=GORGON_OK) return error;
            error=gorgonLoadClsnFromMemory(&frame->clsnDown,data,ofs);
            if(error!=GORGON_OK) return error;
            error=gorgonLoadClsnFromMemory(&frame->clsnRight,data,ofs);
            if(error!=GORGON_OK) return error;
            return GORGON_OK;
	    }
	    return GORGON_INVALID_FRAME;
	}
	return GORGON_INVALID_MEMORY;
}
/**
 * função para carregar um gorgonAnimation da memória
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 08/05/2008
 * @final: 09/05/2008
 * @param: gorgonAnimation * ponteiro para a animação a ser carregada
 * @param: char * ponteiro para a memória referente ao gorgonAnimation
 * @param: int * ponteiro para a posição de memória que começará a ser lida
 * @return: int gorgon_error
 * @exemple:
 *
 * char *data;
 * gorgonAnimation animation;
 * int ofs=0;
 * if(gorgonLoadAnimationFromMemory(&animation,data,&ofs)!=GORGON_OK)
 *      printf("erro!\n");
 */
int gorgonLoadAnimationFromMemory(gorgonAnimation *animation,char *data,int *ofs)
{
    short *action;
    short *looping;
	short *frames;
    short i;
    int error;

	if(data!=NULL)
    {
        if(animation!=NULL)
        {
            action=(short*)&data[*ofs];
            (*ofs)+=sizeof(short);
            looping=(short*)&data[*ofs];
            (*ofs)+=sizeof(short);
            frames=(short*)&data[*ofs];
            (*ofs)+=sizeof(short);
            error=gorgonCreateAnimation(animation,*action,*frames,*looping);
            if(error!=GORGON_OK) return error;
            for(i=0; i<*frames; i++)
            {
                error=gorgonLoadFrameFromMemory(&animation->frame[i],data,ofs);
                if(error!=GORGON_OK) return error;
            }
            return GORGON_OK;
        }
        return GORGON_INVALID_ANIMATION;
    }
    return GORGON_MEMORY_ERROR;
}
/**
 * função para carregar um gorgonAnimationPack da memória
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 08/05/2008
 * @final: 09/05/2008
 * @param: gorgonAnimationPack * ponteiro para o pacote de animações a ser carregado
 * @param: char * ponteiro para a memória referente ao gorgonAnimation
 * @param: int * ponteiro para a posição de memória que começará a ser lida
 * @return: int gorgon_error
 * @exemple:
 *
 * char *data;
 * gorgonAnimationPack animationPack;
 * int ofs=0;
 * if(gorgonLoadAnimationPackFromMemory(&animationPack,data,&ofs)!=GORGON_OK)
 *      printf("erro!\n");
 */
int gorgonLoadAnimationPackFromMemory(gorgonAnimationPack *animationPack,char *data,int *ofs)
{
	int		error;
	short	i;
	short	*animationNum;
	char	*header;
	if(data!=NULL)
	{
		if(animationPack!=NULL)
		{
            header=(char *)&data[*ofs];
            (*ofs)+=(sizeof(char)*55);
            animationNum=(short*)&data[*ofs];
            (*ofs)+=sizeof(short);
            gorgonCreateAnimationPack(animationPack,*animationNum);

            for(i=0; i<*animationNum; i++)
            {
                error=gorgonLoadAnimationFromMemory(&animationPack->animation[i],data,ofs);
                if(error!=GORGON_OK) return error;
            }
            return GORGON_OK;
        }
        return GORGON_INVALID_ANIMATIONPACK;
    }
    return GORGON_MEMORY_ERROR;
}

/**
 * função para carregar um gorgonAnimationPack de um arquivo
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 08/05/2008
 * @final: 09/05/2008
 * @param: gorgonAnimationPack * ponteiro para o pacote de animações a ser carregado
 * @param: char * string com o nome do arquivo a ser aberto
 * @return: int gorgon_error
 * @exemple:
 *
 * gorgonAnimationPack animationPack;
 * if(gorgonLoadAnimationPackFromFile(&animationPack,"animation_exemple.bin")!=GORGON_OK)
 *      printf("erro!\n");
 */
int gorgonLoadAnimationPack(gorgonAnimationPack *anim,char *filename)
{
    FILE	*f;
    long	size = file_size(filename);
    char	*data;
    int		erro;
    int		ofs=0;
    if(size>0)
    {
        f	= fopen(filename,"rb");
        data= (char *)malloc(size);
        if(data!=NULL)
        {
            fread(&(data[0]),1,size, f);
            fclose(f);
            erro=gorgonLoadAnimationPackFromMemory(anim,data,&ofs);
            if(erro!=GORGON_OK) return erro;
            free(data);
            return GORGON_OK;
        }
        return GORGON_MEMORY_ERROR;
    }
    return GORGON_FILE_NOT_FOUND;
}
/**
 * função para salvar um gorgonClsn em um arquivo
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 08/05/2008
 * @final: 09/05/2008
 * @param: FILE * ponteiro para o arquivo de destino
 * @param: gorgonClsn * ponteiro para a colisão a ser salva
 * @return: int gorgon_error
 * @exemple:
 *
 * FILE *f;
 * gorgonClsn Clsn;
 *
 * f=fopen("clsn.bin","wb");
 * if(f==NULL)
 *      printf("erro");
 * else if(gorgonSaveClsn(f,&Clsn)!=GORGON_OK)
 *      printf("erro!\n");
 */
int gorgonSaveClsn_f(FILE *f, gorgonClsn *Clsn)
{
    short i;
    fwrite(&Clsn->boxNumber,1,sizeof(unsigned short),f);
    for(i=0; i<Clsn->boxNumber; i++)
    {
        fwrite(&Clsn->x1[i],1,sizeof(short),f);
        fwrite(&Clsn->y1[i],1,sizeof(short),f);
        fwrite(&Clsn->x2[i],1,sizeof(short),f);
        fwrite(&Clsn->y2[i],1,sizeof(short),f);
    }
    return GORGON_OK;
}
/**
 * função para salvar um gorgonFrame em um arquivo
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 08/05/2008
 * @final: 09/05/2008
 * @param: FILE * ponteiro para o arquivo de destino
 * @param: gorgonFrame * ponteiro para o frame a ser salva
 * @return: int gorgon_error
 * @exemple:
 *
 * FILE *f;
 * gorgonFrame frame;
 *
 * f=fopen("frame.bin","wb");
 * if(f==NULL)
 *      printf("erro");
 * else if(gorgonSaveFrame(f,&frame)!=GORGON_OK)
 *      printf("erro!\n");
 */
int gorgonSaveFrame_f(FILE *f, gorgonFrame *frame)
{
    fwrite(&frame->group,1,sizeof(short),f);
    fwrite(&frame->spr,1,sizeof(short),f);
    fwrite(&frame->x,1,sizeof(short),f);
    fwrite(&frame->y,1,sizeof(short),f);
    fwrite(&frame->time,1,sizeof(short),f);
    fwrite(&frame->effect,1,sizeof(short),f);
    gorgonSaveClsn_f(f,&frame->clsnRed);
    gorgonSaveClsn_f(f,&frame->clsnBlue);
    gorgonSaveClsn_f(f,&frame->clsnUp);
    gorgonSaveClsn_f(f,&frame->clsnLeft);
    gorgonSaveClsn_f(f,&frame->clsnDown);
    gorgonSaveClsn_f(f,&frame->clsnRight);
    return GORGON_OK;

}
/**
 * função para salvar um gorgonAnimation em um arquivo
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 08/05/2008
 * @final: 09/05/2008
 * @param: FILE * ponteiro para o arquivo de destino
 * @param: gorgonAnimation * ponteiro para a animação a ser salva
 * @return: int gorgon_error
 * @exemple:
 *
 * FILE *f;
 * gorgonAnimation animation;
 *
 * f=fopen("animation.bin","rb");
 * if(f==NULL)
 *      printf("erro");
 * else if(gorgonSaveAnimation(f,&animation)!=GORGON_OK)
 *      printf("erro!\n");
 */
int gorgonSaveAnimation_f(FILE *f, gorgonAnimation *anim)
{
    int i;
    fwrite(&anim->action,1,sizeof(short),f);
    fwrite(&anim->looping,1,sizeof(short),f);
    fwrite(&anim->frames,1,sizeof(short),f);
    for(i=0; i<anim->frames; i++)
    {
        gorgonSaveFrame_f(f,&anim->frame[i]);
    }
    return GORGON_OK;
}

/**
 * função para salvar um gorgonAnimationPack em um arquivo previamente aberto
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 08/05/2008
 * @final: 11/06/2008
 * @param: FILE * ponteiro para o arquivo
 * @param: gorgonAnimationPack * ponteiro para um pacote de animações
 * @return: int gorgon_error
 * @exemple:
 *
 * gorgonAnimationPack animPack;
 * FILE *f;
 *
 * f=fopen("teste.apk","wb");
 * if(gorgonSaveAnimationPack(f,&animPack)!=GORGON_OK)
 *      printf("erro");
 */
int gorgonSaveAnimationPack_f(FILE *f, gorgonAnimationPack *anim)
{
	int i,error;
	char header[55];
	strcpy(header,"AnimationPack file - from Gorgon's library");
    if(f!=NULL)
    {
    	if(anim!=NULL)
    	{
	        fwrite(&header,1,sizeof(char)*55,f);
	        fwrite(&anim->animationNumber,1,sizeof(short),f);
	        for(i=0; i<anim->animationNumber; i++)
	        {
	            error=gorgonSaveAnimation_f(f,&anim->animation[i]);
	            if(error!=GORGON_OK) return error;
	        }
	        return GORGON_OK;
        }
        return GORGON_INVALID_ANIMATIONPACK;
    }
    return GORGON_INVALID_FILE;
}

/**
 * função para salvar um gorgonAnimationPack em um arquivo
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 08/05/2008
 * @final: 11/06/2008
 * @param: char * nome do arquivo que a animação será salva
 * @param: gorgonAnimationPack * ponteiro para um pacote de animações
 * @return: int gorgon_error
 * @exemple:
 *
 * gorgonAnimationPack animPack;
 *
 * if(gorgonSaveAnimationPack("teste.apk",&animPack)!=GORGON_OK)
 *      printf("erro");
 */
int gorgonSaveAnimationPack(char *filename, gorgonAnimationPack *anim)
{
	FILE *f;
	int error;
	f=fopen(filename,"wb");
    if(f!=NULL)
    {
        error=gorgonSaveAnimationPack_f(f,anim);
        fclose(f);
        return error;
    }
    return GORGON_FILE_CANNOT_WRITE;
}


