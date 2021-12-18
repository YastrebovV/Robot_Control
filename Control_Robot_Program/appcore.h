#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
#include "filesandfolders.h"
#include "robotcontrol.h"
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
    int getCountAx1(); // геттер для countAx1
    void setCountAx1(int countAx); // сеттер для countAx1

private:
    //int count=0;  // Счетчик, которым будем оперировать
    FilesAndFolders FilesAndFolders_C;
    RobotControl RobotControl_C;
};

#endif // APPCORE_H
