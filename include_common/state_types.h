#ifndef STATE_TYPES_H
#define STATE_TYPES_H
enum class MissionStateType
{
    Create,
    ExecuteJob,
    Pause,
    Complete,
    Fail,
};

enum class AMRStateType{
    IDLE,
    BUSY,
    ERROR
};
#endif