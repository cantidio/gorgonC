#include "gorgon_input.h"
#ifndef GORGON_COMMAND
#define GORGON_COMMAND

#define SIZE 120
#define LOCK 6
typedef struct
{
	short start;
	char **key;
	short size;
}gorgonInputBuffer;

typedef struct
{
	short	time;	//the time the player has to execute the move
	short	numKeys;
	char 	**key;	//array 
	char 	hold;
}gorgonCommand;

void	createCommand(gorgonCommand *c,char *cmd,short time);
int	checkCommand(inputBuffer *b, gorgonCommand *c);
void	createInputBuffer(inputBuffer *buf);
void	catchCmd(inputBuffer *b,inputType a);
#endif
