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
    static int speed_axis_move[6];
    static int acc_axis_move[6];
    static int absolutePos[6];

public:
     int rt_ethercat_start();
     void rt_ethercat_stop();
     static bool getEnable_mt(int index) {return enable_mt_ex_Arr[index];}
     static void setEnable_mt(int index, bool enable_mt){enable_mt_ex_Arr[index] = enable_mt;}
     static bool getDir_mt(int index) {return dir_mt_ex_Arr[index];}
     static void setDir_mt(int index, bool dir_mt){dir_mt_ex_Arr[index] = dir_mt;}
     static bool getStart(int index) {return start_ex_Arr[index];}
     static void setStart(int index, bool startAx){start_ex_Arr[index] = startAx;}
     static int getSteps(int index) {return steps_ex_Arr[index];}
     static void setSteps(int index, int steps){steps_ex_Arr[index] = steps;}
     static bool getPul_mt(int index) {return pul_mt_ex_Arr[index];}
     static void setPul_mt(int index, bool pul_mt){pul_mt_ex_Arr[index] = pul_mt;}
     static int getAxisSpeed(int index) {return speed_axis_move[index];}
     static void setAxisSpeed(int index, int axisSpeed){speed_axis_move[index]=axisSpeed;}
     static int getAccSpeed(int index) {return acc_axis_move[index];}
     static void setAccSpeed(int index, int axisAcc){acc_axis_move[index]=axisAcc;}

};

#endif // RT_ETHERCAT_H