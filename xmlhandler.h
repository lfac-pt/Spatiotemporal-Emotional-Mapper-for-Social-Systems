#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <QObject>
#include <QtCore>
#include <QtXml>
#include <QtGui>
#include <QDebug>
#include "abstractmappingdatabuilder.h"

class XMLHandler : public QObject
{
public:
    XMLHandler(QString filename, QWidget* parent);
    bool read(AbstractMappingDataBuilder * builder);
private:
    QDomDocument domDocument;
    QFile* file;
    QWidget* parent;

    void showError(QString message);
    void parseGeographicBonduaries(QDomElement el);
    void parseFrameSet(QDomElement el);
    AbstractMappingDataBuilder * builder;
};

#endif // XMLHANDLER_H
