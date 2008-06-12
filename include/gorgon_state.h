#ifndef GORGON_STATE
#define GORGON_STATE
#include "gorgon_trigger.h"
//type do gorgon state
#define changeState         'A'
#define changeAnimation     'B'
#define playSound           'C'
#define CtrlSet             'D'
#define HitDef              'E'
/*PalBright = 90,0,0
PalContrast  = 120,8,0
Explod
anim = 1202
PalMul  = .70,.20,.20
palfx.time = 30
palfx.add = 10,-20,-100
palfx.mul = 256,250,250
palfx.sinadd = 10,20,10,10
palfx.invertall = 0
palfx.color = 0
envshake.time = 10
envshake.ampl = 10
poweradd = -500
*/

typedef struct
{
    short   stateNumber;            //numero identificador do estado
    char    type;                   //changestate,changeAnim
    short   value;                  //valor do type acima
    short   control;                //0 ou 1
    short   normalDamage;           //damage quando o golpe atinge
    short   guardDamage;            //dano quando o golpe é defendido
    char    guardflag;              //flag de como o golpe pode ser defendido, S-> em pé, C->abaixado, A->no ar
    char    hitflag;                //flag de como o golpe pode ser acertado, S-> em pé, C-> abaixado, A no ar
    short   priority;               //prioridade do golpe, de 0 a 7
    short   getpower;               //quantidade de poder que ganha
    short   givepower;              //quantidade de poder que perde
    short   sparkno;                //index da animação do spark
    short   sparkX;                 //posicao X do spark relativo ao p2
    short   sparkY;                 //posicao Y do spark relativo ao p2
/*
    short   hitSoundGroup;          //grupo do som ao ser acertado
    short   hitSoundSubIndex;       //subindex do som ao ser acertado
    short   hitSoundIndex;          //index do som ao ser acertado
    short   guardSoundGroup;        //grupo do som ao ser defentido
    short   guardSoundSubIndex;     //subindex do som ao ser defendido
    short   guardSoundIndex;        //index di som ao ser defendido
*/
    short   ground_type;            //Type: High, Low, Trip (def: Normal)
    short   ground_slidetime;       //tempo que o oponente escurrega para traz
    short   ground_hittime;         //tempo que o oponente fica no estado de hit
    short   groundVelocityX;        //velocidade que o oponente é empurrado no eixo X
    short   groundVelocityY;        //velocidade que o oponente é empurrado no eixo Y
    short   air_type;               //Type: High, Low, Trip (def: same as ground.type)
    short   airguard_velocity;      // = -1.9,-.8     ;Guard velocity in air (def: (air.xvel*1.5, air.yvel/2))
    short   airVelocityX;           //velocidade que o oponente é empurrado no eixo X
    short   airVelocityY;           //velocidade que o oponente é empurrado no eixo Y
    short   air_slidetime;          //tempo que o oponente escurrega
    short   air_hittime;            //tempo até que o oponente reganhe controle no ar
    short   fall;                   //se o oponente cai com esse golpe
    short   juggle;                 //quantas vezes o golpe pode acertar o oponente se ele está no ar
    short   fall_recover;           //se pode se recuperar da queda
    short   air_recover;            //se pode ser recuperar no ar
    short   triggerNum;               //numero de triggers para esse golpe
    gorgonTrigger *trigger;
}gorgonState;

#endif
