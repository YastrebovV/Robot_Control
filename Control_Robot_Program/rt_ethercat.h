﻿#ifndef RT_ETHERCAT_H
#define RT_ETHERCAT_H

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <rtdm/rtdm.h>
#include <alchemy/task.h>
#include <alchemy/sem.h>
#include <alchemy/mutex.h>
#include <alchemy/timer.h>
#include <pthread.h>

#include "/opt/etherlab/include/ecrt.h"

class rt_ethercat
{
public:
     rt_ethercat();

private:
    static bool enable_mt_ex_Arr[6];
    static bool dir_mt_ex_Arr[6];
    static bool start_ex_Arr[6];
    static int steps_ex_Arr[6];
    static bool pul_mt_ex_Arr[6];
    static unsigned long long speed_axis_move;
    static unsigned int acc_axis_move[6];
    static unsigned int absolutePos[6];
    static bool startAxisMastering;
    static bool masteringStarted;
    static bool robotMoving;

public:
     int rt_ethercat_start();
     void rt_ethercat_stop();
     static bool getEnable_mt(unsigned int index) {return enable_mt_ex_Arr[index];}
     static void setEnable_mt(unsigned int index, bool enable_mt){enable_mt_ex_Arr[index] = enable_mt;}
     static bool getDir_mt(unsigned int index) {return dir_mt_ex_Arr[index];}
     static void setDir_mt(unsigned int index, bool dir_mt){dir_mt_ex_Arr[index] = dir_mt;}
     static bool getStart(unsigned int index) {return start_ex_Arr[index];}
     static void setStart(unsigned int index, bool startAx){start_ex_Arr[index] = startAx;}
     static int getSteps(unsigned int index) {return steps_ex_Arr[index];}
     static void setSteps(unsigned int index, int steps){steps_ex_Arr[index] = steps;}
     static bool getPul_mt(unsigned int index) {return pul_mt_ex_Arr[index];}
     static void setPul_mt(unsigned int index, bool pul_mt){pul_mt_ex_Arr[index] = pul_mt;}
     static unsigned long long getAxisSpeed() {return speed_axis_move;}
     static void setAxisSpeed(unsigned long long axisSpeed){speed_axis_move=axisSpeed;}
     static unsigned int getAccSpeed(int index) {return acc_axis_move[index];}
     static void setStartAxMastering(bool start){startAxisMastering=start;}
     static void setAccSpeed(int index, unsigned int axisAcc){acc_axis_move[index]=axisAcc;}
     static void setmasteringStarted(bool started){masteringStarted=started;}
     static bool getStartAxMastering(){return startAxisMastering;}
     static bool getmasteringStarted(){return masteringStarted;}
     static bool getRobotMoving(){return robotMoving;}
     static void setRobotMoving(bool stateMove){robotMoving = stateMove;}
};

#endif // RT_ETHERCAT_H
