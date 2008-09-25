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
	int 	i=0;
	char 	name[30];
	BITMAP *layer;
	PALETTE pal;
	gorgonSpritePack spritePack1;
	gorgonSpritePack spritePack;
	scanf("%s",&name);
	init();
	if(gorgonLoadSpritePackFromSff(&spritePack1,name)!=GORGON_OK)	return 1;
	strcat(name,".spk");
	if(gorgonSaveSpritePack(name,&spritePack1)!=GORGON_OK)		return 1;
	if(gorgonLoadSpritePack(&spritePack,name)!=GORGON_OK)		return 1;
/*layer=create_bitmap(320,100);
	for(i=0; i<spritePack.spriteNumber; i++)
	{
		sprintf(name,"saida_%d.bmp",i);
		printf("%s\n",name);
		spritePack.sprite[i].x=0;
		spritePack.sprite[i].y=spritePack.sprite[i].image->h;
		
		clear_to_color(layer,makecol(255,0,255));
		gorgonDrawSpriteByIndex(layer,&spritePack,NULL,i,H_FLIP,100,80);
		get_pallete(pal);
		save_bmp(name,layer,pal);
		
	}
	i=0;
	destroy_bitmap(layer);*/
	while(!key[KEY_ESC])
	{
		clear(screen);
		if(key[KEY_RIGHT] && i<spritePack.spriteNumber-1) i++;
		else if(key[KEY_LEFT] && i>0) i--;
		gorgonDrawSpriteByIndex(screen,&spritePack,NULL,i,NORMAL,200,200);
		textprintf_ex(screen,font,10,10,makecol(255,255,255),-1,"index: %d",i);
		textprintf_ex(screen,font,10,20,makecol(255,255,255),-1,"Group: %d",spritePack.sprite[i].group);
		textprintf_ex(screen,font,10,30,makecol(255,255,255),-1,"index: %d",spritePack.sprite[i].index);
		textprintf_ex(screen,font,10,40,makecol(255,255,255),-1,"x: %d",spritePack.sprite[i].x);
		textprintf_ex(screen,font,10,50,makecol(255,255,255),-1,"y: %d",spritePack.sprite[i].y);
		rest(80);
	}
	gorgonDestroySpritePack(&spritePack1);
	gorgonDestroySpritePack(&spritePack);
	denit();
	return 0;
}
END_OF_MAIN()
