#include "../include/gorgon_trigger.h"

int gorgonCreateTrigger(gorgonTrigger *trigger,short number)
{
    if(trigger!=NULL)
    {
        trigger->type=(gorgonTriggerType *)calloc(number,sizeof(gorgonTriggerType));
        trigger->value=(short *)calloc(number,sizeof(short));
        trigger->value2=(short *)calloc(number,sizeof(short));
        trigger->op=(char *)calloc(number,sizeof(char));
        trigger->triggerNum=number;
        if(trigger->type==NULL || trigger->value==NULL || trigger->value2 || trigger->op==NULL)
        return GORGON_OK;
    }
    return GORGON_INVALID_TRIGGER;
}

