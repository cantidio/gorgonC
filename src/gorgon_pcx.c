#include "../include/gorgon_pcx.h"
/**
 * funcao para carregar uma imagem pcx na memória para um BITMAP
 *
 * @autor	: Cantídio Oliveira Fontes
 * @since	: 28/11/2007
 * @final	: 12/05/2008
 * @param	: BITMAP ** apontador de apontador de uma imagem BITMAP, que deseja-se obter
 * @param	: char *, apontador para a memória onde o arquivo pcx está
 * @param	: int *, apontador para a posição do arquivo onde a imagem está
 * @return	: int gorgon_error
 * @example	:
 *
 * BITMAP *image;
 * char *data;
 * int ofs=0;
 * if(gorgonLoadPcxFromMemory(&image,data,&ofs)!=GORGON_OK)
 *		printf("erro\n");
 */
int gorgonLoadPcxFromMemory(BITMAP **image,char *data,int *ofs)
{
	char	*identifier;
	char	*version;
	char	*encoding;
	char	*bitsPerPixel;
	short	*xStart;
	short	*yStart;
	short	*xEnd;
	short	*yEnd;
	short	*hRes;
	short	*vRes;
	char	*palette;
	char	*reserved;
	char	*vnumBitPlanes;
	short	*bytesPerLine;
	short	*paletteType;
  	char	*filler;

  	if(data!=NULL)
  	{
		identifier		= (char *)&data[*ofs];	(*ofs)+=sizeof(char);
		version			= (char *)&data[*ofs];	(*ofs)+=sizeof(char);
		encoding		= (char *)&data[*ofs];	(*ofs)+=sizeof(char);
		bitsPerPixel		= (char *)&data[*ofs];	(*ofs)+=sizeof(char);
		xStart			= (short*)&data[*ofs];	(*ofs)+=sizeof(short);
		yStart			= (short*)&data[*ofs];	(*ofs)+=sizeof(short);
		xEnd			= (short*)&data[*ofs];	(*ofs)+=sizeof(short);
		yEnd			= (short*)&data[*ofs];	(*ofs)+=sizeof(short);
		hRes			= (short*)&data[*ofs];	(*ofs)+=sizeof(short);
		vRes			= (short*)&data[*ofs];	(*ofs)+=sizeof(short);
		palette			= (char *)&data[*ofs];	(*ofs)+=48*sizeof(char);//paleta de 16 cores
		reserved		= (char *)&data[*ofs];	(*ofs)+=sizeof(char);
		vnumBitPlanes		= (char *)&data[*ofs];	(*ofs)+=sizeof(char);
		bytesPerLine		= (short*)&data[*ofs];	(*ofs)+=sizeof(short);
		paletteType		= (short*)&data[*ofs];	(*ofs)+=sizeof(short);
		filler			= (char *)&data[*ofs];	(*ofs)+=58*sizeof(char);//informação inutil...

		if(*bitsPerPixel==8)
		{
			short w=*xEnd-*xStart+1;
			short h=*yEnd-*yStart+1;
			short y;
			short x;
			int value;
			int count;
			*image=create_bitmap_ex(8,w,h);
			for (y=0; y < h; ++y)
			{
				x=0;
				while (x < *bytesPerLine)
				{
					value = data[*ofs]; //check if upper 2 bit are set
					(*ofs) +=1;
					if ((value & 0xc0) == 0xc0)
					{
						count = value & 0x3f;
						value = data[*ofs];
						(*ofs) +=1;
					}
					else
						count = 1;
					while (count > 0)
					{
						if (x < (*image)->w)
							(*image)->line[y][x] = value;
						++x;
						--count;
					}
				}
			}
			return GORGON_OK;
		}
		return GORGON_INVALID_IMAGE;
	}
	return GORGON_INVALID_MEMORY;
}

/**
 * função para salvar uma imagem BMP para um arquivo pcx
 *
 * @author	: Cantídio Oliveira Fontes
 * @since 	: 06/06/2008
 * @final 	: 11/06/2008
 * @param 	: BITMAP *, ponteiro da imagem a ser salva
 * @param 	: FILE *, ponteiro para o arquivo de destino
 * @param 	: RGB *, ponteiro para a paleta de cores a ser usada
 * @return	: int gorgon_error
 * @example	:
 */
int gorgonSavePcx_f(FILE *file,BITMAP *image,RGB *pal)
{
	char	pixel;
	char	savePixel;
	int 	count;
	int 	x;
	int 	y;
	int 	depth;
	
	char	identifier	= 10;
	char	version		= 5;
	char	encoding	= 1;
	char	bitsPerPixel	= 8;
	short	xStart		= 0;
	short	yStart		= 0;
	short	xEnd		= 0;
	short	yEnd		= 0;
	short	hRes		= 320;
	short	vRes		= 200;
	char	reserved	= 0;
	char	bitPlanes	= 0;
	short	bytesPerLine	= 0;
	short	paletteType	= 1;
  	char	filler[58];
	
	if(file!=NULL)
	{
		if(image!=NULL)
		{
			for(count=0; count<58; filler[count]=0,count++);
		  	strcpy(filler,"pcx image saved using gorgonlib.");
		  	
		  	depth		= bitmap_color_depth(image);
		  	xEnd		= image->w-1;
		  	yEnd		= image->h-1;
		  	bitPlanes	= (depth==8) ? 1 : 3;
		  	bytesPerLine	= image->w;

			fwrite(&identifier,1,sizeof(char),file);
			fwrite(&version,1,sizeof(char),file);
			fwrite(&encoding,1,sizeof(char),file);
			fwrite(&bitsPerPixel,1,sizeof(char),file);
			
			fwrite(&xStart,1,sizeof(short),file);
			fwrite(&yStart,1,sizeof(short),file);
			fwrite(&xEnd,1,sizeof(short),file);
			fwrite(&yEnd,1,sizeof(short),file);
			fwrite(&hRes,1,sizeof(short),file);
			fwrite(&vRes,1,sizeof(short),file);
			gorgonSavePalette16_f(file,pal);

			fwrite(&reserved,1,sizeof(char),file);
			fwrite(&bitPlanes,1,sizeof(char),file);
			fwrite(&bytesPerLine,1,sizeof(short),file);
			fwrite(&paletteType,1,sizeof(short),file);
			fwrite(&filler,1,sizeof(char)*58,file);
			
			for (y=0; y<image->h; y++)
			{
				count		= 0;
				savePixel	= 0;
				for (x=0; x<image->w*bitPlanes; x++)
				{
					if (depth == 8)
						pixel = getpixel(image, x, y);
					else
					{
						if (x<image->w)
						{
							pixel = getpixel(image, x, y);
							pixel = getr_depth(depth, pixel);
						}
						else if (x<image->w*2)
						{
							pixel = getpixel(image, x-image->w, y);
							pixel = getg_depth(depth, pixel);
						}
						else
						{
							pixel = getpixel(image, x-image->w*2, y);
							pixel = getb_depth(depth, pixel);
						}
					}
					if (count==0)
					{
						count 		= 1;
						savePixel	= pixel;
					}
					else
					{
						if ((pixel != savePixel) || (count >= 0x3f))
						{
							if ((count > 1) || ((savePixel & 0xC0) == 0xC0))
							{
								count=(0xC0 | count);
								fwrite(&count,1,sizeof(char),file);
							}
							fwrite(&savePixel,1,sizeof(char),file);
							count 		= 1;
							savePixel 	= pixel;
						}
						else	count++;
					}
				}
				if ((count > 1) || ((savePixel & 0xC0) == 0xC0))
				{
					count=(0xC0 | count);
					fwrite(&count,1,sizeof(char),file);
				}
				fwrite(&savePixel,1,sizeof(char),file);
			}
			if(depth==8 && pal!=NULL)
			{
				pixel=12;
				fwrite(&pixel,1,sizeof(char),file);
				gorgonSavePalette_f(file,pal);
			}
			return GORGON_OK;
		}
		return GORGON_INVALID_IMAGE;
	}
	return GORGON_INVALID_FILE;
}

/**
 * função para salvar uma imagem em um arquivo pcx
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 11/06/2008
 * @final: 11/06/2008
 * @param: const char *, string com o nome do arquivo de saida
 * @param: BITMAP *, ponteiro para a imagem a ser salva
 * @param: RGB *pal, palheta de imagem a ser salva no arquivo pcx
 * @return: int gorgon_error
 * @example:
 *
 * RGB *pal;
 * BITMAP *image;
 * 
 * if(gorgonSavePcx("teste.pcx",image,pal)!=GORGON_OK)
 *		printf("erro\n");
 */
int gorgonSavePcx(const char *filename,BITMAP *image,RGB *pal)
{
	FILE *f;
	int error;
	f=fopen(filename,"wb");
	if(f!=NULL)
	{
		error=gorgonSavePcx_f(f,image,pal);
		fclose(f);
		return error;
	}
	return GORGON_FILE_CANNOT_WRITE;
}
