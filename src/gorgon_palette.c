#include "../include/gorgon_palette.h"

/**
 * funcao para salvar uma determinada palheta em um arquivo
 *
 * @autor: Cantidio Oliveira Fontes
 * @since: 30/04/2008
 * @final: 20/06/2008
 * @param: RGB * apontador para a palheta de cores
 * @param: char * string com o nome do arquivo a ser salvo
 * @return: int gorgon_error
 * @example:
 * RGB *pal;
 *
 * if(gorgonSavePaletteInFile(pal,"arquivo.act")!=GORGON_OK)
 *	printf("erro\n");
 */
int gorgonSavePalette_f(FILE *file,RGB *palette)
{
	int i;
	char r;
	char g;
	char b;
	if(palette!=NULL)
	{
		for(i=255; i>=0; i--)
		{
			r=((palette[i].r*255)/63);
			g=((palette[i].g*255)/63);
			b=((palette[i].b*255)/63);

			fwrite(&r,1,sizeof(char),file);
			fwrite(&g,1,sizeof(char),file);
			fwrite(&b,1,sizeof(char),file);
	    }
	    return GORGON_OK;
    }
    return GORGON_INVALID_PALETTE;
}

/**
 * funcao para salvar uma determinada palheta de 16 cores em um arquivo
 *
 * @autor: Cantidio Oliveira Fontes
 * @since: 05/06/2008
 * @final: 15/06/2008
 * @param: RGB * apontador para a palheta de cores
 * @param: char * string com o nome do arquivo a ser salvo
 * @return: int gorgon_error
 * @example:
 *
 * RGB *pal;
 * FILE *file;
 *
 * if(gorgonSavePalette16_f(file,pal)!=GORGON_OK)
 *	printf("erro\n");
 */
int gorgonSavePalette16_f(FILE *file,RGB *palette)
{
	int i;
	char r;
	char g;
	char b;
	if(palette!=NULL)
	{
		for(i=0; i<16; i++)
		{
			r=((palette[i].r*255)/63);
			g=((palette[i].g*255)/63);
			b=((palette[i].b*255)/63);

			fwrite(&r,1,sizeof(char),file);
			fwrite(&g,1,sizeof(char),file);
			fwrite(&b,1,sizeof(char),file);
	    }
	    return GORGON_OK;
    }
    return GORGON_INVALID_PALETTE;
}


/**
 * funcao para salvar uma determinada palheta em um arquivo
 *
 * @autor: Cantidio Oliveira Fontes
 * @since: 30/04/2008
 * @final: 15/06/2008
 * @param: RGB * apontador para a palheta de cores
 * @param: char * string com o nome do arquivo a ser salvo
 * @return: int gorgon_error
 * @example:
 *
 * RGB *pal;
 * if(gorgonSavePaletteInFile(pal,"arquivo.act")!=GORGON_OK)
 *	printf("erro\n");
 */
int gorgonSavePalette(char *filename,RGB *pal)
{
	int error;
 	FILE *file;
	file=fopen(filename,"wb");
	if(file!=NULL)
	{
		error= gorgonSavePalette_f(file,pal);
		fclose(file);
		return error;
	}
	return GORGON_FILE_CANNOT_WRITE;
}

/**
 * funcao para salvar uma determinada palheta em um arquivo
 *
 * @autor: Cantidio Oliveira Fontes
 * @since: 30/04/2008
 * @final: 15/06/2008
 * @param: RGB * apontador para a palheta de cores
 * @param: char * string com o nome do arquivo a ser salvo
 * @return: int gorgon_error
 * @example:
 *
 * RGB *pal;
 * if(gorgonSavePaletteInFile(pal,"arquivo.act")!=GORGON_OK)
 *	printf("erro\n");
 */
int gorgonSavePalette16(char *filename,RGB *palette)
{
	int error;
 	FILE *file;
	file=fopen(filename,"wb");
	if(file!=NULL)
	{
		error= gorgonSavePalette16_f(file,palette);
		fclose(file);
		return error;
	}
	return GORGON_FILE_CANNOT_WRITE;
}

/**
 * funcao para carregar uma palheta de cores direto da mem�ria
 *
 * @autor: Cantidio Oliveira Fontes
 * @since: 29/04/2008
 * @final: 13/06/2008
 * @param: unsigned char * dados da palheta
 * @param: RGB ** apontador de apontador de um RGB
 * @return: int gorgon_error
 * @example:
 *      RGB *pal;
 *      unsigned char *data;
 *      if(gorgonLoadPaletteFromMemory(data,&pal)!=GORGON_OK)
 *          printf("erro\n");
 */
int gorgonLoadPalette_fm(RGB **palette,char *data,int *ofs)
{
	int i;
	unsigned char *r;
	unsigned char *g;
	unsigned char *b;
	*palette=(RGB*)calloc(256,sizeof(RGB));
	if(*palette!=NULL)
	{
		for(i=255; i>=0; i--)
		{
			r = (unsigned char*)&data[*ofs];	(*ofs)+=sizeof(unsigned char);
			g = (unsigned char*)&data[*ofs];	(*ofs)+=sizeof(unsigned char);	
			b = (unsigned char*)&data[*ofs];	(*ofs)+=sizeof(unsigned char);
			(*palette)[i].r = *r/4;
			(*palette)[i].g = *g/4;
			(*palette)[i].b = *b/4;
		}
		return GORGON_OK;
	}
	return GORGON_INVALID_PALETTE;
}

/**
 * funcao para carregar uma palheta de cores de um arquivo
 *
 * @autor: Cantidio Oliveira Fontes
 * @since: 29/04/2008
 * @final: 15/06/2008
 * @param: char * nome do arquivo da palheta
 * @param: RGB * apontador para a palheta de cores
 * @return: int gorgon_error
 * @example:
 *
 * RGB *palette;
 *
 * if(gorgonLoadPalette(&palette,"palette.act")!=GORGON_OK)
 *	printf("erro\n");
 */
int gorgonLoadPalette(RGB **palette,char *filename)
{
	FILE	*file;
	char	*data;
	long	size=file_size(filename);
	int	ofs=0;
	int	error;
	if(size>0)
	{
		file=fopen(filename,"rb");
		data =(char *) malloc(size);
		if(data!=NULL)
		{		
			fread(&(data[0]),1,size,file);
			fclose(file);		
			error=gorgonLoadPalette_fm(palette,data,&ofs);
			free(data);
			return error;
		}
		return GORGON_MEMORY_ERROR;
	}
	return GORGON_FILE_NOT_FOUND;
}

/**
 * funcao para descarregar uma palheta de cores da mem�ria
 *
 * @autor: Cantidio Oliveira Fontes
 * @since: 29/04/2008
 * @final: 29/04/2008
 * @param: RGB * apontador para a palheta de cores
 * @return: int gorgon_error
 * @example:
 *
 * RGB *palette;
 *
 * if(gorgonDestroyPalette(palette)!=GORGON_OK)
 *	printf("erro\n");
 */
int gorgonDestroyPalette(RGB **palette)
{
	if(*palette!=NULL)
	{
		free(*palette);
		*palette=NULL;
		return GORGON_OK;
	}
	return GORGON_INVALID_PALETTE;
}

/**
 * funcao para desenhar uma palheta de cores em um BITMAP qualquer
 *
 * @autor: Cantidio Oliveira Fontes
 * @since: 29/04/2008
 * @final: 30/04/2008
 * @param: RGB * apontador para a palheta de cores
 * @param: BITMAP * apontador para um bitmap, o qual a palheta ser� desenhada
 * @return: int gorgon_error
 * @example:
 *
 * RGB *pal;
 * BITMAP *layer;
 *
 * if(gorgonDrawPalette(pal,layer)!=GORGON_OK)
 *	printf("erro\n");
 */
int gorgonDrawPalette(BITMAP *layer,RGB *palette)
{
	int i,j,x;
	if(layer!=NULL)
	{
		if(palette!=NULL)
		{
			for(i=x=0; i<16; i++)
			{
				for(j=0; j<16; x++,j++)
					rectfill(layer,j*10, i*10,j*10+9, i*10+9, makecol(palette[x].r,palette[x].g,palette[x].b));
			}
			return GORGON_OK;
		}
		return GORGON_INVALID_PALETTE;
	}
	return GORGON_INVALID_IMAGE;
}

/**
 * funcao para se copiar uma paleta de cores para outra
 *
 * @autor: Cantidio Oliveira Fontes
 * @since: 29/04/2008
 * @final: 15/06/2008
 * @param: RGB ** apontador para a palheta de cores que receber� os valores da segunda
 * @param: RGB * paleta de cores que ir� ser a base
 * @return: int gorgon_error
 * @example:
 *
 *      RGB *palette1;
 *      RGB *palette2;
 *      if(gorgonCopyPalette(&palette1,palette2)!=GORGON_OK)
 *          printf("erro\n");
 */
int gorgonCopyPalette(RGB **palette1, RGB *palette2)
{
	short i;
	if(palette2!=NULL)
	{
		*palette1=(RGB*)calloc(256,sizeof(RGB));
		if(*palette1!=NULL)
		{
			for(i=0; i<256; i++)
			{
				(*palette1)[i].r=palette2[i].r;
				(*palette1)[i].g=palette2[i].g;
				(*palette1)[i].b=palette2[i].b;
			}
			return GORGON_OK;
		}
		return GORGON_MEMORY_ERROR;
	}
	return GORGON_INVALID_PALETTE;
}
/**
 * fun��o para criar uma palheta de 256 cores a partir de uma imagem qualquer
 *
 * @author: Cant�dio Oliveira Fontes
 * @since: 07/05/2008
 * @final: 20/06/2008
 * @param: BITMAP *, ponteiro para a imagem
 * @param: RGB *, ponteiro para a palheta de cores
 * @param: int, R
 * @param: int, G
 * @param: int, B
 * @return: int gorgon_error
 * @example:
 *
 * PALETTE pal;
 * BITMAP *img;
 * gorgonCreatePaletteFromImage(img,pal,255,0,255);
*/
int gorgonCreatePaletteFromImage(RGB *palette,BITMAP *image,int r,int g,int b)
{
	int x,y,z;
	int color;
	int trans=makecol32(r,g,b);
	if(image!=NULL)
	{
		for(z=0; z<256; palette[z].r=r,palette[z].g=g,palette[z].b=b,z++);
		for(y=0; y<image->h; y++)
		{
			for(x=0; x<image->w; x++)	
			{
				color=_getpixel32(image,x,y);
				if(color!=trans)
				{
					for(z=1; z<256 && color!=makecol(palette[z].r,palette[z].g,palette[z].b); z++)
						if(trans==makecol32(palette[z].r,palette[z].g,palette[z].b))
						{
							palette[z].r=getr32(color);
							palette[z].g=getg32(color);
							palette[z].b=getb32(color);
							break;
						}
				}
			}
		}
		for(z=0; z<256; palette[z].r/=4,palette[z].g/=4,palette[z].b/=4,z++);
		return GORGON_OK;
	}
	return GORGON_INVALID_IMAGE;
}
