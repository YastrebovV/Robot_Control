#ifndef ROBOTCONTROL_H
#define ROBOTCONTROL_H

#include <QObject>
#include "kinematics.h"
#include <vector>

class RobotControl
{
public:
    RobotControl();

public:
    void JointMove(std::vector<double>& AxisAnglAct, const std::vector<double>& AxisAnglNew);
    int getCountAx1() { return countAx1; } // геттер для countAx1
    void setCountAx1(int countAx) { countAx1 = countAx; } // сеттер для countAx1
    std::vector<double> getAngelAct() { return AngelAct; }
    std::vector<double> getWFrame() { return WFrame; }
    std::vector<double> getTFrame() { return TFrame; }
    std::vector<std::vector<double>> getDH_Param() { return DH_Param; }
    std::vector<std::vector<double>> getT5() { return T5; }
    std::vector<std::vector<double>> getTT() { return TT; }
    Kinematics::ActCoord getActCoord() {return ActCoord;}
    void setActCoord(Kinematics::ActCoord actCoord) { ActCoord = actCoord; }

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
    std::vector<double> AngelAct;
    std::vector<double> WFrame;
    std::vector<double> TFrame;
    std::vector<std::vector<double>> DH_Param;//[3][6];
    std::vector<std::vector<double>> TT;//[4][4];
    std::vector<std::vector<double>> T5;//[4][4];
    int countAx1 = 12;

};

#endif // ROBOTCONTROL_H
