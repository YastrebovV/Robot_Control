#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
#include "filesandfolders.h"
#include "robotcontrol.h"
#include <vector>
#include <string>

class AppCore : public QObject
{
    Q_OBJECT
public:
    explicit AppCore(QObject *parent = 0);

//signals:
    // Сигнал для передачи данных в qml-интерфейс
   // void sendToQml(int count);

public slots:
    void createFile(QString fileName, QString text);
    void deleteFile(QString fileName);
    void writeToFile(QString fileName, QString text);
    QString readFromFile(QString fileName);
    void jointManMove(int numAxis, double valueOffset);
    void cartesianManMove(int axis, double valueOffset);
    void stopMove();

    std::vector<QString> getActCoord();
    std::vector<QString> getActAngles();
    void setActCoord(std::vector<double>ActCoord);

private:
    FilesAndFolders FilesAndFolders_C;
    RobotControl RobotControl_C;
    Kinematics Kinematics_C;
    rt_ethercat *ethercatRT;
};

#endif // APPCORE_H
