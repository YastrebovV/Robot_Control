#include "robotcontrol.h"

using namespace std;

RobotControl::RobotControl()
{
   //при создании класса загрузить данные из конфигурационного файла
      pos_error.resize(6);
      AxisAnglIncr.resize(6);
      pos_err_temp.resize(6);
      ActCoord.resize(8);

      Reduction.resize(6);
      Reduction[0] = 30.0;
      Reduction[1] = 50.0;
      Reduction[2] = 30.0;
      Reduction[3] = 5.18*1.11;
      Reduction[4] = 5.18*(1.24*1.69*2.5);
      Reduction[5] = (5.18/2.111111111)*(1.69*2.5);

      Join.resize(6);
      Join[0]= 0.000001;
      Join[1] = -90;
      Join[2] = 90;
      Join[3] = 0.000001;
      Join[4] = 5.001;
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
    bool dir[6];

    for (unsigned int i = 0; i < 6; i++){

        AxisAnglIncr[i] = static_cast<int>(abs((Join[i] - NewJoin[i]) / (0.45/ Reduction[i])));

        pos_err_temp[i] = abs((Join[i] - NewJoin[i]) / (0.45 / Reduction[i])) - trunc(abs((Join[i] - NewJoin[i]) / (0.45 / Reduction[i])));
        pos_error[i] += pos_err_temp[i];

        if (pos_error[i] > 1)
        {
            AxisAnglIncr[i] += 1;
            pos_error[i] -= 1; ;
        }
        if ((Join[i] - NewJoin[i]) > 0)
        {
            dir[i] = 1;
        }else{
            dir[i] = 0;
        }

    }

    for (unsigned int i = 0; i < 6; i++)
    {
        ethercatRT->setSteps(i, AxisAnglIncr[i]);
        ethercatRT->setDir_mt(i, dir[i]);
        ethercatRT->setStart(i, true);
    }
}

void RobotControl::RobotStop()
{
    double temp;
    for (unsigned int i = 0; i < 6; i++)
    {
        ethercatRT->setStart(i, false);

        if(ethercatRT->getSteps(i)!=0){
            temp = static_cast<double>(AxisAnglIncr[i] - ethercatRT->getSteps(i)) * (0.45 / Reduction[i]);
            pos_error[i] -= pos_err_temp[i];
        }else{
            temp = static_cast<double>(AxisAnglIncr[i]) * (0.45 / Reduction[i]);
        }
        if(ethercatRT->getDir_mt(i) > 0){
            RobotControl::setJoin(i,RobotControl::getAngelAct(i) - temp);
        }else{
            RobotControl::setJoin(i,RobotControl::getAngelAct(i) + temp);
        }
    }

        std::vector<double> Join = getAngelAct();
        Join[2] = Join[2] -90;
        Join[5] = Join[5] +180;
        Kinematics_C.dirKinematics(Join, WFrame, TFrame, DH_Param, ActCoord, T5, TT);
        setActCoord(ActCoord);
}
