#ifndef KINEMATICS_H
#define KINEMATICS_H

#include <QObject>
#include <vector>

class Kinematics
{
public:
    Kinematics();

public:

    void dirKinematics(const std::vector<double> &Join, const std::vector<double>& WFrame, const std::vector<double>& TFrame, const std::vector<std::vector<double>>& DH_Param, std::vector<double>& ActCoord,
             std::vector<std::vector<double>>& T5, std::vector<std::vector<double>>& TT);
    void invKinematics(const std::vector<double> &ActCoord, const std::vector<double> &NewCoord, const std::vector<std::vector<double>>& DH_Param, const std::vector<double>& WFrame,
                       const std::vector<std::vector<double>>& TT, const std::vector<double>&JoinAct, std::vector<double> &Join);

};

#endif // KINEMATICS_H
