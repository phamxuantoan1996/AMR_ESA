# AMR_ESA
For SRC controller

+------------------+
|   Communication  |  (ROS / HTTP / MQTT)
+---------+--------+
          |
          v
+------------------+
|  AMR_Controller  |
|------------------|
| - AMRState       |
| - Mission*       |
|------------------|
| onJobReceived()  |
| tick()           |
| onMissionEvent() |
+---------+--------+
          |
          v
+------------------+
|     Mission      |
|------------------|
| MissionState     |
| JobExecutor      |
+------------------+
