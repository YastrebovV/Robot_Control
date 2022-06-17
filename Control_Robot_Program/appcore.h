#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
#include "filesandfolders.h"
#include "robotcontrol.h"
#include "programcodexml.h"
#include <vector>
#include<iostream>
#include <string>
#include <QtXml>

class AppCore : public QObject
{
    Q_OBJECT

public:
    explicit AppCore(QObject *parent = 0);

signals:
    // Сигнал для передачи данных в qml-интерфейс
    void insertToListMode(QString name, QString tool, QString base);

public slots:
    void createFile(QString fileName, QString path);
    void deleteFile(QString fileName, QString path);
    void openFile(QString fileName, QString path);
    void writeToFile(QString fileName,
                     QString path,
                     QString type,
                     QString name,
                     QString tool,
                     QString base);
    QString readFromFile(QString fileName, QString path);
    void jointManMove(int numAxis, double valueOffset);
    void cartesianManMove(int axis, double valueOffset);
    void stopMove();

    std::vector<QString> getActCoord();
    std::vector<QString> getActAngles();
   // double getAngelAct(unsigned int index);
    void setActCoord(std::vector<double>ActCoord);
    void setSpeed(unsigned int speed);
    unsigned long long getAxisSpeed();
    void setAxisMastering(bool start);

private:
    FilesAndFolders FilesAndFolders_C;
    RobotControl RobotControl_C;
    Kinematics Kinematics_C;
    rt_ethercat *ethercatRT;
    programcodeXML programcodeXML_C;
    QString progName;
    QDomDocument domDoc;
    std::vector<std::vector<QString>> textProgram;
    std::vector<std::vector<double>>  dataProgram;


};

#endif // APPCORE_H
