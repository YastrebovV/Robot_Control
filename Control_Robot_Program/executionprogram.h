#ifndef EXECUTIONPROGRAM_H
#define EXECUTIONPROGRAM_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include "appcore.h"

class ExecutionProgram : public QObject
{
    Q_OBJECT

public:
    explicit ExecutionProgram(QObject *parent = nullptr);

    QString message() const;
    void settingThread(QThread &exeProgramThread, ExecutionProgram &objProgram);

signals:
    void finished();    // Сигнал, по которому будем завершать поток, после завершения метода run

public slots:
    void run(); // Метод с полезной нагрузкой, который может выполняться в цикле

private:
   RobotControl robotControl;
   AppCore appCore;
   Kinematics kinematics;
   rt_ethercat *ethercatRT;

};

#endif // EXECUTIONPROGRAM_H
