#ifndef GORGON_PCX

#define GORGON_PCX
#include "gorgon_error.h"
#include "gorgon_palette.h"

/*typedef struct
{
    char identifier;                   // BYTE	Identifier;         PCX Id Number (Always 0x0A)
    int version;                     // BYTE	Version;            Version Number
    int encoding;                    // BYTE	Encoding;           Encoding Format
    int bitsPerPixel;                // BYTE	BitsPerPixel;       Bits per Pixel
    short xStart;                    // WORD	XStart;             Left of image
    short yStart;                    // WORD	YStart;             Top of Image
    short xEnd;                      // WORD	XEnd;               Right of Image
    short yEnd;                      // WORD	YEnd;               Bottom of image
    short horxRes;                   // WORD	HorzRes;            Horizontal Resolution
    short vertRes;                   // WORD	VertRes;            Vertical Resolution
    int Palette[48];// = new int[48];     // BYTE	Palette[48];        16-Color EGA Palette
    int reserved1;                   // BYTE	Reserved1;          Reserved (Always 0)
    int numBitPlanes;                // BYTE	NumBitPlanes;       Number of Bit Planes
    short bytesPerLine;              // WORD	BytesPerLine;       Bytes per Scan-line
    short paletteType;               // WORD	PaletteType;        Palette Type
    short horzScreenSize;            // WORD	HorzScreenSize;     Horizontal Screen Size
    short vertScreenSize;            // WORD	VertScreenSize;     Vertical Screen Size
    char reserved2[54];// = new byte[54]; // BYTE	Reserved2[54];      Reserved (Always 0)

}gorgonPCX;*/

int gorgonLoadPcx_fm(BITMAP **image,char *data,int *ofs);
int gorgonSavePcx_f(FILE *f,BITMAP *image,RGB *pal);
int gorgonSavePcx(const char *filename,BITMAP *image,RGB *pal);

#endif
