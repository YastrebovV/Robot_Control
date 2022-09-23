#include "appcore.h"

AppCore::AppCore(QObject *parent) : QObject(parent)
{
    ethercatRT->rt_ethercat_start();
}

void AppCore::resizeVector2(const std::size_t& numRow, const std::size_t& colsRow, std::vector<std::vector<QString>>& vector)
{
    vector.resize(numRow);

    for(unsigned int i=0; i < numRow; i++)
       vector[i].resize(colsRow);
}
void AppCore::resizeVector2(const std::size_t& numRow, const std::size_t& colsRow, std::vector<std::vector<double>>& vector)
{
    vector.resize(numRow);

    for(unsigned int i=0; i < numRow; i++)
       vector[i].resize(colsRow);
}

void AppCore::createFile(QString fileName, QString path)
{
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

            resizeVector2(static_cast<std::size_t>(nodes.count()), 4, textProgram);
            resizeVector2(static_cast<std::size_t>(nodes.count()), 6, dataProgram);

            programcodeXML_C.getDataFromDom(domElement, textProgram, dataProgram);

            emit clearListMode();
            for(unsigned int i=0; i<textProgram.size(); i++)
                    emit insertToListMode(textProgram[i][0], textProgram[i][1], textProgram[i][2], textProgram[i][3]);
        }
        file.close();
    }
}

void AppCore::deleteFile(QString fileName, QString path)
{
    QFile file(path+"/"+fileName);
    file.close();
    file.remove();
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
    programcodeXML_C.writeToDomDoc(domDoc, type, name, tool, base, id, RobotControl_C.getActCoord());

    writeToFile(fileName, path);
    openFile(fileName, path);
}

void AppCore::changeLineInFile(QString fileName,
                                QString path,
                                QString type,
                                QString newname,
                                QString oldname,
                                QString tool,
                                QString base,
                                QString id,
                                bool newPos)
{
    QDomElement domElement= domDoc.documentElement();
    std::vector<double> actPos;

    if(newPos)
        actPos = RobotControl_C.getActCoord();

    programcodeXML_C.changeLineInDomDoc(domElement, type, newname, oldname, tool, base, id, actPos);
    writeToFile(fileName, path);
    openFile(fileName, path);
}

void AppCore::deleteLineFromFile(QString fileName,
                                 QString path,
                                 QString name,
                                 QString id)
{
    QDomElement domElement= domDoc.documentElement();
    programcodeXML_C.deleteNode(domElement, name, id);
    programcodeXML_C.changeIdWhenDelLine(domElement, id);
    writeToFile(fileName, path);
    openFile(fileName, path);
}
//Старт потока, в котором будет выполняться программа робота
void AppCore::startProgram(){
    // Запуск выполнения метода run будет осуществляться по сигналу запуска от соответствующего потока
    connect(&exeProgramThread, &QThread::started, &executionProgram, &ExecutionProgram::run);
    //Остановка потока же будет выполняться по сигналу finished от соответствующего объекта в потоке
    connect(&executionProgram, &ExecutionProgram::finished, &exeProgramThread, &QThread::terminate);

    executionProgram.moveToThread(&exeProgramThread);    // Передаём объекты в соответствующие потоки

    executionProgram.setRobotData(RobotControl_C);
    executionProgram.setProgram(textProgram, dataProgram);

    exeProgramThread.start();
}

void AppCore::stopProgram(){
    if(exeProgramThread.isRunning())
        exeProgramThread.quit();
}

std::vector<QString> AppCore::getActCoord()
{
    std::vector<QString> vecStr;
    std::vector<double> actCoord = RobotControl_C.getActCoord();

    for(unsigned i = 0; i < 6; ++i)
         vecStr.push_back(QString::number(actCoord[i]));

    return vecStr;
}
std::vector<QString> AppCore::getActAngles()
{
    std::vector<QString> vecStr;
    for(unsigned i = 0; i < 6; ++i)
        vecStr.push_back(QString::number(RobotControl_C.getAngelAct()[i]));

    return vecStr;
}
void AppCore::setActCoord(std::vector<double> ActCoord)
{
    RobotControl_C.setActCoord(ActCoord);
}

void AppCore::jointManMove(int numAxis, double valueOffset)
{
    RobotControl_C.jointManMove(numAxis, valueOffset);
}
void AppCore::cartesianManMove(int axis, double valueOffset)
{
    RobotControl_C.cartesianManMove(axis, valueOffset);
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

