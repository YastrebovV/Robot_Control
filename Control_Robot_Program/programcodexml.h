#ifndef PROGRAMCODEXML_H
#define PROGRAMCODEXML_H

#include <QtXml>

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
                        const QString& id,
                        const std::vector<double> ActCoord);
    void getDataFromDom(const QDomNode& node,
                      std::vector<std::vector<QString>>& textProgram,
                      std::vector<std::vector<double>>&  dataProgram);
    void deleteNode(QDomNode& node, const QString& name, const QString& id);
    void changeLineInDomDoc(QDomNode& node,
                                   const QString& type,
                                   const QString& newname,
                                   const QString& oldname,
                                   const QString& tool,
                                   const QString& base,
                                   const QString& id,
                                   const std::vector<double> ActCoord);
    void changeIdWhenDelLine(QDomNode& node,
                                      const QString& id);

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
                        const std::vector<double>&   coords
                       );
    void changeLineId(QDomNode& node,
                      const QString& id);

};

#endif // PROGRAMCODEXML_H
