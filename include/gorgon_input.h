#ifndef GORGON_INPUT
#define GORGON_INPUT
#include<allegro.h>
#include "gorgon_error.h"

#define gStick	1
#define	gButton	0
typedef struct
{
	char type;	//0->button,1->stick
	short index;	//qual stick ou botão
	short axis;	//se for stick tem axis x,y
	short pos;	//a posição
}gorgonJoyInput;

typedef struct
{
	short		joystick;//se usa joystick ou não e qual
	short		keyUp;
	short		keyDown;
	short		keyLeft;
	short		keyRight;
	short		keyA;
	short		keyB;
	short		keyC;
	short		keyX;
	short		keyY;
	short		keyZ;
	short		keyStart;
	gorgonJoyInput	joyUp;
	gorgonJoyInput	joyDown;
	gorgonJoyInput	joyLeft;
	gorgonJoyInput	joyRight;
	gorgonJoyInput	joyA;
	gorgonJoyInput	joyB;
	gorgonJoyInput	joyC;
	gorgonJoyInput	joyX;
	gorgonJoyInput	joyY;
	gorgonJoyInput	joyZ;
	gorgonJoyInput	joyStart;
}gorgonInput;

gorgonError gorgonSetJoyInput(gorgonJoyInput *joyInput, char type, short index, short axis, short pos);
gorgonError getDefaultInput(gorgonInput *input);
int checkKeyPushed(gorgonInput *input,char gKey);
#endif
