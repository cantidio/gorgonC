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
	int i=0;
	gorgonSpritePack spritePack1;
	gorgonSpritePack spritePack;
	init();	

	if(gorgonLoadSpritePackFromSff(&spritePack1,"menu.sff")!=GORGON_OK)		return 1;
	if(gorgonSaveSpritePack("menu.spk",&spritePack1)!=GORGON_OK)		return 1;
	if(gorgonLoadSpritePack(&spritePack,"menu.spk")!=GORGON_OK)			return 1;

	while(!key[KEY_ESC])
	{
		clear(screen);
		if(key[KEY_RIGHT] && i<spritePack.spriteNumber-2) i++;
		else if(key[KEY_LEFT] && i>0) i--;
		gorgonDrawSpriteByIndex(screen,&spritePack,NULL,i,NORMAL,200,200);
		textprintf_ex(screen,font,10,10,makecol(255,255,255),-1,"index: %d",i);
		rest(80);
	}
	gorgonDestroySpritePack(&spritePack1);
	gorgonDestroySpritePack(&spritePack);
	denit();
	return 0;
}
END_OF_MAIN()
