#ifndef KINEMATICS_H
#define KINEMATICS_H

#include <QObject>
#include <vector>

class Kinematics
{
public:
    Kinematics();

public:
    struct ActCoord
     {
        double x;
        double y;
        double z;
        double yaw;//R-Z
        double pitch;//R-Y
        double roll;//R-Z
        int QU_J1;
        int QU_J5;
     };
     struct Join
     {
         double J1;
         double J2;
         double J3;
         double J4;
         double J5;
         double J6;
     };

    void dirKinematics(const std::vector<double>& angles, const std::vector<double>& WFrame, const std::vector<double>& TFrame, const std::vector<std::vector<double>>& DH_Param, struct ActCoord& fkv,
             std::vector<std::vector<double>>& T5, std::vector<std::vector<double>>& TT);
    void invKinematics(const struct ActCoord &ActCoord, const struct ActCoord &NewCoord, const std::vector<std::vector<double>>& DH_Param, const std::vector<double>& WFrame,
                       const std::vector<std::vector<double>>& TT, const std::vector<double>& anglesAct, struct Join &Join);


};

#endif // KINEMATICS_H
