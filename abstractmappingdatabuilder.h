#ifndef ABSTRACTMAPPINGDATABUILDER_H
#define ABSTRACTMAPPINGDATABUILDER_H

#include <QObject>
#include <QtCore>
#include <QColor>

class AbstractMappingDataBuilder : public QObject
{
public:
    AbstractMappingDataBuilder();
    virtual void setCoordinates(QString type, QPointF lower_left, QPointF upper_right) {}
    virtual void setBackgroundImage(QString path) {}
    virtual void setAgentEllipseSize(qreal size) {}
    virtual void setEmotionColor(QString emotion, QColor color) {}
    virtual void beginFrameSet(QString time_units) {}
    virtual void beginFrame(qreal t) {}
    virtual void beginAgent(QString n, QString coordinates) {}
    virtual void addEmotion(QString name, qreal intensity) {}
    virtual void addGoal(QString description) {}
    virtual void addBelief(QString description) {}
};

#endif // ABSTRACTMAPPINGDATABUILDER_H
