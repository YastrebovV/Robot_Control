#include "appcore.h"

AppCore::AppCore(QObject *parent) : QObject(parent)
{
    ethercatRT->rt_ethercat_start();
}

void AppCore::createFile(QString fileName, QString text)
{
    FilesAndFolders_C.createFile(fileName, text);
}

void AppCore::deleteFile(QString fileName)
{
    FilesAndFolders_C.deleteFile(fileName);
}

void AppCore::writeToFile(QString fileName, QString text)
{
    FilesAndFolders_C.writeToFile(fileName, text);
}

QString AppCore::readFromFile(QString fileName)
{
   return FilesAndFolders_C.readFromFile(fileName);
}

std::vector<QString> AppCore::getActCoord()
{
    std::vector<QString> vecStr;
    std::vector<double> actCoord = RobotControl_C.getActCoord();
    vecStr.push_back(QString::number(actCoord[0]));
    vecStr.push_back(QString::number(actCoord[1]));
    vecStr.push_back(QString::number(actCoord[2]));
    vecStr.push_back(QString::number(actCoord[4]));
    vecStr.push_back(QString::number(actCoord[5]));
    vecStr.push_back(QString::number(actCoord[3]));
    return vecStr;
}
std::vector<QString> AppCore::getActAngles()
{
    std::vector<QString> vecStr;
    vecStr.push_back(QString::number(RobotControl_C.getAngelAct()[0]));
    vecStr.push_back(QString::number(RobotControl_C.getAngelAct()[1]));
    vecStr.push_back(QString::number(RobotControl_C.getAngelAct()[2]));
    vecStr.push_back(QString::number(RobotControl_C.getAngelAct()[3]));
    vecStr.push_back(QString::number(RobotControl_C.getAngelAct()[4]));
    vecStr.push_back(QString::number(RobotControl_C.getAngelAct()[5]));
    return vecStr;
}
void AppCore::setActCoord(std::vector<double> ActCoord)
{
    RobotControl_C.setActCoord(ActCoord);
}

void AppCore::jointManMove(int numAxis, double valueOffset)
{
    std::vector<double> Join = RobotControl_C.getAngelAct();
    std::vector<double> JoinNew = Join;

    switch (numAxis){
        case 1: JoinNew[0]=Join[0]+valueOffset; break;
        case 2: JoinNew[1]=Join[1]+valueOffset; break;
        case 3: JoinNew[2]=Join[2]+valueOffset; break;
        case 4: JoinNew[3]=Join[3]+valueOffset; break;
        case 5: JoinNew[4]=Join[4]+valueOffset; break;
        case 6: JoinNew[5]=Join[5]+valueOffset; break;
    }

    RobotControl_C.JointMove(Join, JoinNew);
}
void AppCore::cartesianManMove(int axis, double valueOffset)
{
    std::vector<double> WFrame = RobotControl_C.getWFrame();
    std::vector<double> TFrame = RobotControl_C.getTFrame();
    std::vector<std::vector<double>> DH_Param = RobotControl_C.getDH_Param();
    std::vector<std::vector<double>> TT = RobotControl_C.getTT();
    std::vector<std::vector<double>> T5 = RobotControl_C.getT5();;
    std::vector<double> ActCoord = RobotControl_C.getActCoord();
    std::vector<double> ActCoordNew = ActCoord;
    std::vector<double> Join = RobotControl_C.getAngelAct();
    std::vector<double> JoinNew;

    Join[2] = Join[2] -90;
    Join[5] = Join[5] +180;
    JoinNew = Join;

    Kinematics_C.dirKinematics(Join, WFrame, TFrame, DH_Param, ActCoord, T5, TT);

    switch (axis){
        case 1: ActCoordNew[0] += valueOffset; break;
        case 2: ActCoordNew[1] += valueOffset; break;
        case 3: ActCoordNew[2] += valueOffset; break;
        case 4: ActCoordNew[3] += valueOffset; break;
        case 5: ActCoordNew[4] += valueOffset; break;
        case 6: ActCoordNew[5] += valueOffset; break;
    }

    Kinematics_C.invKinematics(ActCoord, ActCoordNew, DH_Param, WFrame, TT, Join, JoinNew);

   //RobotControl_C.setActCoord(ActCoord);
  //  RobotControl_C.setJoin(JoinNew);
    JoinNew[2] = JoinNew[2] -90;
    JoinNew[5] = JoinNew[5] +180;
    RobotControl_C.JointMove(Join, JoinNew);
}
void AppCore::stopMove()
{
    RobotControl_C.RobotStop();
}
