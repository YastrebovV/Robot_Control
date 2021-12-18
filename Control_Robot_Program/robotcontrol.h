#ifndef ROBOTCONTROL_H
#define ROBOTCONTROL_H

#include <QObject>
#include "kinematics.h"

class RobotControl
{
public:
    RobotControl();

public:
    void JointMove(double AxisAnglAct[6],double AxisAnglNew[6], double AxisSpeed[6]);
    int getCountAx1() { return countAx1; } // геттер для countAx1
    void setCountAx1(int countAx) { countAx1 = countAx; } // сеттер для countAx1
private:
    double reductionA1 = 30.0;
    double reductionA2 = 50.0;
    double reductionA3 = 30.0;
    double reductionA4 = 5.18;
    double reductionA5 = 5.18;
    double reductionA6 = 5.18;
    double pos_error[6];
    Kinematics kin;
    Kinematics::ActCoord ActCoord;
    Kinematics::ActCoord NewCoord;
    Kinematics::Join Join;
    double AngelAct[6];
    double WFrame[6];
    double TFrame[6];
    double DH_Param[6][3];
    double TT [4][4];
    double T5[4][4];
    int countAx1 = 12;

};

#endif // ROBOTCONTROL_H
