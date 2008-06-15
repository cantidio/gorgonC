#include "../include/gorgon.h"

/**
 * arquivo de exemplo de funções de animação
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 06/06/2008
 * @final: 13/06/2008
 */
 
void init()
{
	int depth;
	if (allegro_init() != 0)	exit(1);
	install_timer();
	install_keyboard();
	install_mouse();
	depth = desktop_color_depth();
	if (depth == 0) depth = 16;
	set_color_depth(depth);

	if(set_gfx_mode(GFX_AUTODETECT, 320, 240, 0, 0))
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
	gorgonAnimationPack animationPack;
	init();
	if(gorgonCreateAnimationPack(&animationPack,1)!=GORGON_OK)				return 1;
	if(gorgonCreateAnimation(&animationPack.animation[0],0,4,0)!=GORGON_OK)			return 1;
	if(gorgonCreateFrame(&animationPack.animation[0].frame[0],0,0,0,0,10,0)!=GORGON_OK)	return 1;
	if(gorgonCreateFrame(&animationPack.animation[0].frame[1],0,1,0,0,10,0)!=GORGON_OK)	return 1;
	if(gorgonCreateFrame(&animationPack.animation[0].frame[2],0,2,0,0,10,0)!=GORGON_OK)	return 1;
	if(gorgonCreateFrame(&animationPack.animation[0].frame[3],0,1,0,0,10,0)!=GORGON_OK)	return 1;
	if(gorgonSaveAnimationPack("teste.apk",&animationPack)!=GORGON_OK)			return 1;
	if(gorgonDestroyAnimationPack(&animationPack)!=GORGON_OK)				return 1;
	if(gorgonLoadAnimationPack(&animationPack,"teste.apk")!=GORGON_OK)			return 1;
	if(gorgonDestroyAnimationPack(&animationPack)!=GORGON_OK)				return 1;
	denit();
	return 0;
}
END_OF_MAIN()
