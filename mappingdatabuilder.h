#ifndef MAPPINGDATABUILDER_H
#define MAPPINGDATABUILDER_H

#include "abstractmappingdatabuilder.h"
#include "mappingrawdata.h"
#include <QDebug>

class MappingDataBuilder : public AbstractMappingDataBuilder
{
public:
    MappingDataBuilder();
    void setCoordinates(QString type, QPointF lower_left, QPointF upper_right);
    void setBackgroundImage(QString path);
    void setAgentEllipseSize(qreal size);
    void setEmotionColor(QString emotion, QColor color);
    void beginFrameSet(QString time_units);
    void beginFrame(qreal t);
    void beginAgent(QString n, QString coordinates);
    void addEmotion(QString name, qreal intensity);
    void addGoal(QString description);
    void addBelief(QString description);
    MappingRawData* getResult();

    QString error_log;
private:
    MappingRawData * mrd;
    Frame* in_constrution_frame;
    Agent* in_constrution_agent;
    qreal time_multiplier;
    QHash<QString, qreal>* time_multipliers_dictionary;
    bool dirty_agent, dirty_frame;
    bool verbose;
    int agent_couter;
    QHash<QString, int> agent_dict;
};

#endif // MAPPINGDATABUILDER_H
