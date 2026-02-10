# AMR_ESA
For SRC controller

                    ┌──────────────┐
                    │     WMS      │
                    │ (External)   │
                    └──────┬───────┘
                           │ Command / Cancel / Pause / Resume
                           ▼
┌──────────────────────────────────────────────────────────┐
│                    AMR_Controller                        │
│──────────────────────────────────────────────────────────│
│ - AMRStateMachine                                        │
│ - MissionManager                                         │
│ - subscribe(EventBus)                                    │
│ - publish(EventBus)                                      │
│                                                          │
│ + sendCommand(cmd)                                       │
│ + cancelMission()                                        │
│ + pauseMission()                                         │
│ + resumeMission()                                        │
└──────┬───────────────────────┬──────────────────────────┘
       │                       │
       │ owns                  │ subscribes
       ▼                       ▼
┌──────────────┐        ┌──────────────┐
│  Mission     │        │   EventBus   │
│──────────────│        │──────────────│
│ MissionState │◄───────┤ publish()    │
│ Executor     │        │ subscribe()  │
└──────┬───────┘        └──────┬───────┘
       │ executes               │
       ▼                        │
┌──────────────┐                │
│ JobStep      │◄───────────────┘
│──────────────│   Event
│ + execute()  │
└──────┬───────┘
       │ uses
       ▼
┌──────────────────┐
│  RobotFacade     │
│──────────────────│
│ + moveTo()       │
│ + forkliftUp()   │
│ + forkliftDown() │
│ + readStatus()   │
└──────┬───────────┘
       │ updates
       ▼
┌──────────────────┐
│   AMRStatus      │
│──────────────────│
│ battery          │
│ pose             │
│ health           │
│ error_code       │
└──────────────────┘
