#include "../include/gorgon_input.h"

gorgonError gorgonSetJoyInput(gorgonJoyInput *joyInput, char type, short index, short axis, short pos)
{
	if(joyInput!=NULL)
	{
		joyInput->type	= type;
		joyInput->index	= index;
		joyInput->axis	= axis;
		joyInput->pos	= pos;
		return GORGON_OK;
	}
	return GORGON_INVALID_JOY_INPUT;
}
/**
 * funçao para pegar a configuração padrao dos controles
 *
 * @author:	Cantídio Oliveira Fontes
 * @since:	15/11/2007
 * @final:	12/07/2008
 * @param:	gorgonInput*, apontador para a entrada de dados que deseja-se pegar a configuração padrão
 */
gorgonError getDefaultInput(gorgonInput *input)
{
	input->joystick		= -1;//teclado por padrão
	//configuração padrão sdo teclado
	input->keyStart		= KEY_ENTER;
	input->keyUp		= KEY_UP;
	input->keyDown		= KEY_DOWN;
	input->keyLeft		= KEY_LEFT;
	input->keyRight		= KEY_RIGHT;
	input->keyA		= KEY_Q;
	input->keyB		= KEY_W;
	input->keyC		= KEY_E;
	input->keyX		= KEY_A;
	input->keyY		= KEY_S;
	input->keyZ		= KEY_D;
	
	//configuração padrão de joystick
	gorgonSetJoyInput(&input->joyUp,	gStick,		0,	1,	-127);
	gorgonSetJoyInput(&input->joyDown,	gStick,		0,	1,	127);
	gorgonSetJoyInput(&input->joyLeft,	gStick,		0,	0,	-127);
	gorgonSetJoyInput(&input->joyRight,	gStick,		0,	0,	127);
	gorgonSetJoyInput(&input->joyStart,	gButton,	11,	0,	0);
	gorgonSetJoyInput(&input->joyA,		gButton,	3,	0,	0);
	gorgonSetJoyInput(&input->joyB,		gButton,	0,	0,	0);
	gorgonSetJoyInput(&input->joyC,		gButton,	2,	0,	0);
	gorgonSetJoyInput(&input->joyX,		gButton,	1,	0,	0);
	gorgonSetJoyInput(&input->joyY,		gButton,	6,	0,	0);
	gorgonSetJoyInput(&input->joyZ,		gButton,	7,	0,	0);
}
/**
 * checkKeyPushed
 *
 * @author:	Cantídio Oliveira Fontes
 * @since:	16/11/2007
 * @final:	12/07/2008
 * @param:	gorgonInput*, a estrutura de entrada do jogador 
 * @param:	char, o comando que deseja-se verificar se foi ativado ou não
 * @return: 	int retorna 0 ou 1
 * @abstract: 	função que recebe a estrutura de entrada do jogador e qual tecla deseja-se verificar se foi apertada
 */
int checkKeyPushed(gorgonInput *input,char gKey)
{
	if(input!=NULL)
	{
		switch(gKey)
		{
			case 'A':
				if(input->joystick!=-1)//se estiver usando algum joystick
				{
					if(input->joyA.type==0 && joy[input->joystick].button[input->joyA.index].b) return 1;
	   				else if(input->joyA.type==1 && joy[input->joystick].stick[input->joyA.index].axis[input->joyA.axis].pos==input->joyA.pos) return 1;
				}
				else if(key[input->keyA]) return 1;
				break;
			case 'B':
				if(input->joystick!=-1)//se estiver usando algum joystick
				{
					if(input->joyB.type==0 && joy[input->joystick].button[input->joyB.index].b) return 1;
	   				else if(input->joyB.type==1 && joy[input->joystick].stick[input->joyB.index].axis[input->joyB.axis].pos==input->joyB.pos) return 1;
				}
				else if(key[input->keyB]) return 1;
				break;
			case 'C':
				if(input->joystick!=-1)//se estiver usando algum joystick
				{
					if(input->joyC.type==0 && joy[input->joystick].button[input->joyC.index].b) return 1;
	   				else if(input->joyC.type==1 && joy[input->joystick].stick[input->joyC.index].axis[input->joyC.axis].pos==input->joyC.pos) return 1;
				}
				else if(key[input->keyC]) return 1;
				break;
			case 'X':
				if(input->joystick!=-1)//se estiver usando algum joystick
				{
					if(input->joyX.type==0 && joy[input->joystick].button[input->joyX.index].b) return 1;
	   				else if(input->joyX.type==1 && joy[input->joystick].stick[input->joyX.index].axis[input->joyX.axis].pos==input->joyX.pos) return 1;
				}
				else if(key[input->keyX]) return 1;
				break;
			case 'Y':
				if(input->joystick!=-1)//se estiver usando algum joystick
				{
					if(input->joyY.type==0 && joy[input->joystick].button[input->joyY.index].b) return 1;
	   				else if(input->joyY.type==1 && joy[input->joystick].stick[input->joyY.index].axis[input->joyY.axis].pos==input->joyY.pos) return 1;
				}
				else if(key[input->keyY]) return 1;
				break;
			case 'Z':
				if(input->joystick!=-1)//se estiver usando algum joystick
				{
					if(input->joyZ.type==0 && joy[input->joystick].button[input->joyZ.index].b) return 1;
	   				else if(input->joyZ.type==1 && joy[input->joystick].stick[input->joyZ.index].axis[input->joyZ.axis].pos==input->joyZ.pos) return 1;
				}
				else if(key[input->keyZ]) return 1;
				break;
			case 'S':
				if(input->joystick!=-1)//se estiver usando algum joystick
				{
					if(input->joyStart.type==0 && joy[input->joystick].button[input->joyStart.index].b) return 1;
	   				else if(input->joyStart.type==1 && joy[input->joystick].stick[input->joyStart.index].axis[input->joyStart.axis].pos==input->joyStart.pos) return 1;
				}
				else if(key[input->keyStart]) return 1;
				break;
			case 'U':
				if(input->joystick!=-1)//se estiver usando algum joystick
				{
					if(input->joyUp.type==0 && joy[input->joystick].button[input->joyUp.index].b) return 1;
	   				else if(input->joyUp.type==1 && joy[input->joystick].stick[input->joyUp.index].axis[input->joyUp.axis].pos==input->joyUp.pos) return 1;
				}
				else if(key[input->keyUp]) return 1;
				break;
			case 'D':
				if(input->joystick!=-1)//se estiver usando algum joystick
				{
					if(input->joyDown.type==0 && joy[input->joystick].button[input->joyDown.index].b) return 1;
	   				else if(input->joyDown.type==1 && joy[input->joystick].stick[input->joyDown.index].axis[input->joyDown.axis].pos==input->joyDown.pos) return 1;
				}
				else if(key[input->keyDown]) return 1;
				break;
			case 'L':
				if(input->joystick!=-1)//se estiver usando algum joystick
				{
					if(input->joyLeft.type==0 && joy[input->joystick].button[input->joyLeft.index].b) return 1;
	   				else if(input->joyLeft.type==1 && joy[input->joystick].stick[input->joyLeft.index].axis[input->joyLeft.axis].pos==input->joyLeft.pos) return 1;
				}
				else if(key[input->keyLeft]) return 1;
				break;
			case 'R':
				if(input->joystick!=-1)//se estiver usando algum joystick
				{
					if(input->joyRight.type==0 && joy[input->joystick].button[input->joyRight.index].b) return 1;
	   				else if(input->joyRight.type==1 && joy[input->joystick].stick[input->joyRight.index].axis[input->joyRight.axis].pos==input->joyRight.pos) return 1;
				}
				else if(key[input->keyRight]) return 1;
				break;
		}
	}
	return 0;
}
