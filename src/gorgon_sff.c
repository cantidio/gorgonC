#include "../include/gorgon_sff.h"

/**
 * funcao para carregar uma palheta de cores de um arquivo sff que é invertida direto da memória
 *
 * @autor: Cantidio Oliveira Fontes
 * @since: 29/04/2008
 * @final: 12/05/2008
 * @param: unsigned char * dados da palheta
 * @param: RGB ** apontador de apontador de um RGB
 * @return: int gorgon_error
 * @exemple:
 *      RGB *pal;
 *      unsigned char *data;
 *      if(gorgonLoadSffPaletteFromMemory(data,&pal)!=GORGON_OK)
 *          printf("erro\n");
 */
int gorgonLoadSffPaletteFromMemory(char *data,RGB **pal)
{
	int i,x;
	unsigned char *r,*g,*b;
	*pal=(RGB*)calloc(256,sizeof(RGB));
	if(*pal!=NULL)
	{
	    for(i=0,x=0; i<256; i++)
		{
			r = (unsigned char*)&data[x++];
			g = (unsigned char*)&data[x++];
			b = (unsigned char*)&data[x++];
			(*pal)[i].r = *r/4;
			(*pal)[i].g = *g/4;
			(*pal)[i].b = *b/4;
		}
		return GORGON_OK;
	}
	return GORGON_MEMORY_ERROR;
}

/**
 * função para carregar um sprite de um arquivo sff direto da memória
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 28/11/2007
 * @final: 09/06/2008
 * @param: gorgonSff * apontador para um gorgonSff
 * @param: short, indice que guardará o sprite do sff
 * @param: char * apontador para os dados na memória do sprite
 * @param: int * apontador para o marcador da posição da memória atual
 * @return: int gorgon_error
 *
 * gorgonSff sff;
 * char data;
 * int ofs;
 * if(gorgonLoadSffSpriteFromMemory(&sff,0,&data,&ofs)!=GORGON_OK)
 *      printf("erro\n");
 */
int gorgonLoadSffSpriteFromMemory(gorgonSff *sff,short index,char *data,int *ofs)
{
    int   *nextSubFile;
	int   *sizeOfData;
	short *x;
	short *y;
	short *groupNumber;
	short *imageIndex;
	short *prevIndex;
	char  *reusePalette;
	char  *comment;
	if(data!=NULL)
	{
		nextSubFile	= (int *) 	&data[*ofs];	(*ofs)+=sizeof(int);
		sizeOfData	= (int *) 	&data[*ofs];	(*ofs)+=sizeof(int);
		x			= (short *) &data[*ofs];	(*ofs)+=sizeof(short);
		y			= (short *) &data[*ofs];	(*ofs)+=sizeof(short);
		groupNumber	= (short *) &data[*ofs];	(*ofs)+=sizeof(short);
		imageIndex	= (short *) &data[*ofs];	(*ofs)+=sizeof(short);
		prevIndex	= (short *) &data[*ofs];	(*ofs)+=sizeof(short);
		reusePalette= (char *)	&data[*ofs];	(*ofs)+=sizeof(char);
		comment		= (char *)	&data[*ofs];	(*ofs)+=13*sizeof(char);

        sff->sprite[index].x	= *x;
        sff->sprite[index].y	= *y;
        sff->sprite[index].group= *groupNumber;
        sff->sprite[index].index= *imageIndex;

        if (*sizeOfData == 0)
        {
            sff->sprite[index].image		= sff->sprite[*prevIndex].image;
            sff->sprite[index].pal			= sff->sprite[*prevIndex].pal;
            sff->sprite[index].imageLinked	= 1;
            sff->sprite[index].paletteLinked= 1;
        }
        else
        {
            sff->sprite[index].imageLinked=0;
            gorgonLoadPcxFromMemory(&sff->sprite[index].image,data,ofs);
            if (!(int)*reusePalette)
            {
                sff->sprite[index].paletteLinked=0;
				gorgonLoadSffPaletteFromMemory(&data[(*nextSubFile) - 768],&sff->sprite[index].pal);
            }
            else if(index>0)
            {
                sff->sprite[index].pal = sff->sprite[index-1].pal;
                sff->sprite[index].paletteLinked=1;
            }
            else sff->sprite[index].pal =NULL;
        }
        (*ofs)=*nextSubFile;
        return GORGON_OK;
	}
	return GORGON_INVALID_MEMORY;
}

/**
 * funcao para caregar um arquivo sff direto da memória
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 28/11/2007
 * @final: 11/05/2008
 * @param: gorgonSff * apontador para um gorgonSff que guardará as informações
 * @param: char * apontador para os dados na memória do arquivo sff
 * @param: int * apontador para o marcador da posição de memória que o arquivo está, se for o primeira arquivo, será 0
 * @return: int gorgon_error
 * @exemple:
 *
 * char data;
 * gorgonSff sff;
 * int ofs=0;
 * if(gorgonLoadSffFromMemory(&sff,&data,&ofs)!=GORGON_OK)
 *		printf("erro\n");
 */
int gorgonLoadSffFromMemory(gorgonSff *sff,char *data,int *ofs)
{
    char    *signature;
    char    *version;
    int     *numGroups;
    int     *numImages;
    int     *firstOffSet;
    int     *sizeSubHeader;
    char    *paletteType;
    char    *blank;
    char    *comment;
    int     i;
    int     error;
    if(data!=NULL)
    {
        signature		=(char*)&data[*ofs];	(*ofs)+=sizeof(char)*12;
        version			=(char*)&data[*ofs];	(*ofs)+=sizeof(char)*4;
        numGroups		=(int *)&data[*ofs];	(*ofs)+=sizeof(int);
        numImages		=(int *)&data[*ofs];	(*ofs)+=sizeof(int);
        firstOffSet		=(int *)&data[*ofs];	(*ofs)+=sizeof(int);
        sizeSubHeader	=(int *)&data[*ofs];	(*ofs)+=sizeof(int);
        paletteType		=(char*)&data[*ofs];	(*ofs)+=sizeof(char);
        blank			=(char*)&data[*ofs];	(*ofs)+=sizeof(char)*3;
        comment			=(char*)&data[*ofs];	(*ofs)+=sizeof(char)*476;

        sff->spriteNum=*numImages;
        sff->paletteType=*paletteType;
        sff->sprite=(gorgonSffSprite *)malloc(sizeof(gorgonSffSprite)*sff->spriteNum);

        for(i=0; i<sff->spriteNum; i++)
        {
            error=gorgonLoadSffSpriteFromMemory(sff,i,data,ofs);
            if(error!=GORGON_OK)
                return error;
        }
        return GORGON_OK;
    }
    return GORGON_INVALID_MEMORY;
}

/**
 * função para carregar um arquivo sff
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 28/11/2007
 * @final: 11/05/2008
 * @param: gorgonSff * apontador para um gorgonSff que guardará as informações
 * @param: const char * nome do arquivo a ser aberto
 * @return: int gorgon_error
 * @exemple:
 *
 * gorgonSff sff;
 * if(gorgonLoadSff(&sff,"teste.sff")!=GORGON_OK)
 *		printf("erro\n");
 */
int gorgonLoadSff(gorgonSff *sff,const char *filename)
{
    FILE *f;
    long size= file_size(filename);
    int ofs=0;
    char *data;
    if(size>0)
    {
        f=fopen(filename,"rb");
        data=(char *)malloc(size);
        if(data!=NULL)
        {
            fread(&(data[0]),1,size, f);
            fclose(f);
			return gorgonLoadSffFromMemory(sff,data,&ofs);
        }
        return GORGON_MEMORY_ERROR;
    }
    return GORGON_FILE_NOT_FOUND;
}

/**
 * funcao para descaregar um arquivo sff da memória
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 28/11/2007
 * @final: 11/06/2008
 * @param: gorgonSff *sff apontador para um gorgonSff a ser desalocado
 * @return: int gorgon_error
 * @exemple:
 *
 * gorgonSff sff;
 * if(gorgonUnloadSff(&sff)!=GORGON_OK)
 *		printf("erro\n");
 */
int gorgonUnloadSff(gorgonSff *sff)
{
    int i;
    if(sff!=NULL)
    {
	    for(i=0; i<sff->spriteNum; i++)
	    {
	        if(!sff->sprite[i].imageLinked)
	            destroy_bitmap(sff->sprite[i].image);
	        if(!sff->sprite[i].paletteLinked)
	            free(sff->sprite[i].pal);
	    }
	    free(sff->sprite);
	    sff->sprite=NULL;
	    sff->spriteNum=0;
	    return GORGON_OK;
    }
    return GORGON_INVALID_SFF;
}
