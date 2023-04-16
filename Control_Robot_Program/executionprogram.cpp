#include "executionprogram.h"

ExecutionProgram::ExecutionProgram(QObject *parent) : QObject(parent)
{

}
void ExecutionProgram::setRobotData(const RobotControl & robotControl)
{
    this->robotControl = robotControl;
}

void ExecutionProgram::setProgram(const std::vector<std::vector<QString>> & textProgram, const std::vector<std::vector<double>> & dataProgram)
{
    this->textProgram = textProgram;
    this->dataProgram = dataProgram;
}

void ExecutionProgram::run()
{
    int countTemp = 0;
    for(unsigned i = 0; i < textProgram.size(); ++i)
    {
         if(textProgram[i][1] == "Wait sec"){
             QThread::sleep(textProgram[i][0].toULong());
             continue;
         }

        robotControl.executionProgram(dataProgram[i]);

        qDebug() << ethercatRT->getSteps(1) << endl;

        //Ожидание окончания перемещения.
        while (ethercatRT->getRobotMoving()) {};

        robotControl.RobotStop();
        countTemp++;
    }
    qDebug() << countTemp << endl;

    emit finished();
}
