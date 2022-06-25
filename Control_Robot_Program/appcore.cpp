#include "appcore.h"

AppCore::AppCore(QObject *parent) : QObject(parent)
{
    ethercatRT->rt_ethercat_start();
}

void AppCore::createFile(QString fileName, QString path)
{
    //FilesAndFolders_C.createFile(fileName, text);
   domDoc = programcodeXML_C.createDomDoc(fileName);
   writeToFile(fileName+".xml", path);

}

void AppCore::openFile(QString fileName, QString path)
{
    QFile  file(path+"/"+fileName);

    if(file.open(QIODevice::ReadOnly)) {
        if(domDoc.setContent(&file)) {
            QDomElement domElement= domDoc.documentElement();
            QDomNodeList nodes = domDoc.elementsByTagName("point");
            textProgram.resize(nodes.count());
            dataProgram.resize(nodes.count());
            for(unsigned int i=0; i<nodes.count(); i++){
               textProgram[i].resize(4);
               dataProgram[i].resize(6);
            }
            programcodeXML_C.traverseNode(domElement, textProgram, dataProgram, -1, 1);

            emit clearListMode();
            for(unsigned int i=0; i<textProgram.size(); i++)
                    emit insertToListMode(textProgram[i][0], textProgram[i][2], textProgram[i][3]);
        }
        file.close();
    }
}

void AppCore::deleteFile(QString fileName, QString path)
{
    FilesAndFolders_C.deleteFile(path+"/"+fileName);
}
void AppCore::writeToFile(const QString& fileName,
                          const QString& path)
{
    QFile file(path+"/"+fileName);
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream(&file) << domDoc.toString();
        file.close();
    }
}

void AppCore::writeLineToFile(QString fileName,
                          QString path,
                          QString type,
                          QString name,
                          QString tool,
                          QString base,
                          QString id)
{
    QDomElement domElement= domDoc.documentElement();
    programcodeXML_C.writeToDomDoc(domDoc, type, name, tool, base, id);

    QFile file(path+"/"+fileName);
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream(&file) << domDoc.toString();
        file.close();
    }
}

void AppCore::changeLineInFile(QString fileName,
                                QString path,
                                QString type,
                                QString newname,
                                QString oldname,
                                QString tool,
                                QString base)
{
    QDomElement domElement= domDoc.documentElement();

    programcodeXML_C.changeLineInDomDoc(domElement, type, newname, oldname, tool, base, textProgram, dataProgram, -1, 1);
    writeToFile(fileName, path);
}

void AppCore::deleteLineFromFile(QString fileName,
                                 QString path,
                                 QString name)
{
    QDomElement domElement= domDoc.documentElement();
    programcodeXML_C.deleteNode(domElement, name);
    writeToFile(fileName, path);
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
    std::vector<double> ActCoordNew;// = ActCoord;
    std::vector<double> Join = RobotControl_C.getAngelAct();
    std::vector<double> JoinNew;

    ActCoordNew.resize(8);
    Join[2] = Join[2] - 90;
    Join[5] = Join[5] + 180;
    JoinNew = Join;

    Kinematics_C.dirKinematics(Join, WFrame, TFrame, DH_Param, ActCoord, T5, TT);

    switch (axis){
        case 1: ActCoordNew[0] = valueOffset; break;
        case 2: ActCoordNew[1] = valueOffset; break;
        case 3: ActCoordNew[2] = valueOffset; break;
        case 4: ActCoordNew[3] = valueOffset; break;
        case 5: ActCoordNew[4] = valueOffset; break;
        case 6: ActCoordNew[5] = valueOffset; break;
    }

    Kinematics_C.invKinematics(ActCoord, ActCoordNew, DH_Param, WFrame, TT, Join, JoinNew);

    JoinNew[2] = JoinNew[2] -90;
    JoinNew[5] = JoinNew[5] +180;
    RobotControl_C.JointMove(Join, JoinNew);
}
void AppCore::stopMove()
{
    RobotControl_C.RobotStop();
}

void AppCore::setSpeed(unsigned int speed)
{
   // unsigned long long temp = (15-speed/10)*100000;
    ethercatRT->setAxisSpeed(speed);
}
unsigned long long AppCore::getAxisSpeed()
{
   return ethercatRT->getAxisSpeed();
}

void AppCore::setAxisMastering(bool start)
{
    ethercatRT->setStartAxMastering(start);
}

