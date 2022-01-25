#include "appcore.h"

AppCore::AppCore(QObject *parent) : QObject(parent)
{

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
    vecStr.push_back(QString::number(RobotControl_C.getActCoord().x));
    vecStr.push_back(QString::number(RobotControl_C.getActCoord().y));
    vecStr.push_back(QString::number(RobotControl_C.getActCoord().z));
    vecStr.push_back(QString::number(RobotControl_C.getActCoord().pitch));
    vecStr.push_back(QString::number(RobotControl_C.getActCoord().roll));
    vecStr.push_back(QString::number(RobotControl_C.getActCoord().yaw));
    return vecStr;
}
std::vector<QString> AppCore::getActAngles()
{
    std::vector<QString> vecStr;
    vecStr.push_back(QString::number(RobotControl_C.getAngelAct().J1));
    vecStr.push_back(QString::number(RobotControl_C.getAngelAct().J2));
    vecStr.push_back(QString::number(RobotControl_C.getAngelAct().J3));
    vecStr.push_back(QString::number(RobotControl_C.getAngelAct().J4));
    vecStr.push_back(QString::number(RobotControl_C.getAngelAct().J5));
    vecStr.push_back(QString::number(RobotControl_C.getAngelAct().J6));
    return vecStr;
}
void AppCore::setActCoord(Kinematics::ActCoord ActCoord)
{
    RobotControl_C.setActCoord(ActCoord);
}

void AppCore::jointManMove(int numAxis, double valueOffset)
{
    Kinematics::Join Join = RobotControl_C.getAngelAct();
    Kinematics::Join JoinNew = Join;

    switch (numAxis){
        case 1: JoinNew.J1=Join.J1+valueOffset; break;
        case 2: JoinNew.J2=Join.J2+valueOffset; break;
        case 3: JoinNew.J3=Join.J3+valueOffset; break;
        case 4: JoinNew.J4=Join.J4+valueOffset; break;
        case 5: JoinNew.J5=Join.J5+valueOffset; break;
        case 6: JoinNew.J6=Join.J6+valueOffset; break;
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
    Kinematics::ActCoord ActCoord = RobotControl_C.getActCoord();
    Kinematics::ActCoord ActCoordNew = ActCoord;
    Kinematics::Join Join = RobotControl_C.getAngelAct();
    Kinematics::Join JoinNew = Join;

    Join.J3 = Join.J3 -90;
    Join.J6 = Join.J6 +180;
    JoinNew = Join;

    Kinematics_C.dirKinematics(Join, WFrame, TFrame, DH_Param, ActCoord, T5, TT);
    switch (axis){
        case 1: ActCoordNew.x = valueOffset; break;
        case 2: ActCoordNew.y = valueOffset; break;
        case 3: ActCoordNew.z = valueOffset; break;
        case 4: ActCoordNew.yaw = valueOffset; break;
        case 5: ActCoordNew.pitch = valueOffset; break;
        case 6: ActCoordNew.roll = valueOffset; break;
    }

    Kinematics_C.invKinematics(ActCoord, ActCoordNew, DH_Param, WFrame, TT, Join, JoinNew);

   //RobotControl_C.setActCoord(ActCoord);
  //  RobotControl_C.setJoin(JoinNew);

    RobotControl_C.JointMove(Join, JoinNew);
}
