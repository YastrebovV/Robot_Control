#ifndef FILESANDFOLDERS_H
#define FILESANDFOLDERS_H

#include <QObject>
#include <QFile>
#include <QTextStream>

class FilesAndFolders
{
public:
    FilesAndFolders();

public:
    bool createFile(QString fileName, QString text);
    bool deleteFile(QString fileName);
    bool writeToFile(QString fileName, QString text);
    QString readFromFile(QString fileName);

};

#endif // FILESANDFOLDERS_H
