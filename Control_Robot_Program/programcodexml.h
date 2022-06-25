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
                        const QString& base,
                        const QString& id);
    void traverseNode(const QDomNode& node,
                      std::vector<std::vector<QString>>& textProgram,
                      std::vector<std::vector<double>>&  dataProgram,
                      unsigned int countName,
                      unsigned int countTag);
    void deleteNode(QDomNode& node, const QString& name);
    void changeLineInDomDoc(QDomNode& node,
                                   const QString& type,
                                   const QString& newname,
                                   const QString& oldname,
                                   const QString& tool,
                                   const QString& base,
                            std::vector<std::vector<QString>>& textProgram,
                            std::vector<std::vector<double>>&  dataProgram,
                            unsigned int countName,
                            unsigned int countTag);

private:
    QDomElement makeElement(QDomDocument& domDoc,
                            const QString& elemName,
                            const std::vector<QString>&  arrAttr,
                            const std::vector<QString>&  dataAttr
                           );
    QDomElement addPoint(      QDomDocument& domDoc,
                        const QString&      strType,
                        const QString&      strName,
                        const QString&      strTool,
                        const QString&      strBase,
                        const QString& id,
                        const coords&       coords
                       );
    void changeLineId(QDomNode& node,
                      const QString& id);
    RobotControl RobotControl_C;

};

#endif // PROGRAMCODEXML_H
