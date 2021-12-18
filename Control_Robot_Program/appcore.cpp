#include "appcore.h"

//using namespace std;

AppCore::AppCore(QObject *parent) : QObject(parent)
{

}

//void AppCore::receiveFromQml()
//{
//    count++;
//    emit sendToQml(count);
//}

//void AppCore::testMetod()
//{
//    count = 0;
//    emit sendToQml(count);
//}

void AppCore::createFile(QString fileName, QString text)
{
    FilesAndFolders_C.createFile(fileName, text);
}

void AppCore::deleteFile(QString fileName)
{
    FilesAndFolders_C.deleteFile(fileName);
}

void AppCore::writeToFile(QString fileName, QString text)
{
    FilesAndFolders_C.writeToFile(fileName, text);
}

QString AppCore::readFromFile(QString fileName)
{
   return FilesAndFolders_C.readFromFile(fileName);
}

int AppCore::getCountAx1()
{
    return RobotControl_C.getCountAx1();
}

void AppCore::setCountAx1(int countAx)
{
    RobotControl_C.setCountAx1(countAx);
}
