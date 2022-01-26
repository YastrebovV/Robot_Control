#include "robotcontrol.h"

using namespace std;

RobotControl::RobotControl()
{
   //при создании класса загрузить данные из конфигурационного файла

      Join.resize(6);
      Join[0]= 0.000001;
      Join[1] = -90;
      Join[2] = 90;
      Join[3] = 0.000001;
      Join[4] = 0.001;
      Join[5] = 0.000001;

      WFrame.resize(6);
      WFrame[0] = 0;
      WFrame[1] = 0;
      WFrame[2] = 0;
      WFrame[3] = 0;
      WFrame[4] = 0;
      WFrame[5] = 0;

      TFrame.resize(6);
      TFrame[0] = 0;
      TFrame[1] = 0;
      TFrame[2] = 0;
      TFrame[3] = 0;
      TFrame[4] = 0;
      TFrame[5] = 0;

      DH_Param.resize(3);
      for(unsigned int i=0; i<3; i++)
         DH_Param[i].resize(6);

      DH_Param[0][0] = -90;//alpha
      DH_Param[0][1] = 0;
      DH_Param[0][2] = 90;
      DH_Param[0][3] = -90;
      DH_Param[0][4] = 90;
      DH_Param[0][5] = 0;//
      DH_Param[1][0] = 253.69;//d
      DH_Param[1][1] = 0;
      DH_Param[1][2] = 0;
      DH_Param[1][3] = -287.95;
      DH_Param[1][4] = 0;
      DH_Param[1][5] = -56;//
      DH_Param[2][0] = 109.36;//a
      DH_Param[2][1] = 235;
      DH_Param[2][2] = 79.95;
      DH_Param[2][3] = 0;
      DH_Param[2][4] = 0;
      DH_Param[2][5] = 0;//
//      DH_Param[0][0] = -90;//alpha
//      DH_Param[0][1] = 0;
//      DH_Param[0][2] = 90;
//      DH_Param[0][3] = -90;
//      DH_Param[0][4] = 90;
//      DH_Param[0][5] = 0;//
//      DH_Param[1][0] = 169.77;//d
//      DH_Param[1][1] = 0;
//      DH_Param[1][2] = 0;
//      DH_Param[1][3] = -222.63;
//      DH_Param[1][4] = 0;
//      DH_Param[1][5] = -36.25;//
//      DH_Param[2][0] = 64.2;//a
//      DH_Param[2][1] = 305;
//      DH_Param[2][2] = 0;
//      DH_Param[2][3] = 0;
//      DH_Param[2][4] = 0;
//      DH_Param[2][5] = 0;//

      T5.resize(4);
      for(unsigned int i=0; i<4; i++)
         T5[i].resize(4);
      TT.resize(4);
      for(unsigned int i=0; i<4; i++)
         TT[i].resize(4);
}

void RobotControl::JointMove(std::vector<double> Join, std::vector<double> NewJoin)  //осевое перемещение робота
{
    int AxisAnglIncr[6];
    bool dir[6];

    AxisAnglIncr[0] = int(abs((Join[0] - NewJoin[0]) / (1.8/ reductionA1)));

    pos_error[0] += abs((Join[0] - NewJoin[0]) / (1.8 / reductionA1)) - trunc(abs((Join[0] -
        NewJoin[0]) / (1.8 / reductionA1)));

    if (pos_error[0] > 1)
    {
        AxisAnglIncr[0] += 1;
        pos_error[0] = pos_error[0] - 1; ;
    }
    if ((Join[0] - NewJoin[0]) > 0)
     {
        dir[0] = 1;
     }
     else dir[0] = 0;

    AxisAnglIncr[1] = int(abs((Join[1] - NewJoin[1]) / (1.8 / reductionA2)));
    pos_error[1] += abs((Join[1] - NewJoin[1]) / (1.8 / reductionA2)) - trunc(abs((Join[1] -
       NewJoin[1]) / (1.8 / reductionA2)));
    if (pos_error[1] > 1)
    {
        AxisAnglIncr[1] += 1;
        pos_error[1] = pos_error[1]-1;
    }

    if ((Join[1] - NewJoin[1]) > 0)
    {
        dir[1] = 1;
    }
    else dir[1] = 0;

    AxisAnglIncr[2] = int(abs((Join[2] - NewJoin[2]) / (1.8 / reductionA3)));
    pos_error[2] += abs((Join[2] - NewJoin[2]) / (1.8 / reductionA3)) - trunc(abs((Join[2] -
        NewJoin[2]) / (1.8 / reductionA3)));
    if (pos_error[2] > 1)
    {
        AxisAnglIncr[2] += 1;
        pos_error[2] = pos_error[2] - 1;
    }

    if ((Join[2] - NewJoin[2]) > 0)
    {
        dir[2] = 1;
    }
    else dir[2] = 0;

    AxisAnglIncr[3] = int(abs((Join[3] - NewJoin[3]) / (1.8 / reductionA4)));
    pos_error[3] += abs((Join[3] - NewJoin[3]) / (1.8 / reductionA4)) - trunc(abs((Join[3] -
       NewJoin[3]) / (1.8 / reductionA4)));
    if (pos_error[3] > 1)
    {
        AxisAnglIncr[3] += 1;
        pos_error[3] = pos_error[3] - 1;
    }

    if ((Join[3] - NewJoin[3]) > 0)
    {
        dir[3] = 1;
    }
    else dir[3] = 0;

    AxisAnglIncr[4] = int(abs((Join[4] - NewJoin[4]) / (1.8 / reductionA5)));
    pos_error[4] += abs((Join[4] - NewJoin[4]) / (1.8 / reductionA5)) - trunc(abs((Join[4] -
        NewJoin[4]) / (1.8 / reductionA5)));
    if (pos_error[4] > 1)
    {
        AxisAnglIncr[4] += 1;
        pos_error[4] = pos_error[4] - 1;
    }

    if ((Join[4] - NewJoin[4]) > 0)
    {
        dir[4] = 1;
    }
    else dir[4] = 0;

    AxisAnglIncr[5] = int(abs((Join[5] - NewJoin[5]) / (1.8 / reductionA6)));
    pos_error[5] += abs((Join[5] - NewJoin[5]) / (1.8 / reductionA6)) - trunc(abs((Join[5] -
         NewJoin[5]) / (1.8 / reductionA6)));
    if (pos_error[5] > 1)
    {
        AxisAnglIncr[5] += 1;
        pos_error[5] = pos_error[5] - 1;
    }

    if ((Join[5] - NewJoin[5]) > 0)
    {
        dir[5] = 1;
    }
    else dir[5] = 0;

    for (int i = 0; i < 6; i++)
    {
        ethercatRT->setSteps(i+1, AxisAnglIncr[i]);
        ethercatRT->setDir_mt(i+1, dir[i]);
        ethercatRT->setStart(i+1, true);
    }
}

void RobotControl::RobotStoped()
{
    for (int i = 0; i < 6; i++)
    {
        ethercatRT->setStart(i+1, false);
    }
}
