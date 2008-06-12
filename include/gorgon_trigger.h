#ifndef GORGON_TRIGGER
#define GORGON_TRIGGER
#include<allegro.h>
#include "gorgon_error.h"

//type do trigger
#define hitBy       0
#define life        1
#define time        2
#define animTime    3
#define stateNo     4
#define command     5
#define anim        6
#define HitCount    7
#define AnimElemNo  8
#define velX        9
#define velY        10
#define colideRight 11
#define colideLeft  12
#define colideDown  13
#define colideUp    14
/*
P2statetype = A
P2statetype = S
animElem = 9
Ctrl
Facing Returns 1 if the player is facing to the right, and -1 if the player is facing to the left.

FrontEdgeBodyDist gives the distance between the front of the player (as determined by the front edge of his width bar) and the edge of the screen.
FrontEdgeDist gives the distance between the x-axis of the player and the edge of the screen in front of the player.


Floor
HitOver
IsHelper
Life
LifeMax
MoveType
NumEnemy
NumExplod
NumHelper
NumPartner
P2BodyDist
P2Dist
P2Life
P2MoveType
P2StateNo
P2StateType
Power
PowerMax
NumProj
  - NumProjID
ProjContact(*,***)
ProjContactTime
ProjGuarded
ProjGuardedTime
ProjHit
ProjHitTime
ScreenPos
StateNo
StateType
*/
typedef short gorgonTriggerType;
typedef struct
{
    gorgonTriggerType *type;
    short *value;
    short *value2;
    char *op;
    short triggerNum;
}gorgonTrigger;

#endif
/*
typedef struct{
    short life;//: Returns value of the "life" parameter. (int)
    short attack;//: Returns value of the "attack" parameter. (int)
    short defence;//: Returns value of the "defence" parameter. (int)    short fall_defence_mul;//: Returns value of the defence multiplier,                        //calculated as 100/(f+100), where f is the "fall.defence_up"                        //parameter. (float)
    short liedown_time;//: Returns value of the "liedown.time" parameter.  (int)
    short airjuggle;//: Returns value of the "airjuggle" parameter. (int)
    short sparkno;//: Returns value of the "sparkno" parameter. (int)
    short guard_sparkno;//: Returns value of the "guard.sparkno" parameter.	     (int)

    float size_xscale;//: Returns value of the "xscale" parameter. (float)
    float size_yscale;//: Returns value of the "yscale" parameter. (float)
    short size_ground_back;//: Returns value of the "ground.back" parameter. (int)
    short size_ground_front;//: Returns value of the "ground.front" parameter.(int)
    short size.air.back;//: Returns value of the "air.back" parameter. (int)
    short size.air.front;//: Returns value of the "air.front" parameter. (int)
    short size.height;//: Returns value of the "height" parameter. (int)
    short size.attack.dist;//: Returns value of the "attack.dist" parameter. (int)
    short size.proj.attack.dist;//: Returns value of the "proj.attack.dist"    parameter. (int)
    short size.proj.doscale;//: Returns value of the "proj.doscale" parameter.           (int)
    short size.head.pos.x;//: Returns x-component of the "head.pos" parameter.           (int)
    short size.head.pos.y;//: Returns y-component of the "head.pos" parameter.           (int)
    short size.mid.pos.x;//: Returns x-component of the "mid.pos" parameter.           (int)
    short size.mid.pos.y;//: Returns y-component of the "mid.pos" parameter.           (int)
    short size.shadowoffset;//: Returns value of the "shadowoffset" parameter.           (int)
    short size.draw.offset.x;//: Returns x-component of the "draw.offset"           parameter. (int)
    short size.draw.offset.y;//: Returns y-component of the "draw.offset"           parameter. (int)

  //The following values of param_name return values specified in the
  //[Velocity] group in the player's constants.

    float velocity.walk.fwd.x;//: Returns value of the "walk.fwd" parameter.           (float)
    float velocity.walk.back.x;//: Returns value of the "walk.back" parameter.           (float)
    float velocity.run.fwd.x;//: Returns x-component of the "run.fwd" parameter.           (float)
    float velocity.run.fwd.y;//: Returns y-component of the "run.fwd" parameter.           (float)
    float velocity.run.back.x;//: Returns x-component of the "run.back" parameter.           (float)
    float velocity.run.back.y;//: Returns y-component of the "run.back" parameter.           (float)
    float velocity.jump.y;//: Returns y-component of the "jump.neu" parameter.
           //Note: this is NOT "velocity.jump.neu.y". Only the "neu"
           //parameters take a y-component value. (float)
    float velocity.jump.neu.x;//: Returns x-component of the "jump.neu" parameter.           (float)
    float velocity.jump.back.x;//: Returns value of the "jump.back" paramamter.             (float)
    float velocity.jump.fwd.x;//: Returns value of the "jump.fwd" parameter.           (float)
    float velocity.runjump.back.x;//: Returns value of the "runjump.back"           paramamter. (float)
    float velocity.runjump.fwd.x;//: Returns value of the "runjump.fwd" parameter.           (float)
    float velocity.airjump.y;//: Returns y-component of the "airjump.neu"  parameter. Note: this is NOT "velocity.airjump.neu.y".   (float)
    float velocity.airjump.neu.x;//: Returns x-component of the "airjump.neu"           parameter. (float)
    float velocity.airjump.back.x;//: Returns value of the "airjump.back"           paramamter. (float)
    float velocity.airjump.fwd.x;//: Returns value of the "airjump.fwd" parameter.           (float)
            //The following values of param_name return values specified in the
            //[Movement] group in the player's constants.
    short movement.airjump.num;//: Returns value of the "airjump.num" parameter.(int)
    short movement.airjump.height;//: Returns value of the "airjump.height" parameter. (int)
    float movement.yaccel;//: Returns value of the "yaccel" parameter. (float)
    float movement.stand.friction;//: Returns value of the "stand.friction"           parameter. (float)
    float movement.crouch.friction;//: Returns value of the "crouch.friction"
*/
