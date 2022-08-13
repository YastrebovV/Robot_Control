#include "executionprogram.h"

ExecutionProgram::ExecutionProgram(QObject *parent) : QObject(parent)
{

}

void ExecutionProgram::run()
{
    std::vector<std::vector<double>> TT;
    std::vector<std::vector<double>> T5;
    std::vector<double> ActCoordNew;
    std::vector<double> JoinNew;
    std::vector<std::vector<QString>> textProgram = appCore.getTextProgram();
    std::vector<std::vector<double>> dataProgram = appCore.getDataProgram();

    ActCoordNew.resize(6);

    for(unsigned i = 0; i < textProgram.size(); ++i)
    {
        if(textProgram[i][1] == "PTP" || textProgram[i][1] == "LIN")
            for(unsigned j = 0; j < 6; ++j)
                ActCoordNew[j] = robotControl.getActCoord()[j] - dataProgram[i][j];

         if(textProgram[i][1] == "Wait sec"){
             QThread::sleep(textProgram[i][2].toULong());
             continue;
         }

        kinematics.invKinematics(robotControl.getActCoord(), ActCoordNew, robotControl.getDH_Param(), robotControl.getWFrame(), TT, robotControl.getAngelAct(), JoinNew);

        JoinNew[2] = JoinNew[2] - 90;
        JoinNew[5] = JoinNew[5] + 180;
        robotControl.JointMove(robotControl.getAngelAct(), JoinNew);

        //Ожидание окончания перемещения.
        while (ethercatRT->getSteps(0) > 0 && ethercatRT->getSteps(1) > 0 && ethercatRT->getSteps(2) > 0
               && ethercatRT->getSteps(3) > 0 && ethercatRT->getSteps(4) > 0 && ethercatRT->getSteps(5) > 0) {

        }
    }

    emit finished();
}

void ExecutionProgram::settingThread(QThread &exeProgramThread, ExecutionProgram &objProgram)
{
    // Запуск выполнения метода run будет осуществляться по сигналу запуска от соответствующего потока
    connect(&exeProgramThread, &QThread::started, &objProgram, &ExecutionProgram::run);
    // Остановка потока же будет выполняться по сигналу finished от соответствующего объекта в потоке
    connect(&objProgram, &ExecutionProgram::finished, &exeProgramThread, &QThread::terminate);

    objProgram.moveToThread(&exeProgramThread);    // Передаём объекты в соответствующие потоки
}
