#include "robotcontrol.h"

using namespace std;

RobotControl::RobotControl()
{
   //при создании класса загрузить данные из конфигурационного файла
      AngelAct[0] = 0;
      AngelAct[1] = 0;
      AngelAct[2] = 0;
      AngelAct[3] = 0;
      AngelAct[4] = 0;
      AngelAct[5] = 0;

      WFrame[0] = 0;
      WFrame[1] = 0;
      WFrame[2] = 0;
      WFrame[3] = 0;
      WFrame[4] = 0;
      WFrame[5] = 0;

      TFrame[0] = 0;
      TFrame[1] = 0;
      TFrame[2] = 0;
      TFrame[3] = 0;
      TFrame[4] = 0;
      TFrame[5] = 0;

      DH_Param[0][0] = -90;//alpha
      DH_Param[1][0] = 0;
      DH_Param[2][0] = 90;
      DH_Param[3][0] = -90;
      DH_Param[4][0] = 90;
      DH_Param[5][0] = 0;//
      DH_Param[0][1] = 253.69;//d
      DH_Param[1][1] = 0;
      DH_Param[2][1] = 0;
      DH_Param[3][1] = -287.95;
      DH_Param[4][1] = 0;
      DH_Param[5][1] = -56;//
      DH_Param[0][2] = 109.36;//a
      DH_Param[1][2] = 235;
      DH_Param[2][2] = 79.95;
      DH_Param[3][2] = 0;
      DH_Param[4][2] = 0;
      DH_Param[5][2] = 0;//
}

void RobotControl::JointMove(vector<double>& AxisAnglAct, const vector<double>& AxisAnglNew)  //осевое перемещение робота
{
    int AxisAnglIncr[6];
    int dir[6];

    AxisAnglIncr[0] = int(abs((AxisAnglAct[0] - AxisAnglNew[0]) / (1.8/ reductionA1)));

    pos_error[0] += abs((AxisAnglAct[0] - AxisAnglNew[0]) / (1.8 / reductionA1)) - trunc(abs((AxisAnglAct[0] -
        AxisAnglNew[0]) / (1.8 / reductionA1)));

    if (pos_error[0] > 1)
    {
        AxisAnglIncr[0] += 1;
        pos_error[0] = pos_error[0] - 1; ;
    }
    if ((AxisAnglAct[0] - AxisAnglNew[0]) > 0)
     {
        dir[0] = 1;
     }
     else dir[0] = 0;

    AxisAnglIncr[1] = int(abs((AxisAnglAct[1] - AxisAnglNew[1]) / (1.8 / reductionA2)));
    pos_error[1] += abs((AxisAnglAct[1] - AxisAnglNew[1]) / (1.8 / reductionA2)) - trunc(abs((AxisAnglAct[1] -
       AxisAnglNew[1]) / (1.8 / reductionA2)));
    if (pos_error[1] > 1)
    {
        AxisAnglIncr[1] += 1;
        pos_error[1] = pos_error[1]-1;
    }

    if ((AxisAnglAct[1] - AxisAnglNew[1]) > 0)
    {
        dir[1] = 1;
    }
    else dir[1] = 0;

    AxisAnglIncr[2] = int(abs((AxisAnglAct[2] - AxisAnglNew[2]) / (1.8 / reductionA3)));
    pos_error[2] += abs((AxisAnglAct[2] - AxisAnglNew[2]) / (1.8 / reductionA3)) - trunc(abs((AxisAnglAct[2] -
        AxisAnglNew[2]) / (1.8 / reductionA3)));
    if (pos_error[2] > 1)
    {
        AxisAnglIncr[2] += 1;
        pos_error[2] = pos_error[2] - 1;
    }

    if ((AxisAnglAct[2] - AxisAnglNew[2]) > 0)
    {
        dir[2] = 1;
    }
    else dir[2] = 0;

    AxisAnglIncr[3] = int(abs((AxisAnglAct[3] - AxisAnglNew[3]) / (1.8 / reductionA4)));
    pos_error[3] += abs((AxisAnglAct[3] - AxisAnglNew[3]) / (1.8 / reductionA4)) - trunc(abs((AxisAnglAct[3] -
       AxisAnglNew[3]) / (1.8 / reductionA4)));
    if (pos_error[3] > 1)
    {
        AxisAnglIncr[3] += 1;
        pos_error[3] = pos_error[3] - 1;
    }

    if ((AxisAnglAct[3] - AxisAnglNew[3]) > 0)
    {
        dir[3] = 1;
    }
    else dir[3] = 0;

    AxisAnglIncr[4] = int(abs((AxisAnglAct[4] - AxisAnglNew[4]) / (1.8 / reductionA5)));
    pos_error[4] += abs((AxisAnglAct[4] - AxisAnglNew[4]) / (1.8 / reductionA5)) - trunc(abs((AxisAnglAct[4] -
        AxisAnglNew[4]) / (1.8 / reductionA5)));
    if (pos_error[4] > 1)
    {
        AxisAnglIncr[4] += 1;
        pos_error[4] = pos_error[4] - 1;
    }

    if ((AxisAnglAct[4] - AxisAnglNew[4]) > 0)
    {
        dir[4] = 1;
    }
    else dir[4] = 0;

    AxisAnglIncr[5] = int(abs((AxisAnglAct[5] - AxisAnglNew[5]) / (1.8 / reductionA6)));
    pos_error[5] += abs((AxisAnglAct[5] - AxisAnglNew[5]) / (1.8 / reductionA6)) - trunc(abs((AxisAnglAct[5] -
         AxisAnglNew[5]) / (1.8 / reductionA6)));
    if (pos_error[5] > 1)
    {
        AxisAnglIncr[5] += 1;
        pos_error[5] = pos_error[5] - 1;
    }

    if ((AxisAnglAct[5] - AxisAnglNew[5]) > 0)
    {
        dir[5] = 1;
    }
    else dir[5] = 0;

    for (int i = 0; i < 6; i++)
    {
     //   Send(Convert.ToString(i + 1) + "," + dir + "," + Convert.ToString(AxisAnglIncr[i]) + "," + Convert.ToString(AxisSpeed[i]) + "^");
    }
    //Send("*");
}
