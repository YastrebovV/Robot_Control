#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
#include "filesandfolders.h"
#include "robotcontrol.h"
#include <vector>
#include <string>
//#include <iostream>

//using namespace std;

class AppCore : public QObject
{
    Q_OBJECT
public:
    explicit AppCore(QObject *parent = 0);

//signals:
    // Сигнал для передачи данных в qml-интерфейс
   // void sendToQml(int count);

public slots:
    // Слоты для приёма данных из qml-интерфейса
    //void receiveFromQml();
    //void testMetod();
    void createFile(QString fileName, QString text);
    void deleteFile(QString fileName);
    void writeToFile(QString fileName, QString text);
    QString readFromFile(QString fileName);
    void jointManMove(char numAxis, double valueOffset);
    void cartesianManMove(char axis, double valueOffset);

    std::vector<QString> getActCoord();
    std::vector<QString> getActAngles();
    void setActCoord(Kinematics::ActCoord ActCoord);

private:
    //int count=0;  // Счетчик, которым будем оперировать
    FilesAndFolders FilesAndFolders_C;
    RobotControl RobotControl_C;
    Kinematics Kinematics_C;
};

#endif // APPCORE_H
