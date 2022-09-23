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
    for(unsigned i = 0; i < textProgram.size(); ++i)
    {
         if(textProgram[i][1] == "Wait sec"){
             QThread::sleep(textProgram[i][0].toULong());
             continue;
         }

        robotControl.executionProgram(dataProgram[i]);

        //Ожидание окончания перемещения.
        while (ethercatRT->getSteps(0) > 0 && ethercatRT->getSteps(1) > 0 && ethercatRT->getSteps(2) > 0
               && ethercatRT->getSteps(3) > 0 && ethercatRT->getSteps(4) > 0 && ethercatRT->getSteps(5) > 0) {

        }
        robotControl.RobotStop();
    }

    emit finished();
}
