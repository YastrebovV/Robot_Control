#ifndef ROBOTCONTROL_H
#define ROBOTCONTROL_H

#include <QObject>
#include <QDebug>
#include "kinematics.h"
#include <vector>
#include "rt_ethercat.h"

class RobotControl
{
public:
    RobotControl();

public:
    void RobotStop();
    void jointManMove(const int & numAxis, const double & valueOffset);
    void cartesianManMove(const int & axis, const double & valueOffset);
    void executionProgram(const std::vector<double> & dataProgramLine);
    std::vector<double> getAngelAct() { return Join; }
    double getAngelAct(unsigned int index) { return Join[index]; }
    std::vector<double> getWFrame() { return WFrame; }
    std::vector<double> getTFrame() { return TFrame; }
    std::vector<std::vector<double>> getDH_Param() { return DH_Param; }
    std::vector<std::vector<double>> getT5() { return T5; }
    std::vector<std::vector<double>> getTT() { return TT; }
    std::vector<double> getActCoord() {return ActCoord;}
    void setActCoord(std::vector<double> actCoord) { ActCoord = actCoord; }
    void setJoin(std::vector<double> NewJoin) {Join=NewJoin;}
    void setJoin(unsigned int index, double angel){Join[index] = angel;}    

private:
    void JointMove(const std::vector<double> & Join, const std::vector<double> & NewJoin);
    std::vector<double> pos_error;
    std::vector<double> pos_err_temp;
    std::vector<int> AxisAnglIncr;
    Kinematics kin;
    std::vector<double> Reduction;
    std::vector<double> ActCoord;
    std::vector<double> NewCoord;
    std::vector<double> Join;
    std::vector<double> WFrame;
    std::vector<double> TFrame;
    std::vector<std::vector<double>> DH_Param;//[3][6];
    std::vector<std::vector<double>> TT;//[4][4];
    std::vector<std::vector<double>> T5;//[4][4];
    rt_ethercat *ethercatRT;
    Kinematics Kinematics_C;

};

#endif // ROBOTCONTROL_H
