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
                    const std::vector<double>&   coords
                   )
{
    std::vector<QString> nameAttr;
    std::vector<QString> dataAttr;

    nameAttr.assign({"id", "type", "name", "tool", "base", "x", "y", "z", "a", "b", "c"});
    dataAttr.assign({id, strType, strName, strTool, strBase,
                    QString::number(coords[0]), QString::number(coords[1]),
                    QString::number(coords[2]), QString::number(coords[3]),
                    QString::number(coords[4]), QString::number(coords[5])});

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
                               const QString& id,
                               const std::vector<double> ActCoord)
{

    QDomElement  domElement = domDoc.firstChildElement();
    QDomElement domElement1= domDoc.documentElement();

    changeLineId(domElement1, id);

    QDomElement point = addPoint(domDoc, type, name, tool, base, id, ActCoord);
    domElement.appendChild(point);
}

void programcodeXML::getDataFromDom(const QDomNode& node,
                  std::vector<std::vector<QString>>& textProgram,
                  std::vector<std::vector<double>>&  dataProgram)
{
   QDomNode domNode = node.firstChild();

   while(!domNode.isNull()) {
       if(domNode.isElement()) {
          QDomElement domElement = domNode.toElement();
          if(!domElement.isNull()) {
              if(domElement.tagName() == "point") {

                  unsigned int countName = domElement.attribute("id", "").toUInt();

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
       getDataFromDom(domNode, textProgram, dataProgram);
       domNode = domNode.nextSibling();
    }
}

void programcodeXML::deleteNode(QDomNode& node, const QString& name, const QString& id)
{
    QDomNode domNode = node.firstChild();

    while(!domNode.isNull()) {
        if(domNode.isElement()) {
           QDomElement domElement = domNode.toElement();
           if(!domElement.isNull()) {
               if(domElement.tagName() == "point") {
                   if (domElement.attribute("name", "") == name && domElement.attribute("id", "") == id){
                       QDomNode parentNode = domNode.parentNode();
                       parentNode.removeChild(domNode);
                        break;
                   }
              }
           }
        }
        deleteNode(domNode, name, id);
        domNode = domNode.nextSibling();
    }
}

void programcodeXML::changeLineInDomDoc(QDomNode& node,
                                        const QString& type,
                                        const QString& newname,
                                        const QString& oldname,
                                        const QString& tool,
                                        const QString& base,
                                        const QString& id,
                                        const std::vector<double> ActCoord)
{

    QDomNode domNode = node.firstChild();

    while(!domNode.isNull()) {
        if(domNode.isElement()) {
           QDomElement domElement = domNode.toElement();
           if(!domElement.isNull()) {
               if(domElement.tagName() == "point") {

                   if (domElement.attribute("name", "") == oldname && domElement.attribute("id", "") == id){
                       domElement.removeAttribute("name");
                       domElement.setAttribute("name", newname);
                       domElement.removeAttribute("type");
                       domElement.setAttribute("type", type);
                       domElement.removeAttribute("tool");
                       domElement.setAttribute("tool", tool);
                       domElement.removeAttribute("base");
                       domElement.setAttribute("base", base);
                       if(ActCoord.size() == 6){
                           domElement.removeAttribute("x");
                           domElement.setAttribute("x", ActCoord[0]);
                           domElement.removeAttribute("y");
                           domElement.setAttribute("y", ActCoord[1]);
                           domElement.removeAttribute("z");
                           domElement.setAttribute("z", ActCoord[2]);
                           domElement.removeAttribute("a");
                           domElement.setAttribute("a", ActCoord[3]);
                           domElement.removeAttribute("b");
                           domElement.setAttribute("b", ActCoord[4]);
                           domElement.removeAttribute("c");
                           domElement.setAttribute("c", ActCoord[5]);
                       }
                   }
               }
           }
        }
        changeLineInDomDoc(domNode, type, newname, oldname, tool, base, id, ActCoord);
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
