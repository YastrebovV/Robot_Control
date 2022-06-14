#ifndef PROGRAMCODEXML_H
#define PROGRAMCODEXML_H

#include <QtXml>
#include "robotcontrol.h"

struct coords{
    double x;
    double y;
    double z;
    double a;
    double b;
    double c;
};

class programcodeXML
{
public:
    programcodeXML();
    QDomDocument createDomDoc(const QString& progName);
    void writeToDomDoc(QDomDocument& domDoc,
                        const QString& type,
                        const QString& name,
                        const QString& tool,
                        const QString& base);

private:
    QDomElement makeElement(      QDomDocument& domDoc,
                            const QString&      strName,
                            const QString&      strAttr = QString::null,
                            const QString&      strText = QString::null
                           );
    QDomElement addPoint(      QDomDocument& domDoc,
                        const QString&      strType,
                        const QString&      strName,
                        const QString&      strTool,
                        const QString&      strBase,
                        const coords&       coords
                       );
    RobotControl RobotControl_C;

};

#endif // PROGRAMCODEXML_H
