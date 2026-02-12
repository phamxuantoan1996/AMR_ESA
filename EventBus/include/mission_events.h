#ifndef MISSION_EVENT_H
#define MISSION_EVENT_H
#include "state_types.h"

struct MissionStateChangedEvent
{
    MissionStateType from;
    MissionStateType to;
};

#endif