#include "programcodexml.h"

programcodeXML::programcodeXML()
{

}

QDomElement programcodeXML::makeElement(QDomDocument& domDoc,
                        const QString& elemName,
                        const std::vector<QString>&  arrAttr,
                        const std::vector<QString>&  dataAttr
                       )
{
    QDomElement domElement = domDoc.createElement(elemName);
    QDomAttr domAttr;
    for(unsigned int i =0; i < arrAttr.size(); i++){
        QDomAttr domAttr = domDoc.createAttribute(arrAttr[i]);
        domAttr.setValue(dataAttr[i]);
        domElement.setAttributeNode(domAttr);
    }

    return domElement;
}

QDomElement programcodeXML::addPoint(      QDomDocument& domDoc,
                    const QString&      strType,
                    const QString&      strName,
                    const QString&      strTool,
                    const QString&      strBase,
                    const QString&      id,
                    const coords&       coords
                   )
{
    std::vector<QString> nameAttr;
    std::vector<QString> dataAttr;

    nameAttr.assign({"id", "type", "name", "tool", "base", "x", "y", "z", "a", "b", "c"});
    dataAttr.assign({id, strType, strName, strTool, strBase,
                    QString::number(coords.x), QString::number(coords.y),
                    QString::number(coords.z), QString::number(coords.a),
                    QString::number(coords.b), QString::number(coords.c)});

    QDomElement domElement = makeElement(domDoc,"point", nameAttr, dataAttr);

    return domElement;
}

QDomDocument programcodeXML::createDomDoc(const QString& progName)
{
     QDomDocument doc(progName);
     QDomElement  domElement = doc.createElement(progName);
     doc.appendChild(domElement);
     return doc;
}

void programcodeXML::writeToDomDoc(QDomDocument& domDoc,
                               const QString& type,
                               const QString& name,
                               const QString& tool,
                               const QString& base,
                               const QString& id)
{
    coords coordsLocal;

    QDomElement  domElement = domDoc.firstChildElement();

    std::vector<double> ActCoord = RobotControl_C.getActCoord();
    coordsLocal.x = ActCoord[0];
    coordsLocal.y = ActCoord[1];
    coordsLocal.z = ActCoord[2];
    coordsLocal.a = ActCoord[3];
    coordsLocal.b = ActCoord[4];
    coordsLocal.c = ActCoord[5];

    QDomElement domElement1= domDoc.documentElement();

    changeLineId(domElement1, id);

    QDomElement point = addPoint(domDoc, type, name, tool, base, id, coordsLocal);
    domElement.appendChild(point);
}

void programcodeXML::traverseNode(const QDomNode& node,
                  std::vector<std::vector<QString>>& textProgram,
                  std::vector<std::vector<double>>&  dataProgram,
                  unsigned int countName,
                  unsigned int countTag)
{
   QDomNode domNode = node.firstChild();

   while(!domNode.isNull()) {
       if(domNode.isElement()) {
          QDomElement domElement = domNode.toElement();
          if(!domElement.isNull()) {
              if(domElement.tagName() == "point") {

                  countName = domElement.attribute("id", "").toUInt();

                  textProgram[countName][0] = domElement.attribute("name", "");
                  textProgram[countName][1] = domElement.attribute("type", "");
                  textProgram[countName][2] = domElement.attribute("tool", "");
                  textProgram[countName][3] = domElement.attribute("base", "");
                  dataProgram[countName][0] = domElement.attribute("x", "").toDouble();
                  dataProgram[countName][1] = domElement.attribute("y", "").toDouble();
                  dataProgram[countName][2] = domElement.attribute("z", "").toDouble();
                  dataProgram[countName][3] = domElement.attribute("a", "").toDouble();
                  dataProgram[countName][4] = domElement.attribute("b", "").toDouble();
                  dataProgram[countName][5] = domElement.attribute("c", "").toDouble();
              }
          }
       }
       traverseNode(domNode, textProgram, dataProgram, countName, countTag);
       domNode = domNode.nextSibling();
    }
}

void programcodeXML::deleteNode(QDomNode& node, const QString& name)
{
    QDomNode domNode = node.firstChild();

    while(!domNode.isNull()) {
        if(domNode.isElement()) {
           QDomElement domElement = domNode.toElement();
           if(!domElement.isNull()) {
               if(domElement.tagName() == "point") {
                   if (domElement.attribute("name", "") == name){
                       QDomNode parentNode = domNode.parentNode();
                       parentNode.removeChild(domNode);
                        break;
                   }
              }
           }
        }
        deleteNode(domNode, name);
        domNode = domNode.nextSibling();
    }
}

void programcodeXML::changeLineInDomDoc(QDomNode& node,
                                        const QString& type,
                                        const QString& newname,
                                        const QString& oldname,
                                        const QString& tool,
                                        const QString& base,
                                        std::vector<std::vector<QString>>& textProgram,
                                        std::vector<std::vector<double>>&  dataProgram,
                                        unsigned int countName,
                                        unsigned int countTag)
{

    QDomNode domNode = node.firstChild();

    while(!domNode.isNull()) {
        if(domNode.isElement()) {
           QDomElement domElement = domNode.toElement();
           if(!domElement.isNull()) {
               if(domElement.tagName() == "point") {

                   countName = domElement.attribute("id", "").toUInt();

                   if (domElement.attribute("name", "") == oldname){
                       domElement.removeAttribute("name");
                       domElement.setAttribute("name", newname);
                       domElement.removeAttribute("type");
                       domElement.setAttribute("type", type);
                       domElement.removeAttribute("tool");
                       domElement.setAttribute("tool", tool);
                       domElement.removeAttribute("base");
                       domElement.setAttribute("base", base);
                   }
                   textProgram[countName][0] = domElement.attribute("name", "");
                   textProgram[countName][1] = domElement.attribute("type", "");
                   textProgram[countName][2] = domElement.attribute("tool", "");
                   textProgram[countName][3] = domElement.attribute("base", "");
               }
           }
        }
        changeLineInDomDoc(domNode, type, newname, oldname, tool, base, textProgram, dataProgram, countName, countTag);
        domNode = domNode.nextSibling();
     }

}

void programcodeXML::changeLineId(QDomNode& node,
                                  const QString& id)
{
    QDomNode domNode = node.firstChild();

    while(!domNode.isNull()) {
        if(domNode.isElement()) {
           QDomElement domElement = domNode.toElement();
           if(!domElement.isNull()) {
               if(domElement.tagName() == "point") {
                   if (domElement.attribute("id", "").toUInt() >= id.toUInt()){
                       QString tempStr = QString::number(domElement.attribute("id", "").toUInt()+1);
                       domElement.removeAttribute("id");
                       domElement.setAttribute("id", tempStr);
                   }
               }
           }
        }
        changeLineId(domNode, id);
        domNode = domNode.nextSibling();
     }
}

void programcodeXML::changeIdWhenDelLine(QDomNode& node,
                                  const QString& id)
{
    QDomNode domNode = node.firstChild();

    while(!domNode.isNull()) {
        if(domNode.isElement()) {
           QDomElement domElement = domNode.toElement();
           if(!domElement.isNull()) {
               if(domElement.tagName() == "point") {
                   if (domElement.attribute("id", "").toUInt() > id.toUInt()){
                       QString tempStr = QString::number(domElement.attribute("id", "").toUInt()-1);
                       domElement.removeAttribute("id");
                       domElement.setAttribute("id", tempStr);
                   }
               }
           }
        }
        changeLineId(domNode, id);
        domNode = domNode.nextSibling();
     }
}
