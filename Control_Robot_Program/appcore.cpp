#include "appcore.h"

//using namespace std;

AppCore::AppCore(QObject *parent) : QObject(parent)
{

}

//void AppCore::receiveFromQml()
//{
//    count++;
//    emit sendToQml(count);
//}

//void AppCore::testMetod()
//{
//    count = 0;
//    emit sendToQml(count);
//}

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

void AppCore::setActCoord(Kinematics::ActCoord ActCoord)
{
    RobotControl_C.setActCoord(ActCoord);
}

void AppCore::jointManMove(char numAxis, double valueOffset)
{
    std::vector<double> AxisAnglAct = RobotControl_C.getAngelAct();
    std::vector<double> AxisAnglNew;

    AxisAnglNew = AxisAnglAct;

    switch (numAxis){
        case 1: AxisAnglNew[0]=AxisAnglAct[0]+valueOffset; break;
        case 2: AxisAnglNew[1]=AxisAnglAct[1]+valueOffset; break;
        case 3: AxisAnglNew[2]=AxisAnglAct[2]+valueOffset; break;
        case 4: AxisAnglNew[3]=AxisAnglAct[3]+valueOffset; break;
        case 5: AxisAnglNew[4]=AxisAnglAct[4]+valueOffset; break;
        case 6: AxisAnglNew[5]=AxisAnglAct[5]+valueOffset; break;
    }

    RobotControl_C.JointMove(AxisAnglAct, AxisAnglNew);
}
void AppCore::cartesianManMove(char axis, double valueOffset)
{
    std::vector<double> AxisAnglAct = RobotControl_C.getAngelAct();
    std::vector<double> WFrame = RobotControl_C.getWFrame();
    std::vector<double> TFrame = RobotControl_C.getTFrame();
    std::vector<std::vector<double>> DH_Param = RobotControl_C.getDH_Param();
    std::vector<std::vector<double>> TT = RobotControl_C.getTT();
    std::vector<std::vector<double>> T5 = RobotControl_C.getT5();;
    Kinematics::ActCoord ActCoord;

    AxisAnglAct[2] = AxisAnglAct[2] -90;
    AxisAnglAct[5] = AxisAnglAct[2] +180;

    Kinematics_C.dirKinematics(AxisAnglAct, WFrame, TFrame, DH_Param, ActCoord, T5, TT);

    RobotControl_C.setActCoord(ActCoord);
}
