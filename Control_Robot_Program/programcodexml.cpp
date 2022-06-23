#include "programcodexml.h"

programcodeXML::programcodeXML()
{

}

QDomElement programcodeXML::makeElement(      QDomDocument& domDoc,
                        const QString&      strName,
                        const QString&      strAttr,
                        const QString&      strText
                       )
{
    QDomElement domElement = domDoc.createElement(strName);

    if (!strAttr.isEmpty()) {
        QDomAttr domAttr = domDoc.createAttribute("name");
        domAttr.setValue(strAttr);
        domElement.setAttributeNode(domAttr);
    }

    if (!strText.isEmpty()) {
        QDomText domText = domDoc.createTextNode(strText);
        domElement.appendChild(domText);
    }
    return domElement;
}

QDomElement programcodeXML::addPoint(      QDomDocument& domDoc,
                    const QString&      strType,
                    const QString&      strName,
                    const QString&      strTool,
                    const QString&      strBase,
                    const coords&       coords
                   )
{

    QDomElement domElement = makeElement(domDoc,
                                         "point",
                                         strName
                                        );

    domElement.appendChild(makeElement(domDoc, "type", "", strType));
    domElement.appendChild(makeElement(domDoc, "tool", "", strTool));
    domElement.appendChild(makeElement(domDoc, "base", "", strBase));
    domElement.appendChild(makeElement(domDoc, "x", "", QString::number(coords.x)));
    domElement.appendChild(makeElement(domDoc, "y", "", QString::number(coords.y)));
    domElement.appendChild(makeElement(domDoc, "z", "", QString::number(coords.z)));
    domElement.appendChild(makeElement(domDoc, "a", "", QString::number(coords.a)));
    domElement.appendChild(makeElement(domDoc, "b", "", QString::number(coords.b)));
    domElement.appendChild(makeElement(domDoc, "c", "", QString::number(coords.c)));

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
                               const QString& base)
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


    QDomElement point = addPoint(domDoc, type, name, tool, base, coordsLocal);

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
                 // qDebug() << "Attr: "
                         //  << domElement.attribute("name", "");
                  countName++;
                  countTag=1;
                  textProgram[countName][0] = domElement.attribute("name", "");
              }else {
                  //qDebug() << "TagName: " << domElement.tagName()
                          // << "\tText: " << domElement.text();
                  if(countTag<=3){
                      textProgram[countName][countTag]=domElement.text();
                  }else{
                      dataProgram[countName][countTag-4]=domElement.text().toDouble();
                  }
                  countTag++;
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
                    //qDebug() << "Attr: "
                            // << domElement.attribute("name", "");
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
                                        unsigned int countTag,
                                        bool nameTrue)
{

    QDomNode domNode = node.firstChild();

    while(!domNode.isNull()) {
        if(domNode.isElement()) {
           QDomElement domElement = domNode.toElement();
           if(!domElement.isNull()) {
               if(domElement.tagName() == "point") {
                  // qDebug() << "Attr: "
                         //   << domElement.attribute("name", "");
                   nameTrue = false;
                   countName++;
                   countTag=1;

                   if (domElement.attribute("name", "") == oldname){
                       domElement.removeAttribute("name");
                       domElement.setAttribute("name", newname);
                       nameTrue = true;
                   }
                   textProgram[countName][0] = domElement.attribute("name", "");
               }else {
                   //qDebug() << "TagName: " << domElement.tagName()
                           // << "\tText: " << domElement.text();
                   if(countTag<=3){
                       if(nameTrue){
                            QDomText t = domElement.firstChild().toText();
                            if(domElement.tagName() == "type") {

                            }
                            if(domElement.tagName()== "tool") {
                              t.setData(tool);
                            }
                            if(domElement.tagName() == "base") {
                              t.setData(base);
                            }
                       }
                       textProgram[countName][countTag]=domElement.text();
                   }
                   countTag++;
              }
           }
        }
        changeLineInDomDoc(domNode, type, newname, oldname, tool, base, textProgram, dataProgram, countName, countTag, nameTrue);
        domNode = domNode.nextSibling();
     }

}

