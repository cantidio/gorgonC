#include "../include/gorgon_animation_file.h"

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
 *	  printf("erro");
 * else if(gorgonSaveClsn(f,&Clsn)!=GORGON_OK)
 *	  printf("erro!\n");
 */
int gorgonSaveClsn_f(FILE *file, gorgonClsn *Clsn)
{
	short i;
	if(file!=NULL)
	{
		if(Clsn!=NULL)
		{
			fwrite(&Clsn->boxNumber,1,sizeof(unsigned short),file);
			for(i=0; i<Clsn->boxNumber; i++)
			{
				fwrite(&Clsn->x1[i],1,sizeof(short),file);
				fwrite(&Clsn->y1[i],1,sizeof(short),file);
				fwrite(&Clsn->x2[i],1,sizeof(short),file);
				fwrite(&Clsn->y2[i],1,sizeof(short),file);
			}
			return GORGON_OK;
		}
		return GORGON_INVALID_CLSN;
	}
	return GORGON_INVALID_FILE;
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
 *	  printf("erro");
 * else if(gorgonSaveFrame(f,&frame)!=GORGON_OK)
 *	  printf("erro!\n");
 */
int gorgonSaveFrame_f(FILE *file, gorgonFrame *frame)
{
	if(file!=NULL)
	{
		if(frame!=NULL)
		{
			fwrite(&frame->group,1,sizeof(short),file);
			fwrite(&frame->spr,1,sizeof(short),file);
			fwrite(&frame->x,1,sizeof(short),file);
			fwrite(&frame->y,1,sizeof(short),file);
			fwrite(&frame->time,1,sizeof(short),file);
			fwrite(&frame->effect,1,sizeof(short),file);
			gorgonSaveClsn_f(file,&frame->clsnRed);
			gorgonSaveClsn_f(file,&frame->clsnBlue);
			gorgonSaveClsn_f(file,&frame->clsnUp);
			gorgonSaveClsn_f(file,&frame->clsnLeft);
			gorgonSaveClsn_f(file,&frame->clsnDown);
			gorgonSaveClsn_f(file,&frame->clsnRight);
			return GORGON_OK;
		}
		return GORGON_INVALID_FRAME;
	}
	return GORGON_INVALID_FILE;
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
 *	  printf("erro");
 * else if(gorgonSaveAnimation(f,&animation)!=GORGON_OK)
 *	  printf("erro!\n");
 */
int gorgonSaveAnimation_f(FILE *file, gorgonAnimation *animation)
{
	int i;
	int error;
	if(file!=NULL)
	{
		if(animation!=NULL)
		{
			fwrite(&animation->action,1,sizeof(short),file);
			fwrite(&animation->looping,1,sizeof(short),file);
			fwrite(&animation->frames,1,sizeof(short),file);
			for(i=0; i<animation->frames; i++)
			{
				error=gorgonSaveFrame_f(file,&animation->frame[i]);
				if(error!=GORGON_OK) return error;
			}
			return GORGON_OK;
		}
		return GORGON_INVALID_ANIMATION;
	}
	return GORGON_INVALID_FILE;
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
 *	  printf("erro");
 */
int gorgonSaveAnimationPack_f(FILE *file, gorgonAnimationPack *animationPack)
{
	int i,error;
	char header[55];
	strcpy(header,"AnimationPack file - from Gorgon's library");
	if(file!=NULL)	{
		if(animationPack!=NULL)
		{
			fwrite(&header,1,sizeof(char)*55,file);
			fwrite(&animationPack->animationNumber,1,sizeof(short),file);
			for(i=0; i<animationPack->animationNumber; i++)
			{
				error=gorgonSaveAnimation_f(file,&animationPack->animation[i]);
				if(error!=GORGON_OK) return error;
			}
			return GORGON_OK;
		}
		return GORGON_INVALID_ANIMATIONPACK;
	}
	return GORGON_INVALID_FILE;
}

/**
 * função para salvar um gorgonClsn em um arquivo
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 08/05/2008
 * @final: 11/06/2008
 * @param: char * nome do arquivo que a animação será salva
 * @param: gorgonClsn * ponteiro para uma colisão
 * @return: int gorgon_error
 * @example:
 *
 * gorgonClsn clsn;
 *
 * if(gorgonSaveClsn("teste.clsn",&clsn)!=GORGON_OK)
 *	  printf("erro");
 */
int gorgonSaveClsn(char *filename, gorgonClsn *clsn)
{
	FILE *file;
	int error;
	if(filename!=NULL)
	{
		file=fopen(filename,"wb");
		if(file!=NULL)
		{
				error=gorgonSaveClsn_f(file,clsn);
			fclose(file);
			return error;
		}
		return GORGON_FILE_CANNOT_WRITE;
	}
	return GORGON_INVALID_VALUE;
}

/**
 * função para salvar um gorgonFrame em um arquivo
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 08/05/2008
 * @final: 11/06/2008
 * @param: char * nome do arquivo que o frame será salvo
 * @param: gorgonFrame * ponteiro para um frame
 * @return: int gorgon_error
 * @example:
 *
 * gorgonFrame frame;
 *
 * if(gorgonSaveFrame("teste.frame",&frame)!=GORGON_OK)
 *	  printf("erro");
 */
int gorgonSaveFrame(char *filename, gorgonFrame *frame)
{
	FILE *file;
	int error;
	if(filename!=NULL)
	{
		file=fopen(filename,"wb");
		if(file!=NULL)
		{
				error=gorgonSaveFrame_f(file,frame);
			fclose(file);
			return error;
		}
		return GORGON_FILE_CANNOT_WRITE;
	}
	return GORGON_INVALID_VALUE;
}

/**
 * função para salvar um gorgonAnimation em um arquivo
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 08/05/2008
 * @final: 11/06/2008
 * @param: char * nome do arquivo que a animação será salva
 * @param: gorgonAnimation * ponteiro para uma animação
 * @return: int gorgon_error
 * @example:
 *
 * gorgonAnimation animation;
 *
 * if(gorgonSaveAnimation("teste.animation",&animation)!=GORGON_OK)
 *	  printf("erro");
 */
int gorgonSaveAnimation(char *filename, gorgonAnimation *animation)
{
	FILE *file;
	int error;
	if(filename!=NULL)
	{
		file=fopen(filename,"wb");
		if(file!=NULL)
		{
				error=gorgonSaveAnimation_f(file,animation);
			fclose(file);
			return error;
		}
		return GORGON_FILE_CANNOT_WRITE;
	}
	return GORGON_INVALID_VALUE;
}

/**
 * função para salvar um gorgonAnimationPack em um arquivo
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 08/05/2008
 * @final: 11/06/2008
 * @param: char * nome do arquivo que o pacote de animações será salvo
 * @param: gorgonAnimationPack * ponteiro para um pacote de animações
 * @return: int gorgon_error
 * @exemple:
 *
 * gorgonAnimationPack animPack;
 *
 * if(gorgonSaveAnimationPack("teste.apk",&animPack)!=GORGON_OK)
 *	  printf("erro");
 */
int gorgonSaveAnimationPack(char *filename, gorgonAnimationPack *animationPack)
{
	FILE *file;
	int error;
	file=fopen(filename,"wb");
	if(filename!=NULL)
	{
		if(file!=NULL)
		{
				error=gorgonSaveAnimationPack_f(file,animationPack);
			fclose(file);
			return error;
		}
		return GORGON_FILE_CANNOT_WRITE;
	}
	return GORGON_INVALID_VALUE;
}

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
 * if(gorgonLoadClsn_fm(&clsn,data,&ofs)!=GORGON_OK)
 *	  printf("erro!\n");
 */
int gorgonLoadClsn_fm(gorgonClsn *clsn,char *data,int *ofs)
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
 * if(gorgonLoadFrame_fm(&frame,data,&ofs)!=GORGON_OK)
 *	  printf("erro!\n");
 */
int gorgonLoadFrame_fm(gorgonFrame *frame,char *data,int *ofs)
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
			error=gorgonLoadClsn_fm(&frame->clsnRed,data,ofs);
			if(error!=GORGON_OK) return error;
			error=gorgonLoadClsn_fm(&frame->clsnBlue,data,ofs);
			if(error!=GORGON_OK) return error;
			error=gorgonLoadClsn_fm(&frame->clsnUp,data,ofs);
			if(error!=GORGON_OK) return error;
			error=gorgonLoadClsn_fm(&frame->clsnLeft,data,ofs);
			if(error!=GORGON_OK) return error;
			error=gorgonLoadClsn_fm(&frame->clsnDown,data,ofs);
			if(error!=GORGON_OK) return error;
			error=gorgonLoadClsn_fm(&frame->clsnRight,data,ofs);
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
 * if(gorgonLoadAnimation_fm(&animation,data,&ofs)!=GORGON_OK)
 *	  printf("erro!\n");
 */
int gorgonLoadAnimation_fm(gorgonAnimation *animation,char *data,int *ofs)
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
				error=gorgonLoadFrame_fm(&animation->frame[i],data,ofs);
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
 * if(gorgonLoadAnimationPack_fm(&animationPack,data,&ofs)!=GORGON_OK)
 *	  printf("erro!\n");
 */
int gorgonLoadAnimationPack_fm(gorgonAnimationPack *animationPack,char *data,int *ofs)
{
	int	error;
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
				error=gorgonLoadAnimation_fm(&animationPack->animation[i],data,ofs);
				if(error!=GORGON_OK) return error;
			}
			return GORGON_OK;
		}
		return GORGON_INVALID_ANIMATIONPACK;
	}
	return GORGON_MEMORY_ERROR;
}

/**
 * função para carregar uma gorgonClsn de um arquivo
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 15/06/2008
 * @final: 15/06/2008
 * @param: gorgonClsn * ponteiro para a colisão a ser carregada
 * @param: char * string com o nome do arquivo a ser aberto
 * @return: int gorgon_error
 * @exemple:
 *
 * gorgonClsn clsn;
 * if(gorgonLoadClsn(&clsn,"animation.gcs")!=GORGON_OK)
 *	  printf("erro!\n");
 */
int gorgonLoadClsn(gorgonClsn *clsn,char *filename)
{
	FILE	*file;
	long	size = file_size(filename);
	char	*data;
	int	erro;
	int	ofs=0;
	if(size>0)
	{
		file= fopen(filename,"rb");
		data= (char *)malloc(size);
		if(data!=NULL)
		{
			fread(&(data[0]),1,size, file);
			fclose(file);
			erro=gorgonLoadClsn_fm(clsn,data,&ofs);
			free(data);			
			if(erro!=GORGON_OK) return erro;
			return GORGON_OK;
		}
		return GORGON_MEMORY_ERROR;
	}
	return GORGON_FILE_NOT_FOUND;
}
/**
 * função para carregar uma gorgonFrame de um arquivo
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 15/06/2008
 * @final: 15/06/2008
 * @param: gorgonFrame * ponteiro para o frame a ser carregado
 * @param: char * string com o nome do arquivo a ser aberto
 * @return: int gorgon_error
 * @exemple:
 *
 * gorgonFrame frame;
 * if(gorgonLoadFrame(&frame,"frame.gfm")!=GORGON_OK)
 *	  printf("erro!\n");
 */
int gorgonLoadFrame(gorgonFrame *frame,char *filename)
{
	FILE	*file;
	long	size = file_size(filename);
	char	*data;
	int	erro;
	int	ofs=0;
	if(size>0)
	{
		file= fopen(filename,"rb");
		data= (char *)malloc(size);
		if(data!=NULL)
		{
			fread(&(data[0]),1,size, file);
			fclose(file);
			erro=gorgonLoadFrame_fm(frame,data,&ofs);
			free(data);
			if(erro!=GORGON_OK) return erro;
			return GORGON_OK;
		}
		return GORGON_MEMORY_ERROR;
	}
	return GORGON_FILE_NOT_FOUND;
}
/**
 * função para carregar uma gorgonAnimation de um arquivo
 *
 * @autor: Cantídio Oliveira Fontes
 * @since: 15/06/2008
 * @final: 15/06/2008
 * @param: gorgonAnimation * ponteiro para a animação a ser carregada
 * @param: char * string com o nome do arquivo a ser aberto
 * @return: int gorgon_error
 * @exemple:
 *
 * gorgonAnimation animation;
 * if(gorgonLoadAnimation(&animation,"animation.gan")!=GORGON_OK)
 *	  printf("erro!\n");
 */
int gorgonLoadAnimation(gorgonAnimation *animation,char *filename)
{
	FILE	*file;
	long	size = file_size(filename);
	char	*data;
	int	erro;
	int	ofs=0;
	if(size>0)
	{
		file= fopen(filename,"rb");
		data= (char *)malloc(size);
		if(data!=NULL)
		{
			fread(&(data[0]),1,size, file);
			fclose(file);
			erro=gorgonLoadAnimation_fm(animation,data,&ofs);
			free(data);			
			if(erro!=GORGON_OK) return erro;
			return GORGON_OK;
		}
		return GORGON_MEMORY_ERROR;
	}
	return GORGON_FILE_NOT_FOUND;
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
 * if(gorgonLoadAnimationPack(&animationPack,"animation_exemple.bin")!=GORGON_OK)
 *	  printf("erro!\n");
 */
int gorgonLoadAnimationPack(gorgonAnimationPack *animationPack,char *filename)
{
	FILE	*file;
	long	size = file_size(filename);
	char	*data;
	int	erro;
	int	ofs=0;
	if(size>0)
	{
		file= fopen(filename,"rb");
		data= (char *)malloc(size);
		if(data!=NULL)
		{
			fread(&(data[0]),1,size, file);
			fclose(file);
			erro=gorgonLoadAnimationPack_fm(animationPack,data,&ofs);
			free(data);			
			if(erro!=GORGON_OK) return erro;
			return GORGON_OK;
		}
		return GORGON_MEMORY_ERROR;
	}
	return GORGON_FILE_NOT_FOUND;
}



