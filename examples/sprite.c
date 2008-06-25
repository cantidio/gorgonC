#include "../include/gorgon.h"

/**
 * arquivo de exemplo de funções de sprite
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 13/06/2008
 * @final: 14/06/2008
 */
 
void init()
{
	int depth;
	if (allegro_init() != 0)	exit(1);
	install_timer();
	install_keyboard();
	key[KEY_ENTER]=0;
	install_mouse();
	depth = desktop_color_depth();
	if (depth == 0) depth = 16;
	set_color_depth(depth);

	if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, 320, 240, 0, 0))
	{
		if (set_gfx_mode(GFX_AUTODETECT, 320, 240, 0, 0))
			exit(1);
	}
}

void denit()
{
	remove_keyboard();
	remove_timer();
	allegro_exit();
}
int main()
{
	gorgonSpritePack spritePack1;
	gorgonSpritePack spritePack;
	init();	

	if(gorgonLoadSpritePackFromSff(&spritePack1,"yamatto.sff")!=GORGON_OK)		return 1;
	if(gorgonSaveSpritePack("yamatto.spk",&spritePack1)!=GORGON_OK)		return 1;
	if(gorgonLoadSpritePack(&spritePack,"yamatto.spk")!=GORGON_OK)			return 1;

	while(!key[KEY_ESC])
	{
		gorgonDrawSpriteByIndex(screen,&spritePack,NULL,0,NORMAL,200,200);
		
	}
	denit();
	return 0;
}
END_OF_MAIN()
