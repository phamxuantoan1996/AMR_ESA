#ifndef AMR_EVENTS_H
#define AMR_EVENTS_H

#include "state_amr.h"

struct AMRStateChangedEvent
{
    AMRStateType from;
    AMRStateType to;
};

#endif
