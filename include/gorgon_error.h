
#ifndef GORGON_ERROR
#define GORGON_ERROR
#define	gorgonError			int
#define GORGON_OK			0	//processo executado com sucesso
#define GORGON_MEMORY_ERROR 		1	//erro ao alocar mem�ria
#define GORGON_FILE_NOT_FOUND		2	//arquivo n�o encontrado
#define GORGON_FILE_CANNOT_WRITE        3	//n�o pode escrever algum arquivo, por falta de espa�o no hd ou por permiss�es.
#define GORGON_INVALID_FILE		4	//arquivo inv�lido
#define GORGON_INVALID_PALETTE		5	//paleta inv�lida, provavelmente ponteiro em NULL
#define GORGON_INVALID_IMAGE		6	//imagem inv�lida, provavelmente ponteiro em NULL
#define GORGON_INVALID_SPRITE           7	//valor de sprite fornecido � inv�lido, provavelmente ponteiro em NULL
#define GORGON_INVALID_SFF		8	//sff inv�lido, provavelmente ponteiro em NULL
#define GORGON_INVALID_INDEX		9	//indice de vetor fornecido � invalido
#define GORGON_INVALID_VALUE            10	//valor invalido
#define GORGON_INVALID_FRAME            11	//valor de frame fornecido � inv�lido, provavelmente ponteiro em NULL
#define GORGON_INVALID_CLSN             12	//valor de Clsn fornecido � inv�lido, provavelmente ponteiro em NULL ou numero de retangulos de colis�o abaixo de 1
#define GORGON_INVALID_SPRITEPACK       13	//valor de spritepack fornecido � inv�lido, provavelmente ponteiro em NULL
#define GORGON_INVALID_ANIMATION        14	//valor de animacao fornecido � inv�lido, provavelmente ponteiro em NULL
#define GORGON_INVALID_TRIGGER          15	//valor de trigger � inv�lido, provavelmente ponteiro em NULL
#define GORGON_INVALID_MEMORY           16	//valor de mem�ria � inv�lido, provavelmente ponteiro em NULL
#define GORGON_INVALID_ANIMATIONPACK    17	//valor de animationPack � inv�lido, provavelmente ponteiro em NULL
#define GORGON_END_ANIMATION            18	//animacao acabou
#define GORGON_ANIMATION_RUNNING        19	//animacao rodando
#define GORGON_INVALID_AUDIO		20	//vari�vel gorgonaudio invalida, provavelmente ponteiro em NULL
#define GORGON_SOUND_SYSTEM_ERROR	21	//problema com a F_MOD
#define GORGON_LOAD_SOUND_ERROR		22	//problema ao carregar o som
#define GORGON_INVALID_SOUND		23	//variavel de som inv�lida, provavelmente ponteiro em NULL
#define GORGON_INVALID_BACKGROUND	24	//valor para o background inv�lido, provavelmente ponteiro em NULL
#define GORGON_INVALID_LAYER		25	//valor para a camada do cen�rio � inv�lida, provavelmente ponteiro em NULL
#define GORGON_INVALID_LAYERPACK	26
#define GORGON_INVALID_TILE		27	//valor para um tile do cen�rio � inv�lido, provavelmente ponteiro em NULL
#define GORGON_INVALID_MEMORY_OFFSET	28
#define	GORGON_INVALID_JOY_INPUT	29

#endif
