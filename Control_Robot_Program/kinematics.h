#ifndef KINEMATICS_H
#define KINEMATICS_H

#include <QObject>

class Kinematics
{
public:
    Kinematics();

public:
    void dirKinematics(double angles[6], double WFrame[6], double TFrame[6], double DH_Param[6][3], struct ActCoord *fkv, double **T5,double **TT);
    void invKinematics(struct ActCoord ActCoord, struct ActCoord NewCoord, double DH_Param[6][3], double WFrame[6], double TT[4][4], double anglesAct[6], struct Join *Join);
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
};

#endif // KINEMATICS_H
