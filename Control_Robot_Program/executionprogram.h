#ifndef EXECUTIONPROGRAM_H
#define EXECUTIONPROGRAM_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include "kinematics.h"
#include "rt_ethercat.h"
#include "robotcontrol.h"

class ExecutionProgram : public QObject
{
    Q_OBJECT

public:
    explicit ExecutionProgram(QObject *parent = nullptr);
    void setRobotData(const RobotControl & robotControl);
    void setProgram(const std::vector<std::vector<QString>> & textProgram, const std::vector<std::vector<double>> & dataProgram);

signals:
    void finished();    // Сигнал, по которому будем завершать поток, после завершения метода run

public slots:
    void run(); // Метод с полезной нагрузкой, который может выполняться в цикле

private:
   RobotControl robotControl;
   Kinematics kinematics;
   rt_ethercat *ethercatRT;
   std::vector<std::vector<QString>> textProgram;
   std::vector<std::vector<double>> dataProgram;

};

#endif // EXECUTIONPROGRAM_H
