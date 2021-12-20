#include "kinematics.h"

using namespace std;

Kinematics::Kinematics()
{

}

 double angTorad(double angl)
 {
     double radian = angl * M_PI / 180;
     return radian;
 }
 double radToang(double rad)
 {
     double ang = rad * 180 / M_PI;
     return ang;
 }

 void Kinematics::dirKinematics(const vector<double>& angles, const vector<double>& WFrame, const vector<double>& TFrame, const vector<std::vector<double>>& DH_Param, struct ActCoord& fkv,
          vector<vector<double>>& T5, vector<vector<double>>& TT)
 {

     double WFM[4][4];
     double TFM[4][4];
     double J1[4][4];
     double J2[4][4];
     double J3[4][4];
     double J4[4][4];
     double J5[4][4];
     double J6[4][4];

     double T1[4][4];
     double T2[4][4];
     double T3[4][4];
     double T4[4][4];
     //T5[4][4];
     double T6[4][4];
     //TT[4][4];

     //WORLD FRAME MATRIX
     WFM[0][0] = cos(angTorad(WFrame[5])) * cos(angTorad(WFrame[4]));
     WFM[1][0] = sin(angTorad(WFrame[5])) * cos(angTorad(WFrame[4]));
     WFM[2][0] = -sin(angTorad(WFrame[5]));
     WFM[3][0] = 0;
     WFM[0][1] = -sin(angTorad(WFrame[5])) * cos(angTorad(WFrame[3])) + cos(angTorad(WFrame[5])) * sin(angTorad(WFrame[4])) * sin(angTorad(WFrame[3]));
     WFM[1][1] = cos(angTorad(WFrame[5])) * cos(angTorad(WFrame[3])) + sin(angTorad(WFrame[5])) * sin(angTorad(WFrame[4])) * sin(angTorad(WFrame[3]));
     WFM[2][1] = cos(angTorad(WFrame[4])) * sin(angTorad(WFrame[3]));
     WFM[3][1] = 0;
     WFM[0][2] = sin(angTorad(WFrame[5])) * sin(angTorad(WFrame[3])) + cos(angTorad(WFrame[5])) * sin(angTorad(WFrame[4])) * cos(angTorad(WFrame[3]));
     WFM[1][2] = -cos(angTorad(WFrame[5])) * sin(angTorad(WFrame[3])) + sin(angTorad(WFrame[5])) * cos(angTorad(WFrame[4])) * sin(angTorad(WFrame[3]));
     WFM[2][2] = cos(angTorad(WFrame[4])) * cos(angTorad(WFrame[3]));
     WFM[3][2] = 0;
     WFM[0][3] = WFrame[0];
     WFM[1][3] = WFrame[1];
     WFM[2][3] = WFrame[2];
     WFM[3][3] = 1;

     //JOIN 1 MATRIX 
     J1[0][0] = cos(angTorad(angles[0]));
     J1[1][0] = sin(angTorad(angles[0]));
     J1[2][0] = 0;
     J1[3][0] = 0;
     J1[0][1] = -sin(angTorad(angles[0])) * cos(angTorad(DH_Param[0][0]));
     J1[1][1] = cos(angTorad(angles[0])) * cos(angTorad(DH_Param[0][0]));
     J1[2][1] = sin(angTorad(DH_Param[0][0]));
     J1[3][1] = 0;
     J1[0][2] = sin(angTorad(angles[0])) * sin(angTorad(DH_Param[0][0]));
     J1[1][2] = -cos(angTorad(angles[0])) * sin(angTorad(DH_Param[0][0]));
     J1[2][2] = cos(angTorad(DH_Param[0][0]));
     J1[3][2] = 0;
     J1[0][3] = DH_Param[0][2] * cos(angTorad(angles[0]));
     J1[1][3] = DH_Param[0][2] * sin(angTorad(angles[0])); ;
     J1[2][3] = DH_Param[0][1];
     J1[3][3] = 1;

     //JOIN 2 MATRIX 
     J2[0][0] = cos(angTorad(angles[1]));
     J2[1][0] = sin(angTorad(angles[1]));
     J2[2][0] = 0;
     J2[3][0] = 0;
     J2[0][1] = -sin(angTorad(angles[1])) * cos(angTorad(DH_Param[1][0]));
     J2[1][1] = cos(angTorad(angles[1])) * cos(angTorad(DH_Param[1][0]));
     J2[2][1] = sin(angTorad(DH_Param[1][0]));
     J2[3][1] = 0;
     J2[0][2] = sin(angTorad(angles[1])) * sin(angTorad(DH_Param[1][0]));
     J2[1][2] = -cos(angTorad(angles[1])) * sin(angTorad(DH_Param[1][0]));
     J2[2][2] = cos(angTorad(DH_Param[1][0]));
     J2[3][2] = 0;
     J2[0][3] = DH_Param[1][2] * cos(angTorad(angles[1]));
     J2[1][3] = DH_Param[1][2] * sin(angTorad(angles[1])); ;
     J2[2][3] = DH_Param[1][1];
     J2[3][3] = 1;

     //JOIN 3 MATRIX 
     J3[0][0] = cos(angTorad(angles[2]));
     J3[1][0] = sin(angTorad(angles[2]));
     J3[2][0] = 0;
     J3[3][0] = 0;
     J3[0][1] = -sin(angTorad(angles[2])) * cos(angTorad(DH_Param[2][0]));
     J3[1][1] = cos(angTorad(angles[2])) * cos(angTorad(DH_Param[2][0]));
     J3[2][1] = sin(angTorad(DH_Param[2][0]));
     J3[3][1] = 0;
     J3[0][2] = sin(angTorad(angles[2])) * sin(angTorad(DH_Param[2][0]));
     J3[1][2] = -cos(angTorad(angles[2])) * sin(angTorad(DH_Param[2][0]));
     J3[2][2] = cos(angTorad(DH_Param[2][0]));
     J3[3][2] = 0;
     J3[0][3] = DH_Param[2][2] * cos(angTorad(angles[2]));
     J3[1][3] = DH_Param[2][2] * sin(angTorad(angles[2])); ;
     J3[2][3] = 0;
     J3[3][3] = 1;


     //JOIN 4 MATRIX 
     J4[0][0] = cos(angTorad(angles[3]));
     J4[1][0] = sin(angTorad(angles[3]));
     J4[2][0] = 0;
     J4[3][0] = 0;
     J4[0][1] = -sin(angTorad(angles[3])) * cos(angTorad(DH_Param[3][0]));
     J4[1][1] = cos(angTorad(angles[3])) * cos(angTorad(DH_Param[3][0]));
     J4[2][1] = sin(angTorad(DH_Param[3][0]));
     J4[3][1] = 0;
     J4[0][2] = sin(angTorad(angles[3])) * sin(angTorad(DH_Param[3][0]));
     J4[1][2] = -cos(angTorad(angles[3])) * sin(angTorad(DH_Param[3][0]));
     J4[2][2] = cos(angTorad(DH_Param[3][0]));
     J4[3][2] = 0;
     J4[0][3] = DH_Param[3][2] * cos(angTorad(angles[3]));
     J4[1][3] = DH_Param[3][2] * sin(angTorad(angles[3])); ;
     J4[2][3] = DH_Param[3][1];
     J4[3][3] = 1;


     //JOIN 5 MATRIX 
     J5[0][0] = cos(angTorad(angles[4]));
     J5[1][0] = sin(angTorad(angles[4]));
     J5[2][0] = 0;
     J5[3][0] = 0;
     J5[0][1] = -sin(angTorad(angles[4])) * cos(angTorad(DH_Param[4][0]));
     J5[1][1] = cos(angTorad(angles[4])) * cos(angTorad(DH_Param[4][0]));
     J5[2][1] = sin(angTorad(DH_Param[4][0]));
     J5[3][1] = 0;
     J5[0][2] = sin(angTorad(angles[4])) * sin(angTorad(DH_Param[4][0]));
     J5[1][2] = -cos(angTorad(angles[4])) * sin(angTorad(DH_Param[4][0]));
     J5[2][2] = cos(angTorad(DH_Param[4][0]));
     J5[3][2] = 0;
     J5[0][3] = DH_Param[4][2] * cos(angTorad(angles[4]));
     J5[1][3] = DH_Param[4][2] * sin(angTorad(angles[4])); ;
     J5[2][3] = DH_Param[4][1];
     J5[3][3] = 1;


     //JOIN 6 MATRIX 
     J6[0][0] = cos(angTorad(angles[5]));
     J6[1][0] = sin(angTorad(angles[5]));
     J6[2][0] = 0;
     J6[3][0] = 0;
     J6[0][1] = -sin(angTorad(angles[5])) * cos(angTorad(DH_Param[5][0]));
     J6[1][1] = cos(angTorad(angles[5])) * cos(angTorad(DH_Param[5][0]));
     J6[2][1] = sin(angTorad(DH_Param[5][0]));
     J6[3][1] = 0;
     J6[0][2] = sin(angTorad(angles[5])) * sin(angTorad(DH_Param[5][0]));
     J6[1][2] = -cos(angTorad(angles[5])) * sin(angTorad(DH_Param[5][0]));
     J6[2][2] = cos(angTorad(DH_Param[5][0]));
     J6[3][2] = 0;
     J6[0][3] = DH_Param[5][2] * cos(angTorad(angles[5]));
     J6[1][3] = DH_Param[5][2] * sin(angTorad(angles[5])); ;
     J6[2][3] = DH_Param[5][1];
     J6[3][3] = 1;


     //TOOL FRAME MATRIX
     TFM[0][0] = cos(angTorad(TFrame[5])) * cos(angTorad(TFrame[4]));
     TFM[1][0] = sin(angTorad(TFrame[5])) * cos(angTorad(TFrame[4]));
     TFM[2][0] = -sin(angTorad(TFrame[5]));
     TFM[3][0] = 0;
     TFM[0][1] = -sin(angTorad(TFrame[5])) * cos(angTorad(TFrame[3])) + cos(angTorad(TFrame[5])) * sin(angTorad(TFrame[4])) * sin(angTorad(TFrame[3]));
     TFM[1][1] = cos(angTorad(TFrame[5])) * cos(angTorad(TFrame[3])) + sin(angTorad(TFrame[5])) * sin(angTorad(TFrame[4])) * sin(angTorad(TFrame[3]));
     TFM[2][1] = cos(angTorad(TFrame[4])) * sin(angTorad(TFrame[3]));
     TFM[3][1] = 0;
     TFM[0][2] = sin(angTorad(TFrame[5])) * sin(angTorad(TFrame[3])) + cos(angTorad(TFrame[5])) * sin(angTorad(TFrame[4])) * cos(angTorad(TFrame[3]));
     TFM[1][2] = -cos(angTorad(TFrame[5])) * sin(angTorad(TFrame[3])) + sin(angTorad(TFrame[5])) * sin(angTorad(TFrame[4])) * cos(angTorad(TFrame[3]));
     TFM[2][2] = cos(angTorad(TFrame[4])) * cos(angTorad(TFrame[3]));
     TFM[3][2] = 0;
     TFM[0][3] = TFrame[0];
     TFM[1][3] = TFrame[1];
     TFM[2][3] = TFrame[2];
     TFM[3][3] = 1;

     //T1 MATRIX
     T1[0][0] = (WFM[0][0] * J1[0][0]) + (WFM[0][1] * J1[1][0]) + (WFM[0][2] * J1[2][0]) + (WFM[0][3] * J1[3][0]);
     T1[1][0] = (WFM[1][0] * J1[0][0]) + (WFM[1][1] * J1[1][0]) + (WFM[1][2] * J1[2][0]) + (WFM[1][3] * J1[3][0]);
     T1[2][0] = (WFM[2][0] * J1[0][0]) + (WFM[2][1] * J1[1][0]) + (WFM[2][2] * J1[2][0]) + (WFM[2][3] * J1[3][0]);
     T1[3][0] = (WFM[3][0] * J1[0][0]) + (WFM[3][1] * J1[1][0]) + (WFM[3][2] * J1[2][0]) + (WFM[3][3] * J1[3][0]);
     T1[0][1] = (WFM[0][0] * J1[0][1]) + (WFM[0][1] * J1[1][1]) + (WFM[0][2] * J1[2][1]) + (WFM[0][3] * J1[3][1]);
     T1[1][1] = (WFM[1][0] * J1[0][1]) + (WFM[1][1] * J1[1][1]) + (WFM[1][2] * J1[2][1]) + (WFM[1][3] * J1[3][1]);
     T1[2][1] = (WFM[2][0] * J1[0][1]) + (WFM[2][1] * J1[1][1]) + (WFM[2][2] * J1[2][1]) + (WFM[2][3] * J1[3][1]);
     T1[3][1] = (WFM[3][0] * J1[0][1]) + (WFM[3][1] * J1[1][1]) + (WFM[3][2] * J1[2][1]) + (WFM[3][3] * J1[3][1]);
     T1[0][2] = (WFM[0][0] * J1[0][2]) + (WFM[0][1] * J1[1][2]) + (WFM[0][2] * J1[2][2]) + (WFM[0][3] * J1[3][2]);
     T1[1][2] = (WFM[1][0] * J1[0][2]) + (WFM[1][1] * J1[1][2]) + (WFM[1][2] * J1[2][2]) + (WFM[1][3] * J1[3][2]);
     T1[2][2] = (WFM[2][0] * J1[0][2]) + (WFM[2][1] * J1[1][2]) + (WFM[2][2] * J1[2][2]) + (WFM[2][3] * J1[3][2]);
     T1[3][2] = (WFM[3][0] * J1[0][2]) + (WFM[3][1] * J1[1][2]) + (WFM[3][2] * J1[2][2]) + (WFM[3][3] * J1[3][2]);
     T1[0][3] = (WFM[0][0] * J1[0][3]) + (WFM[0][1] * J1[1][3]) + (WFM[0][2] * J1[2][3]) + (WFM[0][3] * J1[3][3]);
     T1[1][3] = (WFM[1][0] * J1[0][3]) + (WFM[1][1] * J1[1][3]) + (WFM[1][2] * J1[2][3]) + (WFM[1][3] * J1[3][3]);
     T1[2][3] = (WFM[2][0] * J1[0][3]) + (WFM[2][1] * J1[1][3]) + (WFM[2][2] * J1[2][3]) + (WFM[2][3] * J1[3][3]);
     T1[3][3] = (WFM[3][0] * J1[0][3]) + (WFM[3][1] * J1[1][3]) + (WFM[3][2] * J1[2][3]) + (WFM[3][3] * J1[3][3]);

     //T2 MATRIX
     T2[0][0] = (T1[0][0] * J2[0][0]) + (T1[0][1] * J2[1][0]) + (T1[0][2] * J2[2][0]) + (T1[0][3] * J2[3][0]);
     T2[1][0] = (T1[1][0] * J2[0][0]) + (T1[1][1] * J2[1][0]) + (T1[1][2] * J2[2][0]) + (T1[1][3] * J2[3][0]);
     T2[2][0] = (T1[2][0] * J2[0][0]) + (T1[2][1] * J2[1][0]) + (T1[2][2] * J2[2][0]) + (T1[2][3] * J2[3][0]);
     T2[3][0] = (T1[3][0] * J2[0][0]) + (T1[3][1] * J2[1][0]) + (T1[3][2] * J2[2][0]) + (T1[3][3] * J2[3][0]);
     T2[0][1] = (T1[0][0] * J2[0][1]) + (T1[0][1] * J2[1][1]) + (T1[0][2] * J2[2][1]) + (T1[0][3] * J2[3][1]);
     T2[1][1] = (T1[1][0] * J2[0][1]) + (T1[1][1] * J2[1][1]) + (T1[1][2] * J2[2][1]) + (T1[1][3] * J2[3][1]);
     T2[2][1] = (T1[2][0] * J2[0][1]) + (T1[2][1] * J2[1][1]) + (T1[2][2] * J2[2][1]) + (T1[2][3] * J2[3][1]);
     T2[3][1] = (T1[3][0] * J2[0][1]) + (T1[3][1] * J2[1][1]) + (T1[3][2] * J2[2][1]) + (T1[3][3] * J2[3][1]);
     T2[0][2] = (T1[0][0] * J2[0][2]) + (T1[0][1] * J2[1][2]) + (T1[0][2] * J2[2][2]) + (T1[0][3] * J2[3][2]);
     T2[1][2] = (T1[1][0] * J2[0][2]) + (T1[1][1] * J2[1][2]) + (T1[1][2] * J2[2][2]) + (T1[1][3] * J2[3][2]);
     T2[2][2] = (T1[2][0] * J2[0][2]) + (T1[2][1] * J2[1][2]) + (T1[2][2] * J2[2][2]) + (T1[2][3] * J2[3][2]);
     T2[3][2] = (T1[3][0] * J2[0][2]) + (T1[3][1] * J2[1][2]) + (T1[3][2] * J2[2][2]) + (T1[3][3] * J2[3][2]);
     T2[0][3] = (T1[0][0] * J2[0][3]) + (T1[0][1] * J2[1][3]) + (T1[0][2] * J2[2][3]) + (T1[0][3] * J2[3][3]);
     T2[1][3] = (T1[1][0] * J2[0][3]) + (T1[1][1] * J2[1][3]) + (T1[1][2] * J2[2][3]) + (T1[1][3] * J2[3][3]);
     T2[2][3] = (T1[2][0] * J2[0][3]) + (T1[2][1] * J2[1][3]) + (T1[2][2] * J2[2][3]) + (T1[2][3] * J2[3][3]);
     T2[3][3] = (T1[3][0] * J2[0][3]) + (T1[3][1] * J2[1][3]) + (T1[3][2] * J2[2][3]) + (T1[3][3] * J2[3][3]);

     //T3 MATRIX
     T3[0][0] = (T2[0][0] * J3[0][0]) + (T2[0][1] * J3[1][0]) + (T2[0][2] * J3[2][0]) + (T2[0][3] * J3[3][0]);
     T3[1][0] = (T2[1][0] * J3[0][0]) + (T2[1][1] * J3[1][0]) + (T2[1][2] * J3[2][0]) + (T2[1][3] * J3[3][0]);
     T3[2][0] = (T2[2][0] * J3[0][0]) + (T2[2][1] * J3[1][0]) + (T2[2][2] * J3[2][0]) + (T2[2][3] * J3[3][0]);
     T3[3][0] = (T2[3][0] * J3[0][0]) + (T2[3][1] * J3[1][0]) + (T2[3][2] * J3[2][0]) + (T2[3][3] * J3[3][0]);
     T3[0][1] = (T2[0][0] * J3[0][1]) + (T2[0][1] * J3[1][1]) + (T2[0][2] * J3[2][1]) + (T2[0][3] * J3[3][1]);
     T3[1][1] = (T2[1][0] * J3[0][1]) + (T2[1][1] * J3[1][1]) + (T2[1][2] * J3[2][1]) + (T2[1][3] * J3[3][1]);
     T3[2][1] = (T2[2][0] * J3[0][1]) + (T2[2][1] * J3[1][1]) + (T2[2][2] * J3[2][1]) + (T2[2][3] * J3[3][1]);
     T3[3][1] = (T2[3][0] * J3[0][1]) + (T2[3][1] * J3[1][1]) + (T2[3][2] * J3[2][1]) + (T2[3][3] * J3[3][1]);
     T3[0][2] = (T2[0][0] * J3[0][2]) + (T2[0][1] * J3[1][2]) + (T2[0][2] * J3[2][2]) + (T2[0][3] * J3[3][2]);
     T3[1][2] = (T2[1][0] * J3[0][2]) + (T2[1][1] * J3[1][2]) + (T2[1][2] * J3[2][2]) + (T2[1][3] * J3[3][2]);
     T3[2][2] = (T2[2][0] * J3[0][2]) + (T2[2][1] * J3[1][2]) + (T2[2][2] * J3[2][2]) + (T2[2][3] * J3[3][2]);
     T3[3][2] = (T2[3][0] * J3[0][2]) + (T2[3][1] * J3[1][2]) + (T2[3][2] * J3[2][2]) + (T2[3][3] * J3[3][2]);
     T3[0][3] = (T2[0][0] * J3[0][3]) + (T2[0][1] * J3[1][3]) + (T2[0][2] * J3[2][3]) + (T2[0][3] * J3[3][3]);
     T3[1][3] = (T2[1][0] * J3[0][3]) + (T2[1][1] * J3[1][3]) + (T2[1][2] * J3[2][3]) + (T2[1][3] * J3[3][3]);
     T3[2][3] = (T2[2][0] * J3[0][3]) + (T2[2][1] * J3[1][3]) + (T2[2][2] * J3[2][3]) + (T2[2][3] * J3[3][3]);
     T3[3][3] = (T2[3][0] * J3[0][3]) + (T2[3][1] * J3[1][3]) + (T2[3][2] * J3[2][3]) + (T2[3][3] * J3[3][3]);

     //T4 MATRIX
     T4[0][0] = (T3[0][0] * J4[0][0]) + (T3[0][1] * J4[1][0]) + (T3[0][2] * J4[2][0]) + (T3[0][3] * J4[3][0]);
     T4[1][0] = (T3[1][0] * J4[0][0]) + (T3[1][1] * J4[1][0]) + (T3[1][2] * J4[2][0]) + (T3[1][3] * J4[3][0]);
     T4[2][0] = (T3[2][0] * J4[0][0]) + (T3[2][1] * J4[1][0]) + (T3[2][2] * J4[2][0]) + (T3[2][3] * J4[3][0]);
     T4[3][0] = (T3[3][0] * J4[0][0]) + (T3[3][1] * J4[1][0]) + (T3[3][2] * J4[2][0]) + (T3[3][3] * J4[3][0]);
     T4[0][1] = (T3[0][0] * J4[0][1]) + (T3[0][1] * J4[1][1]) + (T3[0][2] * J4[2][1]) + (T3[0][3] * J4[3][1]);
     T4[1][1] = (T3[1][0] * J4[0][1]) + (T3[1][1] * J4[1][1]) + (T3[1][2] * J4[2][1]) + (T3[1][3] * J4[3][1]);
     T4[2][1] = (T3[2][0] * J4[0][1]) + (T3[2][1] * J4[1][1]) + (T3[2][2] * J4[2][1]) + (T3[2][3] * J4[3][1]);
     T4[3][1] = (T3[3][0] * J4[0][1]) + (T3[3][1] * J4[1][1]) + (T3[3][2] * J4[2][1]) + (T3[3][3] * J4[3][1]);
     T4[0][2] = (T3[0][0] * J4[0][2]) + (T3[0][1] * J4[1][2]) + (T3[0][2] * J4[2][2]) + (T3[0][3] * J4[3][2]);
     T4[1][2] = (T3[1][0] * J4[0][2]) + (T3[1][1] * J4[1][2]) + (T3[1][2] * J4[2][2]) + (T3[1][3] * J4[3][2]);
     T4[2][2] = (T3[2][0] * J4[0][2]) + (T3[2][1] * J4[1][2]) + (T3[2][2] * J4[2][2]) + (T3[2][3] * J4[3][2]);
     T4[3][2] = (T3[3][0] * J4[0][2]) + (T3[3][1] * J4[1][2]) + (T3[3][2] * J4[2][2]) + (T3[3][3] * J4[3][2]);
     T4[0][3] = (T3[0][0] * J4[0][3]) + (T3[0][1] * J4[1][3]) + (T3[0][2] * J4[2][3]) + (T3[0][3] * J4[3][3]);
     T4[1][3] = (T3[1][0] * J4[0][3]) + (T3[1][1] * J4[1][3]) + (T3[1][2] * J4[2][3]) + (T3[1][3] * J4[3][3]);
     T4[2][3] = (T3[2][0] * J4[0][3]) + (T3[2][1] * J4[1][3]) + (T3[2][2] * J4[2][3]) + (T3[2][3] * J4[3][3]);
     T4[3][3] = (T3[3][0] * J4[0][3]) + (T3[3][1] * J4[1][3]) + (T3[3][2] * J4[2][3]) + (T3[3][3] * J4[3][3]);

     //T5 MATRIX
     T5[0][0] = (T4[0][0] * J5[0][0]) + (T4[0][1] * J5[1][0]) + (T4[0][2] * J5[2][0]) + (T4[0][3] * J5[3][0]);
     T5[1][0] = (T4[1][0] * J5[0][0]) + (T4[1][1] * J5[1][0]) + (T4[1][2] * J5[2][0]) + (T4[1][3] * J5[3][0]);
     T5[2][0] = (T4[2][0] * J5[0][0]) + (T4[2][1] * J5[1][0]) + (T4[2][2] * J5[2][0]) + (T4[2][3] * J5[3][0]);
     T5[3][0] = (T4[3][0] * J5[0][0]) + (T4[3][1] * J5[1][0]) + (T4[3][2] * J5[2][0]) + (T4[3][3] * J5[3][0]);
     T5[0][1] = (T4[0][0] * J5[0][1]) + (T4[0][1] * J5[1][1]) + (T4[0][2] * J5[2][1]) + (T4[0][3] * J5[3][1]);
     T5[1][1] = (T4[1][0] * J5[0][1]) + (T4[1][1] * J5[1][1]) + (T4[1][2] * J5[2][1]) + (T4[1][3] * J5[3][1]);
     T5[2][1] = (T4[2][0] * J5[0][1]) + (T4[2][1] * J5[1][1]) + (T4[2][2] * J5[2][1]) + (T4[2][3] * J5[3][1]);
     T5[3][1] = (T4[3][0] * J5[0][1]) + (T4[3][1] * J5[1][1]) + (T4[3][2] * J5[2][1]) + (T4[3][3] * J5[3][1]);
     T5[0][2] = (T4[0][0] * J5[0][2]) + (T4[0][1] * J5[1][2]) + (T4[0][2] * J5[2][2]) + (T4[0][3] * J5[3][2]);
     T5[1][2] = (T4[1][0] * J5[0][2]) + (T4[1][1] * J5[1][2]) + (T4[1][2] * J5[2][2]) + (T4[1][3] * J5[3][2]);
     T5[2][2] = (T4[2][0] * J5[0][2]) + (T4[2][1] * J5[1][2]) + (T4[2][2] * J5[2][2]) + (T4[2][3] * J5[3][2]);
     T5[3][2] = (T4[3][0] * J5[0][2]) + (T4[3][1] * J5[1][2]) + (T4[3][2] * J5[2][2]) + (T4[3][3] * J5[3][2]);
     T5[0][3] = (T4[0][0] * J5[0][3]) + (T4[0][1] * J5[1][3]) + (T4[0][2] * J5[2][3]) + (T4[0][3] * J5[3][3]);
     T5[1][3] = (T4[1][0] * J5[0][3]) + (T4[1][1] * J5[1][3]) + (T4[1][2] * J5[2][3]) + (T4[1][3] * J5[3][3]);//j49 -> h5 -> y
     T5[2][3] = (T4[2][0] * J5[0][3]) + (T4[2][1] * J5[1][3]) + (T4[2][2] * J5[2][3]) + (T4[2][3] * J5[3][3]);
     T5[3][3] = (T4[3][0] * J5[0][3]) + (T4[3][1] * J5[1][3]) + (T4[3][2] * J5[2][3]) + (T4[3][3] * J5[3][3]);

     //T6 MATRIX
     T6[0][0] = (T5[0][0] * J6[0][0]) + (T5[0][1] * J6[1][0]) + (T5[0][2] * J6[2][0]) + (T5[0][3] * J6[3][0]);
     T6[1][0] = (T5[1][0] * J6[0][0]) + (T5[1][1] * J6[1][0]) + (T5[1][2] * J6[2][0]) + (T5[1][3] * J6[3][0]);
     T6[2][0] = (T5[2][0] * J6[0][0]) + (T5[2][1] * J6[1][0]) + (T5[2][2] * J6[2][0]) + (T5[2][3] * J6[3][0]);
     T6[3][0] = (T5[3][0] * J6[0][0]) + (T5[3][1] * J6[1][0]) + (T5[3][2] * J6[2][0]) + (T5[3][3] * J6[3][0]);
     T6[0][1] = (T5[0][0] * J6[0][1]) + (T5[0][1] * J6[1][1]) + (T5[0][2] * J6[2][1]) + (T5[0][3] * J6[3][1]);
     T6[1][1] = (T5[1][0] * J6[0][1]) + (T5[1][1] * J6[1][1]) + (T5[1][2] * J6[2][1]) + (T5[1][3] * J6[3][1]);
     T6[2][1] = (T5[2][0] * J6[0][1]) + (T5[2][1] * J6[1][1]) + (T5[2][2] * J6[2][1]) + (T5[2][3] * J6[3][1]);
     T6[3][1] = (T5[3][0] * J6[0][1]) + (T5[3][1] * J6[1][1]) + (T5[3][2] * J6[2][1]) + (T5[3][3] * J6[3][1]);
     T6[0][2] = (T5[0][0] * J6[0][2]) + (T5[0][1] * J6[1][2]) + (T5[0][2] * J6[2][2]) + (T5[0][3] * J6[3][2]);
     T6[1][2] = (T5[1][0] * J6[0][2]) + (T5[1][1] * J6[1][2]) + (T5[1][2] * J6[2][2]) + (T5[1][3] * J6[3][2]);
     T6[2][2] = (T5[2][0] * J6[0][2]) + (T5[2][1] * J6[1][2]) + (T5[2][2] * J6[2][2]) + (T5[2][3] * J6[3][2]);
     T6[3][2] = (T5[3][0] * J6[0][2]) + (T5[3][1] * J6[1][2]) + (T5[3][2] * J6[2][2]) + (T5[3][3] * J6[3][2]);
     T6[0][3] = (T5[0][0] * J6[0][3]) + (T5[0][1] * J6[1][3]) + (T5[0][2] * J6[2][3]) + (T5[0][3] * J6[3][3]);
     T6[1][3] = (T5[1][0] * J6[0][3]) + (T5[1][1] * J6[1][3]) + (T5[1][2] * J6[2][3]) + (T5[1][3] * J6[3][3]);
     T6[2][3] = (T5[2][0] * J6[0][3]) + (T5[2][1] * J6[1][3]) + (T5[2][2] * J6[2][3]) + (T5[2][3] * J6[3][3]);
     T6[3][3] = (T5[3][0] * J6[0][3]) + (T5[3][1] * J6[1][3]) + (T5[3][2] * J6[2][3]) + (T5[3][3] * J6[3][3]);

     //TT MATRIX
     TT[0][0] = (T6[0][0] * TFM[0][0]) + (T6[0][1] * TFM[1][0]) + (T6[0][2] * TFM[2][0]) + (T6[0][3] * TFM[3][0]);
     TT[1][0] = (T6[1][0] * TFM[0][0]) + (T6[1][1] * TFM[1][0]) + (T6[1][2] * TFM[2][0]) + (T6[1][3] * TFM[3][0]);
     TT[2][0] = (T6[2][0] * TFM[0][0]) + (T6[2][1] * TFM[1][0]) + (T6[2][2] * TFM[2][0]) + (T6[2][3] * TFM[3][0]);
     TT[3][0] = (T6[3][0] * TFM[0][0]) + (T6[3][1] * TFM[1][0]) + (T6[3][2] * TFM[2][0]) + (T6[3][3] * TFM[3][0]);
     TT[0][1] = (T6[0][0] * TFM[0][1]) + (T6[0][1] * TFM[1][1]) + (T6[0][2] * TFM[2][1]) + (T6[0][3] * TFM[3][1]);
     TT[1][1] = (T6[1][0] * TFM[0][1]) + (T6[1][1] * TFM[1][1]) + (T6[1][2] * TFM[2][1]) + (T6[1][3] * TFM[3][1]);
     TT[2][1] = (T6[2][0] * TFM[0][1]) + (T6[2][1] * TFM[1][1]) + (T6[2][2] * TFM[2][1]) + (T6[2][3] * TFM[3][1]);
     TT[3][1] = (T6[3][0] * TFM[0][1]) + (T6[3][1] * TFM[1][1]) + (T6[3][2] * TFM[2][1]) + (T6[3][3] * TFM[3][1]);
     TT[0][2] = (T6[0][0] * TFM[0][2]) + (T6[0][1] * TFM[1][2]) + (T6[0][2] * TFM[2][2]) + (T6[0][3] * TFM[3][2]);
     TT[1][2] = (T6[1][0] * TFM[0][2]) + (T6[1][1] * TFM[1][2]) + (T6[1][2] * TFM[2][2]) + (T6[1][3] * TFM[3][2]);
     TT[2][2] = (T6[2][0] * TFM[0][2]) + (T6[2][1] * TFM[1][2]) + (T6[2][2] * TFM[2][2]) + (T6[2][3] * TFM[3][2]);
     TT[3][2] = (T6[3][0] * TFM[0][2]) + (T6[3][1] * TFM[1][2]) + (T6[3][2] * TFM[2][2]) + (T6[3][3] * TFM[3][2]);
     TT[0][3] = (T6[0][0] * TFM[0][3]) + (T6[0][1] * TFM[1][3]) + (T6[0][2] * TFM[2][3]) + (T6[0][3] * TFM[3][3]);
     TT[1][3] = (T6[1][0] * TFM[0][3]) + (T6[1][1] * TFM[1][3]) + (T6[1][2] * TFM[2][3]) + (T6[1][3] * TFM[3][3]);
     TT[2][3] = (T6[2][0] * TFM[0][3]) + (T6[2][1] * TFM[1][3]) + (T6[2][2] * TFM[2][3]) + (T6[2][3] * TFM[3][3]);
     TT[3][3] = (T6[3][0] * TFM[0][3]) + (T6[3][1] * TFM[1][3]) + (T6[3][2] * TFM[2][3]) + (T6[3][3] * TFM[3][3]);

//***************************
     if(J1[1][3] < 0)
     {
         if(J1[0][3] < 0)
         {
             fkv.QU_J1 = 1;
         }
         else fkv.QU_J1 = 2;
     }else if (J1[0][3] < 0)
     {
         fkv.QU_J1 = 4;
     }else fkv.QU_J1 = 3;

     if(T5[1][3] < 0)
     {
         if (T5[0][3] < 0)
         {
             fkv.QU_J5 = 1;
         }
         else fkv.QU_J5 = 2;
     }else if(T5[0][3] < 0)
     {
         fkv.QU_J5 = 4;
     }else fkv.QU_J5 = 3;
     //****************************          
     fkv.pitch = radToang(atan2(sqrt(pow(TT[0][2],2)+ pow(TT[1][2],2)), -TT[2][2]));
     fkv.yaw = radToang(atan2(TT[2][0] / fkv.pitch,TT[2][1] / fkv.pitch));
     fkv.roll = radToang(atan2(TT[0][2] / fkv.pitch,TT[1][2] / fkv.pitch));

     fkv.x = T5[0][3];
     fkv.y = T5[1][3];
     fkv.z = T5[2][3];

 }
 void Kinematics::invKinematics(const struct ActCoord &ActCoord, const struct ActCoord &NewCoord, const vector<vector<double>>& DH_Param, const vector<double>& WFrame,
                    const vector<vector<double>>& TT, const vector<double>& anglesAct, struct Join &Join)
 {
     double armLen1, armLen2, armLen3, armLen3_1, vekP_J2, vekP_J3, armHeight;
     double theta1, theta2_cos, theta2_atan, theta4, theta5, theta6;

     //WFrame = new double[6];
     //DH_Param = new double[6][3];
     //TT = new double[4][4];
     //anglesAct = new double[6];

     double WFM[4][4];
     double J1[4][4];
     double J2[4][4];
     double J3[4][4];
     double DH_Param_Local[6];
     double WFM_J1[4][4];
     double WFM_J1_J2[4][4];
     double WFM_J1_J2_J3[4][4];
     double INV_OF_WFM_J1_J2_J3[6][6];
     double Minor_Determinant[3][3];
     double Cofactors[3][3];
     double Cofactors_Mult_Determinant[3][3];
     double Adjugate_Matrix[3][3];
     double Determinant;
     double Inverse_WFM_J1_J2_J3[3][3];
     double Z_Change[3][3];
     double Y_Change[3][3];
     double X_Change[3][3];
     double Current_R0T[3][3];
     double Z_MULT_Y[3][3];
     double Z_MULT_Y_MULTX[3][3];
     double Z_MULT_Y_MULTX_0T[3][3];
     double R_3_6[3][3];
     double A4, A5, A6, A4_2, A5_2, A6_2;


     if (ActCoord.QU_J1 == 1)
     {
         Join.J1 = (radToang(atan((ActCoord.y + NewCoord.y) / (ActCoord.x + NewCoord.x))) - 90) - 90;
     }
     else if (ActCoord.QU_J1 == 2)
     {
         Join.J1 = radToang(atan((ActCoord.y + NewCoord.y) / (ActCoord.x + NewCoord.x)));
     }
     else if (ActCoord.QU_J1 == 3)
     {
         Join.J1 = radToang(atan((ActCoord.y + NewCoord.y) / (ActCoord.x + NewCoord.x)));
     }
     else Join.J1 = 90 + radToang(atan((ActCoord.y + NewCoord.y) / (ActCoord.x + NewCoord.x))) + 90;

     armLen1 = sqrt(pow(ActCoord.y + NewCoord.y, 2) + pow(ActCoord.x + NewCoord.x, 2)) + DH_Param[0][2];  //P14
     armLen2 = sqrt(pow(ActCoord.y + NewCoord.y, 2) + pow(ActCoord.x + NewCoord.x, 2));   //P15
     armLen3 = abs(armLen2 - DH_Param[0][2]);   //P16
     armLen3_1 = armLen2 - DH_Param[0][2];      //Q16
     armHeight = (ActCoord.z + NewCoord.z) - DH_Param[0][1];  //P17

     if (ActCoord.QU_J1 == ActCoord.QU_J5)
     {
         vekP_J2 = sqrt(pow(armLen3, 2) + pow(armHeight, 2));//P19
     }
     else vekP_J2 = sqrt(pow(armLen1, 2) + pow(armHeight, 2));

     theta1 = radToang(atan(armHeight / armLen3));
     theta5 = radToang(atan(armLen3 / armHeight));
     vekP_J3 = sqrt(pow(DH_Param[2][2], 2) + (pow(abs(DH_Param[3][1]), 2)));//P24

     theta6 = radToang(atan(armHeight / armLen1));
     double test = 2 * DH_Param[1][2] * vekP_J2;
     double test2 = pow(DH_Param[1][2], 2) + pow(vekP_J2, 2) - pow(vekP_J3, 2);

     theta2_cos = radToang(acos((pow(DH_Param[1][2], 2) + pow(vekP_J2, 2) - pow(vekP_J3, 2)) / (2 * DH_Param[1][2] * vekP_J2)));
     theta2_atan = radToang(atan2(sqrt(1 - pow((pow(DH_Param[1][2], 2) + pow(vekP_J2, 2) - pow(vekP_J3, 2)) / (2 * DH_Param[1][2] * vekP_J2), 2)), pow(DH_Param[1][2], 2) + pow(vekP_J2, 2) - pow(vekP_J3, 2)) / (2 * DH_Param[1][2] * vekP_J2));

     if (armLen3_1 > 0 && ActCoord.QU_J1 == ActCoord.QU_J5)
     {
         Join.J2 = -(theta1 + theta2_cos);
     }
     else if (armLen3_1 > 0 && ActCoord.QU_J1 != ActCoord.QU_J5)
     {
         Join.J2 = -(180 - theta6 + theta2_cos);
     }
     else if (armLen3_1 < 0 && ActCoord.QU_J1 != ActCoord.QU_J5)
     {
         Join.J2 = -(180 - theta6 + theta2_cos);
     }
     else
     {
         Join.J2 = -(theta2_cos + theta5 + 90);
     }

     theta4 = radToang(acos((pow(vekP_J3, 2) + pow(abs(DH_Param[3][1]), 2) - pow(DH_Param[2][2], 2)) / (2 * vekP_J3 * abs(DH_Param[3][1]))));
     Join.J3 = 180 - radToang(acos((pow(vekP_J3, 2) + pow(DH_Param[1][2], 2) - pow(vekP_J2, 2)) / (2 * vekP_J3 * DH_Param[1][2]))) + theta4;

     //WORK FRAME INPUT
     DH_Param_Local[0] = angTorad(Join.J1);
     DH_Param_Local[1] = angTorad(Join.J2);
     DH_Param_Local[2] = angTorad(Join.J3-90);
     DH_Param_Local[3] = angTorad(-90);//DH_Param[0][1];
     DH_Param_Local[4] = angTorad(0);//DH_Param[1][1];
     DH_Param_Local[5] = angTorad(90);//DH_Param[2][1];

     //WORK FRAME TABLE
     WFM[0][0] = cos(angTorad(WFrame[5])) * cos(angTorad(WFrame[4]));
     WFM[1][0] = sin(angTorad(WFrame[5])) * cos(angTorad(WFrame[4]));
     WFM[2][0] = -sin(angTorad(WFrame[5]));
     WFM[3][0] = 0;
     WFM[0][1] = -sin(angTorad(WFrame[5])) * cos(angTorad(WFrame[3])) + cos(angTorad(WFrame[5])) * sin(angTorad(WFrame[4])) *
          sin(angTorad(WFrame[3]));
     WFM[1][1] = cos(angTorad(WFrame[5])) * cos(angTorad(WFrame[3])) + sin(angTorad(WFrame[5])) * sin(angTorad(WFrame[4])) *
          sin(angTorad(WFrame[3]));
     WFM[2][1] = cos(angTorad(WFrame[4])) * sin(angTorad(WFrame[3]));
     WFM[3][1] = 0;
     WFM[0][2] = sin(angTorad(WFrame[5])) * sin(angTorad(WFrame[3])) + cos(angTorad(WFrame[5])) * sin(angTorad(WFrame[4])) *
         cos(angTorad(WFrame[3]));
     WFM[1][2] = -cos(angTorad(WFrame[5])) * sin(angTorad(WFrame[3])) + sin(angTorad(WFrame[5])) * sin(angTorad(WFrame[4])) *
          cos(angTorad(WFrame[3]));
     WFM[2][2] = cos(angTorad(WFrame[4])) * cos(angTorad(WFrame[3]));
     WFM[3][2] = 0;
     WFM[0][3] = WFrame[0];
     WFM[1][3] = WFrame[1];
     WFM[2][3] = WFrame[2];
     WFM[3][3] = 1;

     // J1 FRAME
     J1[0][0] = cos(DH_Param_Local[0]);
     J1[1][0] = sin(DH_Param_Local[0]);
     J1[2][0] = 0;
     J1[3][0] = 0;
     J1[0][1] = -sin(DH_Param_Local[0]) * cos(DH_Param_Local[3]);
     J1[1][1] = cos(DH_Param_Local[0]) * cos(DH_Param_Local[3]);
     J1[2][1] = sin(DH_Param_Local[3]);
     J1[3][1] = 0;
     J1[0][2] = sin(DH_Param_Local[0]) * sin(DH_Param_Local[3]);
     J1[1][2] = -cos(DH_Param_Local[0]) * sin(DH_Param_Local[3]);
     J1[2][2] = cos(DH_Param_Local[3]);
     J1[3][2] = 0;
     J1[0][3] = DH_Param[0][2] * cos(DH_Param_Local[0]);
     J1[1][3] = DH_Param[0][2] * sin(DH_Param_Local[0]);
     J1[2][3] = DH_Param[0][1];//D1
     J1[3][3] = 1;
   
     // J2 FRAME
     J2[0][0] = cos(DH_Param_Local[1]);
     J2[1][0] = sin(DH_Param_Local[1]);
     J2[2][0] = 0;
     J2[3][0] = 0;
     J2[0][1] = -sin(DH_Param_Local[1]) * cos(DH_Param_Local[4]);
     J2[1][1] = cos(DH_Param_Local[1]) * cos(DH_Param_Local[4]);
     J2[2][1] = sin(DH_Param_Local[4]);
     J2[3][1] = 0;
     J2[0][2] = sin(DH_Param_Local[1]) * sin(DH_Param_Local[4]);
     J2[1][2] = -cos(DH_Param_Local[1]) * sin(DH_Param_Local[4]);
     J2[2][2] = cos(DH_Param_Local[4]);
     J2[3][2] = 0;
     J2[0][3] = DH_Param[1][2] * cos(DH_Param_Local[1]);
     J2[1][3] = DH_Param[1][2] * sin(DH_Param_Local[1]);
     J2[2][3] = DH_Param[1][1];
     J2[3][3] = 1;
    
     // J3 FRAME
     J3[0][0] = cos(DH_Param_Local[2]);
     J3[1][0] = sin(DH_Param_Local[2]);
     J3[2][0] = 0;
     J3[3][0] = 0;
     J3[0][1] = -sin(DH_Param_Local[2]) * cos(DH_Param_Local[5]);
     J3[1][1] = cos(DH_Param_Local[2]) * cos(DH_Param_Local[5]);
     J3[2][1] = sin(DH_Param_Local[5]);
     J3[3][1] = 0;
     J3[0][2] = sin(DH_Param_Local[2]) * sin(DH_Param_Local[5]);
     J3[1][2] = -cos(DH_Param_Local[2]) * sin(DH_Param_Local[5]);
     J3[2][2] = cos(DH_Param_Local[5]);
     J3[3][2] = 0;
     J3[0][3] = DH_Param[2][2] * cos(DH_Param_Local[2]);
     J3[1][3] = DH_Param[2][2] * sin(DH_Param_Local[2]);
     J3[2][3] = 0;
     J3[3][3] = 1;
   
     //WFM*J1
     WFM_J1[0][0] = WFM[0][0] * J1[0][0] + WFM[0][1] * J1[1][0] + WFM[0][2] * J1[2][0] + WFM[0][3] * J1[3][0];
     WFM_J1[1][0] = WFM[1][0] * J1[0][0] + WFM[1][1] * J1[1][0] + WFM[1][2] * J1[2][0] + WFM[1][3] * J1[3][0];
     WFM_J1[2][0] = WFM[2][0] * J1[0][0] + WFM[2][1] * J1[1][0] + WFM[2][2] * J1[2][0] + WFM[2][3] * J1[3][0];
     WFM_J1[3][0] = WFM[3][0] * J1[0][0] + WFM[3][1] * J1[1][0] + WFM[3][2] * J1[2][0] + WFM[3][3] * J1[3][0];
     WFM_J1[0][1] = WFM[0][0] * J1[0][1] + WFM[0][1] * J1[1][1] + WFM[0][2] * J1[2][1] + WFM[0][3] * J1[3][1];
     WFM_J1[1][1] = WFM[1][0] * J1[0][1] + WFM[1][1] * J1[1][1] + WFM[1][2] * J1[2][1] + WFM[1][3] * J1[3][1];
     WFM_J1[2][1] = WFM[2][0] * J1[0][1] + WFM[2][1] * J1[1][1] + WFM[2][2] * J1[2][1] + WFM[2][3] * J1[3][1];
     WFM_J1[3][1] = WFM[3][0] * J1[0][1] + WFM[3][1] * J1[1][1] + WFM[3][2] * J1[2][1] + WFM[3][3] * J1[3][1];
     WFM_J1[0][2] = WFM[0][0] * J1[0][2] + WFM[0][1] * J1[1][2] + WFM[0][2] * J1[2][2] + WFM[0][3] * J1[3][2];
     WFM_J1[1][2] = WFM[1][0] * J1[0][2] + WFM[1][1] * J1[1][2] + WFM[1][2] * J1[2][2] + WFM[1][3] * J1[3][2];
     WFM_J1[2][2] = WFM[2][0] * J1[0][2] + WFM[2][1] * J1[1][2] + WFM[2][2] * J1[2][2] + WFM[2][3] * J1[3][2];
     WFM_J1[3][2] = WFM[3][0] * J1[0][2] + WFM[3][1] * J1[1][2] + WFM[3][2] * J1[2][2] + WFM[3][3] * J1[3][2];
     WFM_J1[0][3] = WFM[0][0] * J1[0][3] + WFM[0][1] * J1[1][3] + WFM[0][2] * J1[2][3] + WFM[0][3] * J1[3][3];
     WFM_J1[1][3] = WFM[1][0] * J1[0][3] + WFM[1][1] * J1[1][3] + WFM[1][2] * J1[2][3] + WFM[1][3] * J1[3][3];
     WFM_J1[2][3] = WFM[2][0] * J1[0][3] + WFM[2][1] * J1[1][3] + WFM[2][2] * J1[2][3] + WFM[2][3] * J1[3][3];
     WFM_J1[3][3] = WFM[3][0] * J1[0][3] + WFM[3][1] * J1[1][3] + WFM[3][2] * J1[2][3] + WFM[3][3] * J1[3][3];
  
     //(WFM*J1)*J2
     WFM_J1_J2[0][0] = WFM_J1[0][0] * J2[0][0] + WFM_J1[0][1] * J2[1][0] + WFM_J1[0][2] * J2[2][0] + WFM_J1[0][3] * J2[3][0];
     WFM_J1_J2[1][0] = WFM_J1[1][0] * J2[0][0] + WFM_J1[1][1] * J2[1][0] + WFM_J1[1][2] * J2[2][0] + WFM_J1[1][3] * J2[3][0];
     WFM_J1_J2[2][0] = WFM_J1[2][0] * J2[0][0] + WFM_J1[2][1] * J2[1][0] + WFM_J1[2][2] * J2[2][0] + WFM_J1[2][3] * J2[3][0];
     WFM_J1_J2[3][0] = WFM_J1[3][0] * J2[0][0] + WFM_J1[3][1] * J2[1][0] + WFM_J1[3][2] * J2[2][0] + WFM_J1[3][3] * J2[3][0];
     WFM_J1_J2[0][1] = WFM_J1[0][0] * J2[0][1] + WFM_J1[0][1] * J2[1][1] + WFM_J1[0][2] * J2[2][1] + WFM_J1[0][3] * J2[3][1];
     WFM_J1_J2[1][1] = WFM_J1[1][0] * J2[0][1] + WFM_J1[1][1] * J2[1][1] + WFM_J1[1][2] * J2[2][1] + WFM_J1[1][3] * J2[3][1];
     WFM_J1_J2[2][1] = WFM_J1[2][0] * J2[0][1] + WFM_J1[2][1] * J2[1][1] + WFM_J1[2][2] * J2[2][1] + WFM_J1[2][3] * J2[3][1];
     WFM_J1_J2[3][1] = WFM_J1[3][0] * J2[0][1] + WFM_J1[3][1] * J2[1][1] + WFM_J1[3][2] * J2[2][1] + WFM_J1[3][3] * J2[3][1];
     WFM_J1_J2[0][2] = WFM_J1[0][0] * J2[0][2] + WFM_J1[0][1] * J2[1][2] + WFM_J1[0][2] * J2[2][2] + WFM_J1[0][3] * J2[3][2];
     WFM_J1_J2[1][2] = WFM_J1[1][0] * J2[0][2] + WFM_J1[1][1] * J2[1][2] + WFM_J1[1][2] * J2[2][2] + WFM_J1[1][3] * J2[3][2];
     WFM_J1_J2[2][2] = WFM_J1[2][0] * J2[0][2] + WFM_J1[2][1] * J2[1][2] + WFM_J1[2][2] * J2[2][2] + WFM_J1[2][3] * J2[3][2];
     WFM_J1_J2[3][2] = WFM_J1[3][0] * J2[0][2] + WFM_J1[3][1] * J2[1][2] + WFM_J1[3][2] * J2[2][2] + WFM_J1[3][3] * J2[3][2];
     WFM_J1_J2[0][3] = WFM_J1[0][0] * J2[0][3] + WFM_J1[0][1] * J2[1][3] + WFM_J1[0][2] * J2[2][3] + WFM_J1[0][3] * J2[3][3];
     WFM_J1_J2[1][3] = WFM_J1[1][0] * J2[0][3] + WFM_J1[1][1] * J2[1][3] + WFM_J1[1][2] * J2[2][3] + WFM_J1[1][3] * J2[3][3];
     WFM_J1_J2[2][3] = WFM_J1[2][0] * J2[0][3] + WFM_J1[2][1] * J2[1][3] + WFM_J1[2][2] * J2[2][3] + WFM_J1[2][3] * J2[3][3];
     WFM_J1_J2[3][3] = WFM_J1[3][0] * J2[0][3] + WFM_J1[3][1] * J2[1][3] + WFM_J1[3][2] * J2[2][3] + WFM_J1[3][3] * J2[3][3];
   

     //(WFM*J1*J2)*J3
     WFM_J1_J2_J3[0][0] = WFM_J1_J2[0][0] * J3[0][0] + WFM_J1_J2[0][1] * J3[1][0] + WFM_J1_J2[0][2] * J3[2][0] + WFM_J1_J2[0][3] * J3[3][0];
     WFM_J1_J2_J3[1][0] = WFM_J1_J2[1][0] * J3[0][0] + WFM_J1_J2[1][1] * J3[1][0] + WFM_J1_J2[1][2] * J3[2][0] + WFM_J1_J2[1][3] * J3[3][0];
     WFM_J1_J2_J3[2][0] = WFM_J1_J2[2][0] * J3[0][0] + WFM_J1_J2[2][1] * J3[1][0] + WFM_J1_J2[2][2] * J3[2][0] + WFM_J1_J2[2][3] * J3[3][0];
     WFM_J1_J2_J3[3][0] = WFM_J1_J2[3][0] * J3[0][0] + WFM_J1_J2[3][1] * J3[1][0] + WFM_J1_J2[3][2] * J3[2][0] + WFM_J1_J2[3][3] * J3[3][0];
     WFM_J1_J2_J3[0][1] = WFM_J1_J2[0][0] * J3[0][1] + WFM_J1_J2[0][1] * J3[1][1] + WFM_J1_J2[0][2] * J3[2][1] + WFM_J1_J2[0][3] * J3[3][1];
     WFM_J1_J2_J3[1][1] = WFM_J1_J2[1][0] * J3[0][1] + WFM_J1_J2[1][1] * J3[1][1] + WFM_J1_J2[1][2] * J3[2][1] + WFM_J1_J2[1][3] * J3[3][1];
     WFM_J1_J2_J3[2][1] = WFM_J1_J2[2][0] * J3[0][1] + WFM_J1_J2[2][1] * J3[1][1] + WFM_J1_J2[2][2] * J3[2][1] + WFM_J1_J2[2][3] * J3[3][1];
     WFM_J1_J2_J3[3][1] = WFM_J1_J2[3][0] * J3[0][1] + WFM_J1_J2[3][1] * J3[1][1] + WFM_J1_J2[3][2] * J3[2][1] + WFM_J1_J2[3][3] * J3[3][1];
     WFM_J1_J2_J3[0][2] = WFM_J1_J2[0][0] * J3[0][2] + WFM_J1_J2[0][1] * J3[1][2] + WFM_J1_J2[0][2] * J3[2][2] + WFM_J1_J2[0][3] * J3[3][2];
     WFM_J1_J2_J3[1][2] = WFM_J1_J2[1][0] * J3[0][2] + WFM_J1_J2[1][1] * J3[1][2] + WFM_J1_J2[1][2] * J3[2][2] + WFM_J1_J2[1][3] * J3[3][2];
     WFM_J1_J2_J3[2][2] = WFM_J1_J2[2][0] * J3[0][2] + WFM_J1_J2[2][1] * J3[1][2] + WFM_J1_J2[2][2] * J3[2][2] + WFM_J1_J2[2][3] * J3[3][2];
     WFM_J1_J2_J3[3][2] = WFM_J1_J2[3][0] * J3[0][2] + WFM_J1_J2[3][1] * J3[1][2] + WFM_J1_J2[3][2] * J3[2][2] + WFM_J1_J2[3][3] * J3[3][2];
     WFM_J1_J2_J3[0][3] = WFM_J1_J2[0][0] * J3[0][3] + WFM_J1_J2[0][1] * J3[1][3] + WFM_J1_J2[0][2] * J3[2][3] + WFM_J1_J2[0][3] * J3[3][3];
     WFM_J1_J2_J3[1][3] = WFM_J1_J2[1][0] * J3[0][3] + WFM_J1_J2[1][1] * J3[1][3] + WFM_J1_J2[1][2] * J3[2][3] + WFM_J1_J2[1][3] * J3[3][3];
     WFM_J1_J2_J3[2][3] = WFM_J1_J2[2][0] * J3[0][3] + WFM_J1_J2[2][1] * J3[1][3] + WFM_J1_J2[2][2] * J3[2][3] + WFM_J1_J2[2][3] * J3[3][3];
     WFM_J1_J2_J3[3][3] = WFM_J1_J2[3][0] * J3[0][3] + WFM_J1_J2[3][1] * J3[1][3] + WFM_J1_J2[3][2] * J3[2][3] + WFM_J1_J2[3][3] * J3[3][3];
   

     //INVERSE OF (WF*J1*J2)*J3
     INV_OF_WFM_J1_J2_J3[0][0] = WFM_J1_J2_J3[1][1];//Y48
     INV_OF_WFM_J1_J2_J3[1][0] = WFM_J1_J2_J3[2][1];//Y49
     INV_OF_WFM_J1_J2_J3[0][1] = WFM_J1_J2_J3[1][2];//Z48
     INV_OF_WFM_J1_J2_J3[1][1] = WFM_J1_J2_J3[2][2];//Z49
     INV_OF_WFM_J1_J2_J3[0][2] = WFM_J1_J2_J3[1][0];//AA48
     INV_OF_WFM_J1_J2_J3[1][2] = WFM_J1_J2_J3[2][0];//AA49
     INV_OF_WFM_J1_J2_J3[0][3] = WFM_J1_J2_J3[1][2];//AB48
     INV_OF_WFM_J1_J2_J3[1][3] = WFM_J1_J2_J3[2][2];//AB49
     INV_OF_WFM_J1_J2_J3[0][4] = WFM_J1_J2_J3[1][0];//AC48
     INV_OF_WFM_J1_J2_J3[1][4] = WFM_J1_J2_J3[2][0];//AC49
     INV_OF_WFM_J1_J2_J3[0][5] = WFM_J1_J2_J3[1][1];//AD48
     INV_OF_WFM_J1_J2_J3[1][5] = WFM_J1_J2_J3[2][1];//AD49

     INV_OF_WFM_J1_J2_J3[2][0] = WFM_J1_J2_J3[0][1];//Y50
     INV_OF_WFM_J1_J2_J3[3][0] = WFM_J1_J2_J3[2][1];//Y51
     INV_OF_WFM_J1_J2_J3[2][1] = WFM_J1_J2_J3[0][2];//Z50
     INV_OF_WFM_J1_J2_J3[3][1] = WFM_J1_J2_J3[2][2];//Z51
     INV_OF_WFM_J1_J2_J3[2][2] = WFM_J1_J2_J3[0][0];//AA50
     INV_OF_WFM_J1_J2_J3[3][2] = WFM_J1_J2_J3[2][0];//AA51
     INV_OF_WFM_J1_J2_J3[2][3] = WFM_J1_J2_J3[0][2];//AB50
     INV_OF_WFM_J1_J2_J3[3][3] = WFM_J1_J2_J3[2][2];//AB51
     INV_OF_WFM_J1_J2_J3[2][4] = WFM_J1_J2_J3[0][0];//AC50
     INV_OF_WFM_J1_J2_J3[3][4] = WFM_J1_J2_J3[2][0];//AC51
     INV_OF_WFM_J1_J2_J3[2][5] = WFM_J1_J2_J3[0][1];//AD50
     INV_OF_WFM_J1_J2_J3[3][5] = WFM_J1_J2_J3[2][1];//AD51

     INV_OF_WFM_J1_J2_J3[4][0] = WFM_J1_J2_J3[0][1];//Y52
     INV_OF_WFM_J1_J2_J3[5][0] = WFM_J1_J2_J3[1][1];//Y53
     INV_OF_WFM_J1_J2_J3[4][1] = WFM_J1_J2_J3[0][2];//Z52
     INV_OF_WFM_J1_J2_J3[5][1] = WFM_J1_J2_J3[1][2];//Z53
     INV_OF_WFM_J1_J2_J3[4][2] = WFM_J1_J2_J3[0][0];//AA52
     INV_OF_WFM_J1_J2_J3[5][2] = WFM_J1_J2_J3[1][0];//AA53
     INV_OF_WFM_J1_J2_J3[4][3] = WFM_J1_J2_J3[0][2];//AB52
     INV_OF_WFM_J1_J2_J3[5][3] = WFM_J1_J2_J3[1][2];//AB53
     INV_OF_WFM_J1_J2_J3[4][4] = WFM_J1_J2_J3[0][0];//AC52
     INV_OF_WFM_J1_J2_J3[5][4] = WFM_J1_J2_J3[1][0];//AC53
     INV_OF_WFM_J1_J2_J3[4][5] = WFM_J1_J2_J3[0][1];//AD52
     INV_OF_WFM_J1_J2_J3[5][5] = WFM_J1_J2_J3[1][1];//AD53

     //minors determinant
     Minor_Determinant[0][0] = (INV_OF_WFM_J1_J2_J3[0][0] * INV_OF_WFM_J1_J2_J3[1][1]) - (INV_OF_WFM_J1_J2_J3[1][0] * INV_OF_WFM_J1_J2_J3[0][1]);
     Minor_Determinant[1][0] = (INV_OF_WFM_J1_J2_J3[2][0] * INV_OF_WFM_J1_J2_J3[3][1]) - (INV_OF_WFM_J1_J2_J3[3][0] * INV_OF_WFM_J1_J2_J3[2][1]);
     Minor_Determinant[2][0] = (INV_OF_WFM_J1_J2_J3[4][0] * INV_OF_WFM_J1_J2_J3[5][1]) - (INV_OF_WFM_J1_J2_J3[5][0] * INV_OF_WFM_J1_J2_J3[4][1]);
     Minor_Determinant[0][1] = (INV_OF_WFM_J1_J2_J3[0][2] * INV_OF_WFM_J1_J2_J3[1][3]) - (INV_OF_WFM_J1_J2_J3[1][2] * INV_OF_WFM_J1_J2_J3[0][3]);
     Minor_Determinant[1][1] = (INV_OF_WFM_J1_J2_J3[2][2] * INV_OF_WFM_J1_J2_J3[3][3]) - (INV_OF_WFM_J1_J2_J3[3][2] * INV_OF_WFM_J1_J2_J3[2][3]);
     Minor_Determinant[2][1] = (INV_OF_WFM_J1_J2_J3[4][2] * INV_OF_WFM_J1_J2_J3[5][3]) - (INV_OF_WFM_J1_J2_J3[5][2] * INV_OF_WFM_J1_J2_J3[4][3]);
     Minor_Determinant[0][2] = (INV_OF_WFM_J1_J2_J3[0][4] * INV_OF_WFM_J1_J2_J3[1][5]) - (INV_OF_WFM_J1_J2_J3[1][4] * INV_OF_WFM_J1_J2_J3[0][5]);
     Minor_Determinant[1][2] = (INV_OF_WFM_J1_J2_J3[2][4] * INV_OF_WFM_J1_J2_J3[3][5]) - (INV_OF_WFM_J1_J2_J3[3][4] * INV_OF_WFM_J1_J2_J3[2][5]);
     Minor_Determinant[2][2] = (INV_OF_WFM_J1_J2_J3[4][4] * INV_OF_WFM_J1_J2_J3[5][5]) - (INV_OF_WFM_J1_J2_J3[5][4] * INV_OF_WFM_J1_J2_J3[4][5]);
   

     //cofactors
     Cofactors[0][0] = 1;
     Cofactors[1][0] = -1;
     Cofactors[2][0] = 1;
     Cofactors[0][1] = -1;
     Cofactors[1][1] = 1;
     Cofactors[2][1] = -1;
     Cofactors[0][2] = 1;
     Cofactors[1][2] = -1;
     Cofactors[2][2] = 1;

     //cofactors*determinant 
     Cofactors_Mult_Determinant[0][0] = Minor_Determinant[0][0] * Cofactors[0][0];
     Cofactors_Mult_Determinant[1][0] = Minor_Determinant[1][0] * Cofactors[1][0];
     Cofactors_Mult_Determinant[2][0] = Minor_Determinant[2][0] * Cofactors[2][0];
     Cofactors_Mult_Determinant[0][1] = Minor_Determinant[0][1] * Cofactors[0][1];
     Cofactors_Mult_Determinant[1][1] = Minor_Determinant[1][1] * Cofactors[1][1];
     Cofactors_Mult_Determinant[2][1] = Minor_Determinant[2][1] * Cofactors[2][1];
     Cofactors_Mult_Determinant[0][2] = Minor_Determinant[0][2] * Cofactors[0][2];
     Cofactors_Mult_Determinant[1][2] = Minor_Determinant[1][2] * Cofactors[1][2];
     Cofactors_Mult_Determinant[2][2] = Minor_Determinant[2][2] * Cofactors[2][2];
   
     //ADJUGATE MATRIX
     Adjugate_Matrix[0][0] = Cofactors_Mult_Determinant[0][0];
     Adjugate_Matrix[1][0] = Cofactors_Mult_Determinant[0][1];
     Adjugate_Matrix[2][0] = Cofactors_Mult_Determinant[0][2];
     Adjugate_Matrix[0][1] = Cofactors_Mult_Determinant[1][0];
     Adjugate_Matrix[1][1] = Cofactors_Mult_Determinant[1][1];
     Adjugate_Matrix[2][1] = Cofactors_Mult_Determinant[1][2];
     Adjugate_Matrix[0][2] = Cofactors_Mult_Determinant[2][0];
     Adjugate_Matrix[1][2] = Cofactors_Mult_Determinant[2][1];
     Adjugate_Matrix[2][2] = Cofactors_Mult_Determinant[2][2];
  

     Determinant = (WFM_J1_J2_J3[0][0] * Cofactors_Mult_Determinant[0][0]) + (WFM_J1_J2_J3[0][1] * Cofactors_Mult_Determinant[0][1]) + (WFM_J1_J2_J3[0][2] * Cofactors_Mult_Determinant[0][2]);


     //inverse (WF*J1*J2)*J3 
     Inverse_WFM_J1_J2_J3[0][0] = 1 / Determinant * Adjugate_Matrix[0][0];
     Inverse_WFM_J1_J2_J3[1][0] = 1 / Determinant * Adjugate_Matrix[1][0];
     Inverse_WFM_J1_J2_J3[2][0] = 1 / Determinant * Adjugate_Matrix[2][0];
     Inverse_WFM_J1_J2_J3[0][1] = 1 / Determinant * Adjugate_Matrix[0][1];
     Inverse_WFM_J1_J2_J3[1][1] = 1 / Determinant * Adjugate_Matrix[1][1];
     Inverse_WFM_J1_J2_J3[2][1] = 1 / Determinant * Adjugate_Matrix[2][1];
     Inverse_WFM_J1_J2_J3[0][2] = 1 / Determinant * Adjugate_Matrix[0][2];
     Inverse_WFM_J1_J2_J3[1][2] = 1 / Determinant * Adjugate_Matrix[1][2];
     Inverse_WFM_J1_J2_J3[2][2] = 1 / Determinant * Adjugate_Matrix[2][2];
   

     //Z change
     Z_Change[0][0] = cos(angTorad(NewCoord.roll));
     Z_Change[1][0] = sin(angTorad(NewCoord.roll));
     Z_Change[2][0] = 0;
     Z_Change[0][1] = -sin(angTorad(NewCoord.roll));
     Z_Change[1][1] = cos(angTorad(NewCoord.roll));
     Z_Change[2][1] = 0;
     Z_Change[0][2] = 0;
     Z_Change[1][2] = 0;
     Z_Change[2][2] = 1;

     //Y change
     Y_Change[0][0] = cos(angTorad(NewCoord.pitch));
     Y_Change[1][0] = 0;
     Y_Change[2][0] = -sin(angTorad(NewCoord.pitch));
     Y_Change[0][1] = 0;
     Y_Change[1][1] = 1;
     Y_Change[2][1] = 0;
     Y_Change[0][2] = sin(angTorad(NewCoord.pitch));
     Y_Change[1][2] = 0;
     Y_Change[2][2] = cos(angTorad(NewCoord.pitch));

     //X change
     X_Change[0][0] = 1;
     X_Change[1][0] = 0;
     X_Change[2][0] = 0;
     X_Change[0][1] = 0;
     X_Change[1][1] = cos(angTorad(NewCoord.yaw));
     X_Change[2][1] = sin(angTorad(NewCoord.yaw));
     X_Change[0][2] = 0;
     X_Change[1][2] = -sin(angTorad(NewCoord.yaw));
     X_Change[2][2] = cos(angTorad(NewCoord.yaw));

     //Current R 0-T
     Current_R0T[0][0] = TT[0][0];
     Current_R0T[1][0] = TT[1][0];
     Current_R0T[2][0] = TT[2][0];
     Current_R0T[0][1] = TT[0][1];
     Current_R0T[1][1] = TT[1][1];
     Current_R0T[2][1] = TT[2][1];
     Current_R0T[0][2] = TT[0][2];
     Current_R0T[1][2] = TT[1][2];
     Current_R0T[2][2] = TT[2][2];

     //Z*Y
     Z_MULT_Y[0][0] = (Z_Change[0][0] * Y_Change[0][0]) + (Z_Change[0][1] * Y_Change[1][0]) + (Z_Change[0][2] * Y_Change[2][0]);
     Z_MULT_Y[1][0] = (Z_Change[1][0] * Y_Change[0][0]) + (Z_Change[1][1] * Y_Change[1][0]) + (Z_Change[1][2] * Y_Change[2][0]);
     Z_MULT_Y[2][0] = (Z_Change[2][0] * Y_Change[0][0]) + (Z_Change[2][1] * Y_Change[1][0]) + (Z_Change[2][2] * Y_Change[2][0]);
     Z_MULT_Y[0][1] = (Z_Change[0][0] * Y_Change[0][1]) + (Z_Change[0][1] * Y_Change[1][1]) + (Z_Change[0][2] * Y_Change[2][1]);
     Z_MULT_Y[1][1] = (Z_Change[1][0] * Y_Change[0][1]) + (Z_Change[1][1] * Y_Change[1][1]) + (Z_Change[1][2] * Y_Change[2][1]);
     Z_MULT_Y[2][1] = (Z_Change[2][0] * Y_Change[0][1]) + (Z_Change[2][1] * Y_Change[1][1]) + (Z_Change[2][2] * Y_Change[2][1]);
     Z_MULT_Y[0][2] = (Z_Change[0][0] * Y_Change[0][2]) + (Z_Change[0][1] * Y_Change[1][2]) + (Z_Change[0][2] * Y_Change[2][2]);
     Z_MULT_Y[1][2] = (Z_Change[1][0] * Y_Change[0][2]) + (Z_Change[1][1] * Y_Change[1][2]) + (Z_Change[1][2] * Y_Change[2][2]);
     Z_MULT_Y[2][2] = (Z_Change[2][0] * Y_Change[0][2]) + (Z_Change[2][1] * Y_Change[1][2]) + (Z_Change[2][2] * Y_Change[2][2]);

     //Z*Y*X
     Z_MULT_Y_MULTX[0][0] = (Z_MULT_Y[0][0] * X_Change[0][0]) + (Z_MULT_Y[0][1] * X_Change[1][0]) + (Z_MULT_Y[0][2] * X_Change[2][0]);
     Z_MULT_Y_MULTX[1][0] = (Z_MULT_Y[1][0] * X_Change[0][0]) + (Z_MULT_Y[1][1] * X_Change[1][0]) + (Z_MULT_Y[1][2] * X_Change[2][0]);
     Z_MULT_Y_MULTX[2][0] = (Z_MULT_Y[2][0] * X_Change[0][0]) + (Z_MULT_Y[2][1] * X_Change[1][0]) + (Z_MULT_Y[2][2] * X_Change[2][0]);
     Z_MULT_Y_MULTX[0][1] = (Z_MULT_Y[0][0] * X_Change[0][1]) + (Z_MULT_Y[0][1] * X_Change[1][1]) + (Z_MULT_Y[0][2] * X_Change[2][1]);
     Z_MULT_Y_MULTX[1][1] = (Z_MULT_Y[1][0] * X_Change[0][1]) + (Z_MULT_Y[1][1] * X_Change[1][1]) + (Z_MULT_Y[1][2] * X_Change[2][1]);
     Z_MULT_Y_MULTX[2][1] = (Z_MULT_Y[2][0] * X_Change[0][1]) + (Z_MULT_Y[2][1] * X_Change[1][1]) + (Z_MULT_Y[2][2] * X_Change[2][1]);
     Z_MULT_Y_MULTX[0][2] = (Z_MULT_Y[0][0] * X_Change[0][2]) + (Z_MULT_Y[0][1] * X_Change[1][2]) + (Z_MULT_Y[0][2] * X_Change[2][2]);
     Z_MULT_Y_MULTX[1][2] = (Z_MULT_Y[1][0] * X_Change[0][2]) + (Z_MULT_Y[1][1] * X_Change[1][2]) + (Z_MULT_Y[1][2] * X_Change[2][2]);
     Z_MULT_Y_MULTX[2][2] = (Z_MULT_Y[2][0] * X_Change[0][2]) + (Z_MULT_Y[2][1] * X_Change[1][2]) + (Z_MULT_Y[2][2] * X_Change[2][2]);

     //Z*Y*X**0-T
     Z_MULT_Y_MULTX_0T[0][0] = (Z_MULT_Y_MULTX[0][0] * Current_R0T[0][0]) + (Z_MULT_Y_MULTX[0][1] * Current_R0T[1][0]) + (Z_MULT_Y_MULTX[0][2] * Current_R0T[2][0]);
     Z_MULT_Y_MULTX_0T[1][0] = (Z_MULT_Y_MULTX[1][0] * Current_R0T[0][0]) + (Z_MULT_Y_MULTX[1][1] * Current_R0T[1][0]) + (Z_MULT_Y_MULTX[1][2] * Current_R0T[2][0]);
     Z_MULT_Y_MULTX_0T[2][0] = (Z_MULT_Y_MULTX[2][0] * Current_R0T[0][0]) + (Z_MULT_Y_MULTX[2][1] * Current_R0T[1][0]) + (Z_MULT_Y_MULTX[2][2] * Current_R0T[2][0]);
     Z_MULT_Y_MULTX_0T[0][1] = (Z_MULT_Y_MULTX[0][0] * Current_R0T[0][1]) + (Z_MULT_Y_MULTX[0][1] * Current_R0T[1][1]) + (Z_MULT_Y_MULTX[0][2] * Current_R0T[2][1]);
     Z_MULT_Y_MULTX_0T[1][1] = (Z_MULT_Y_MULTX[1][0] * Current_R0T[0][1]) + (Z_MULT_Y_MULTX[1][1] * Current_R0T[1][1]) + (Z_MULT_Y_MULTX[1][2] * Current_R0T[2][1]);
     Z_MULT_Y_MULTX_0T[2][1] = (Z_MULT_Y_MULTX[2][0] * Current_R0T[0][1]) + (Z_MULT_Y_MULTX[2][1] * Current_R0T[1][1]) + (Z_MULT_Y_MULTX[2][2] * Current_R0T[2][1]);
     Z_MULT_Y_MULTX_0T[0][2] = (Z_MULT_Y_MULTX[0][0] * Current_R0T[0][2]) + (Z_MULT_Y_MULTX[0][1] * Current_R0T[1][2]) + (Z_MULT_Y_MULTX[0][2] * Current_R0T[2][2]);
     Z_MULT_Y_MULTX_0T[1][2] = (Z_MULT_Y_MULTX[1][0] * Current_R0T[0][2]) + (Z_MULT_Y_MULTX[1][1] * Current_R0T[1][2]) + (Z_MULT_Y_MULTX[1][2] * Current_R0T[2][2]);
     Z_MULT_Y_MULTX_0T[2][2] = (Z_MULT_Y_MULTX[2][0] * Current_R0T[0][2]) + (Z_MULT_Y_MULTX[2][1] * Current_R0T[1][2]) + (Z_MULT_Y_MULTX[2][2] * Current_R0T[2][2]);
  
     //R,3-6
     R_3_6[0][0] = (Inverse_WFM_J1_J2_J3[0][0] * Z_MULT_Y_MULTX_0T[0][0]) + (Inverse_WFM_J1_J2_J3[0][1] * Z_MULT_Y_MULTX_0T[1][0]) + (Inverse_WFM_J1_J2_J3[0][2] * Z_MULT_Y_MULTX_0T[2][0]);
     R_3_6[1][0] = (Inverse_WFM_J1_J2_J3[1][0] * Z_MULT_Y_MULTX_0T[0][0]) + (Inverse_WFM_J1_J2_J3[1][1] * Z_MULT_Y_MULTX_0T[1][0]) + (Inverse_WFM_J1_J2_J3[1][2] * Z_MULT_Y_MULTX_0T[2][0]);
     R_3_6[2][0] = (Inverse_WFM_J1_J2_J3[2][0] * Z_MULT_Y_MULTX_0T[0][0]) + (Inverse_WFM_J1_J2_J3[2][1] * Z_MULT_Y_MULTX_0T[1][0]) + (Inverse_WFM_J1_J2_J3[2][2] * Z_MULT_Y_MULTX_0T[2][0]);
     R_3_6[0][1] = (Inverse_WFM_J1_J2_J3[0][0] * Z_MULT_Y_MULTX_0T[0][1]) + (Inverse_WFM_J1_J2_J3[0][1] * Z_MULT_Y_MULTX_0T[1][1]) + (Inverse_WFM_J1_J2_J3[0][2] * Z_MULT_Y_MULTX_0T[2][1]);
     R_3_6[1][1] = (Inverse_WFM_J1_J2_J3[1][0] * Z_MULT_Y_MULTX_0T[0][1]) + (Inverse_WFM_J1_J2_J3[1][1] * Z_MULT_Y_MULTX_0T[1][1]) + (Inverse_WFM_J1_J2_J3[1][2] * Z_MULT_Y_MULTX_0T[2][1]);
     R_3_6[2][1] = (Inverse_WFM_J1_J2_J3[2][0] * Z_MULT_Y_MULTX_0T[0][1]) + (Inverse_WFM_J1_J2_J3[2][1] * Z_MULT_Y_MULTX_0T[1][1]) + (Inverse_WFM_J1_J2_J3[2][2] * Z_MULT_Y_MULTX_0T[2][1]);
     R_3_6[0][2] = (Inverse_WFM_J1_J2_J3[0][0] * Z_MULT_Y_MULTX_0T[0][2]) + (Inverse_WFM_J1_J2_J3[0][1] * Z_MULT_Y_MULTX_0T[1][2]) + (Inverse_WFM_J1_J2_J3[0][2] * Z_MULT_Y_MULTX_0T[2][2]);
     R_3_6[1][2] = (Inverse_WFM_J1_J2_J3[1][0] * Z_MULT_Y_MULTX_0T[0][2]) + (Inverse_WFM_J1_J2_J3[1][1] * Z_MULT_Y_MULTX_0T[1][2]) + (Inverse_WFM_J1_J2_J3[1][2] * Z_MULT_Y_MULTX_0T[2][2]);
     R_3_6[2][2] = (Inverse_WFM_J1_J2_J3[2][0] * Z_MULT_Y_MULTX_0T[0][2]) + (Inverse_WFM_J1_J2_J3[2][1] * Z_MULT_Y_MULTX_0T[1][2]) + (Inverse_WFM_J1_J2_J3[2][2] * Z_MULT_Y_MULTX_0T[2][2]);

     //calc 456

     test = R_3_6[2][2];
     test2 = sqrt(abs(1 - pow(R_3_6[2][2],2)));
     A4 = radToang(atan2(R_3_6[1][2], R_3_6[0][2]));
     A5 = radToang(atan2(sqrt(abs(1-pow(R_3_6[2][2], 2))), R_3_6[2][2]));

     if (R_3_6[2][1] < 0)
     {
         A6 = radToang(atan2(R_3_6[2][1], -R_3_6[2][0])) + 180;//R9
         A6_2 = radToang(atan2(-R_3_6[2][1], R_3_6[2][0])) - 180;//S9
     }
     else
     {
         A6 = radToang(atan2(R_3_6[2][1], -R_3_6[2][0])) - 180;
         A6_2 = radToang(atan2(-R_3_6[2][1], R_3_6[2][0])) + 180;
     }
     A4_2 = radToang(atan2(-R_3_6[1][2], -R_3_6[0][2]));
     A5_2 = radToang(atan2(-sqrt(abs(1 - pow(R_3_6[2][2], 2))), R_3_6[2][2]));

     if(anglesAct[4] > 0 && A5 > 0)
     {
         Join.J5 = A5;
     }else
     {
         Join.J5 = A5_2;
     }
     if (Join.J5 > 0)
     {
         Join.J4 = A4;
     }
     else
     {
         Join.J4 = A4_2;
     }
     if (Join.J5 < 0)
     {
         Join.J6 = A6_2;
     }
     else
     {
         Join.J6 = A6;
     }
 }
