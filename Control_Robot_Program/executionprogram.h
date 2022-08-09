#ifndef EXECUTIONPROGRAM_H
#define EXECUTIONPROGRAM_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include "appcore.h"

class ExecutionProgram : public QObject
{
    Q_OBJECT
    // Свойство, управляющее работой потока
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)

public:
    explicit ExecutionProgram(QObject *parent = nullptr);

    bool running() const;
    QString message() const;
    void settingThread(QThread &exeProgramThread, ExecutionProgram &objProgram);

    bool m_running;

signals:
    void finished();    // Сигнал, по которому будем завершать поток, после завершения метода run
    void runningChanged(bool running);

public slots:
    void run(); // Метод с полезной нагрузкой, который может выполняться в цикле
    void setRunning(bool running);

private:
   RobotControl robotControl;
   AppCore appCore;
   Kinematics kinematics;
};

#endif // EXECUTIONPROGRAM_H
