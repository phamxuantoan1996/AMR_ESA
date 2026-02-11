#ifndef AMR_EVENTS_H
#define AMR_EVENTS_H
#include "state_types.h"

struct AMRStateChangedEvent
{
    AMRStateType from;
    AMRStateType to;
};

struct MissionStateChangedEvent
{
    MissionStateType from;
    MissionStateType to;
};

#endif
