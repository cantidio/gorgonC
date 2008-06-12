#include "../include/gorgon_palette.h"

/**
 * funcao para carregar uma palheta de cores direto da memória
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
 *      if(gorgonLoadPaletteFromMemory(data,&pal)!=GORGON_OK)
 *          printf("erro\n");
 */
int gorgonLoadPaletteFromMemory(char *data,RGB **pal)
{
	int i,x;
	unsigned char *r,*g,*b;
	*pal=(RGB*)calloc(256,sizeof(RGB));
	if(*pal!=NULL)
	{
	    for(i=255,x=0; i>=0; i--)
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
 * funcao para descarregar uma palheta de cores da memória
 *
 * @autor: Cantidio Oliveira Fontes
 * @since: 29/04/2008
 * @final: 29/04/2008
 * @param: RGB * apontador para a palheta de cores
 * @return: int gorgon_error
 * @exemple:
 *      RGB *pal;
 *      if(gorgonUnloadPaletteFromMemory(pal)!=GORGON_OK)
 *          printf("erro\n");
 */
int gorgonUnloadPalette(RGB **pal)
{
	if(*pal!=NULL)
	{
		free(*pal);
		*pal=NULL;
		return GORGON_OK;
	}
	return GORGON_INVALID_PALETTE;
}
/**
 * funcao para carregar uma palheta de cores de um arquivo
 *
 * @autor: Cantidio Oliveira Fontes
 * @since: 29/04/2008
 * @final: 29/04/2008
 * @param: char * nome do arquivo da palheta
 * @param: RGB * apontador para a palheta de cores
 * @return: int gorgon_error
 * @exemple:
 *      RGB *pal;
 *      if(gorgonUnloadPaletteFromMemory(pal)!=GORGON_OK)
 *          printf("erro\n");
 */
int gorgonLoadPaletteFromFile(char *filename,RGB **pal)
{
	FILE *file=NULL;
	char *data=NULL;
	long size;
	size=file_size(filename);
	if(size>0)
	{
		file=fopen(filename,"rb");
		if(file!=NULL)
		{
			data =(char *) malloc(size);
			fread(&(data[0]),1,size,file);
			gorgonLoadPaletteFromMemory(data,pal);
			fclose(file);
			free(data);
			return GORGON_OK;
		}
		return GORGON_FILE_NOT_FOUND;
	}
	return GORGON_FILE_NOT_FOUND;
}
/**
 * funcao para desenhar uma palheta de cores em um BITMAP qualquer
 *
 * @autor: Cantidio Oliveira Fontes
 * @since: 29/04/2008
 * @final: 30/04/2008
 * @param: RGB * apontador para a palheta de cores
 * @param: BITMAP * apontador para um bitmap, o qual a palheta será desenhada
 * @return: int gorgon_error
 * @exemple:
 *      RGB *pal;
 *      BITMAP *layer;
 *      if(gorgonDrawPalette(pal,layer)!=GORGON_OK)
 *          printf("erro\n");
 */
int gorgonDrawPalette(RGB *pal,BITMAP *layer)
{
	int i,j,x;
	if(layer==NULL) return GORGON_INVALID_IMAGE;
	if(pal==NULL)   return GORGON_INVALID_PALETTE;
	for(i=x=0; i<16; i++)
	{
		for(j=0; j<16; x++,j++)
			rectfill(layer,j*10, i*10,j*10+9, i*10+9, makecol(pal[x].r,pal[x].g,pal[x].b));
	}
	return GORGON_OK;
}
/**
 * funcao para salvar uma determinada palheta em um arquivo
 *
 * @autor: Cantidio Oliveira Fontes
 * @since: 30/04/2008
 * @final: 30/04/2008
 * @param: RGB * apontador para a palheta de cores
 * @param: char * string com o nome do arquivo a ser salvo
 * @return: int gorgon_error
 * @exemple:
 *      RGB *pal;
 *      if(gorgonSavePaletteInFile(pal,"arquivo.act")!=GORGON_OK)
 *          printf("erro\n");
 */
int gorgonSavePaletteInFile(RGB *pal,char *filename)
{
    FILE *file;
    int i;
    file=fopen(filename,"wb");
    for(i=255; i>=0; i--)
    {
        pal[i].r=((pal[i].r*255)/63);
        pal[i].g=((pal[i].g*255)/63);
        pal[i].b=((pal[i].b*255)/63);

        fwrite(&pal[i].r,1,1,file);
        fwrite(&pal[i].g,1,1,file);
        fwrite(&pal[i].b,1,1,file);

        pal[i].r=((pal[i].r*63)/255);
        pal[i].g=((pal[i].g*63)/255);
        pal[i].b=((pal[i].b*63)/255);
    }
    fclose(file);
    return GORGON_OK;
}

/**
 * funcao para salvar uma determinada palheta em um arquivo
 *
 * @autor: Cantidio Oliveira Fontes
 * @since: 30/04/2008
 * @final: 09/06/2008
 * @param: RGB * apontador para a palheta de cores
 * @param: char * string com o nome do arquivo a ser salvo
 * @return: int gorgon_error
 * @exemple:
 *      RGB *pal;
 *      if(gorgonSavePaletteInFile(pal,"arquivo.act")!=GORGON_OK)
 *          printf("erro\n");
 */
int gorgonSavePalette(RGB *pal,FILE *f)
{
    int i;
    if(pal!=NULL)
    {
	    for(i=0; i<256; i++)
	    {
	        pal[i].r=((pal[i].r*255)/63);
	        pal[i].g=((pal[i].g*255)/63);
	        pal[i].b=((pal[i].b*255)/63);

	        fwrite(&pal[i].r,1,1,f);
	        fwrite(&pal[i].g,1,1,f);
	        fwrite(&pal[i].b,1,1,f);

	        pal[i].r=((pal[i].r*63)/255);
	        pal[i].g=((pal[i].g*63)/255);
	        pal[i].b=((pal[i].b*63)/255);
	    }
	    return GORGON_OK;
    }
    return GORGON_INVALID_PALETTE;
}
int gorgonSavePalette16(RGB *pal,FILE *f)
{
    int i;
    if(pal!=NULL)
    {
	    for(i=0; i<16; i++)
	    {
	        pal[i].r=((pal[i].r*255)/63);
	        pal[i].g=((pal[i].g*255)/63);
	        pal[i].b=((pal[i].b*255)/63);

	        fwrite(&pal[i].r,1,sizeof(char),f);
	        fwrite(&pal[i].g,1,sizeof(char),f);
	        fwrite(&pal[i].b,1,sizeof(char),f);

	        pal[i].r=((pal[i].r*63)/255);
	        pal[i].g=((pal[i].g*63)/255);
	        pal[i].b=((pal[i].b*63)/255);
	    }
	    return GORGON_OK;
    }
    return GORGON_INVALID_PALETTE;
}

int copyPalette(RGB **a, RGB *b)
{
	short i;

	*a=(RGB*)calloc(256,sizeof(RGB));
	if(*a==NULL) return GORGON_MEMORY_ERROR;
	for(i=0; i<256; i++)
	{
		(*a)[i].r=b[i].r;
		(*a)[i].g=b[i].g;
		(*a)[i].b=b[i].b;
	}
	return GORGON_OK;
}
/**
 * função para criar uma palheta de 256 cores a partir de uma imagem qualquer
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 07/05/2008
 * @final: 08/05/2008
 * @param: BITMAP *, ponteiro para a imagem
 * @param: RGB *, ponteiro para a palheta de cores
 * @param: int, R
 * @param: int, G
 * @param: int, B
 * @return: int gorgon_error
 * @exemple:
 *
 * PALETTE pal;
 * BITMAP *img;
 * gorgonCreatePaletteFromImage(img,pal,255,0,255);
*/
void gorgonCreatePaletteFromImage(BITMAP *a, RGB *pal,int r,int g,int b)
{
    int x,y,z;
    int color;
    int trans=makecol32(r,g,b);
    for(z=0; z<256; pal[z].r=r,pal[z].g=g,pal[z].b=b,z++);
    for(x=0; x<a->w; x++)
        for(y=0; y<a->h; y++)
        {
            color=_getpixel32(a,x,y);
            if(color!=trans)
            for(z=1; z<256 && color!=makecol(pal[z].r,pal[z].g,pal[z].b); z++)
                if(trans==makecol32(pal[z].r,pal[z].g,pal[z].b))
                {
                    pal[z].r=getr32(color);
                    pal[z].g=getg32(color);
                    pal[z].b=getb32(color);
                    break;
                }
        }
    for(z=0; z<256; pal[z].r/=4,pal[z].g/=4,pal[z].b/=4,z++);
}
