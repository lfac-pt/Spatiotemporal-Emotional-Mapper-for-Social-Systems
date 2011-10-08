#ifndef MAPPINGRAWDATA_H
#define MAPPINGRAWDATA_H

#include <QObject>
#include <QtCore>
#include <QColor>
#include <frame.h>

class MappingRawData : public QObject
{
public:
    MappingRawData(QPointF lower_left, QPointF upper_right);

    void addFrame(Frame* f);
    Frame* getFrame(qreal t);
    Frame* getLastFrame();
    QPointF getLowerLeft();
    QPointF getUpperRight();
    QString getBackgroundImagePath();
    void setbackgroundImagePath(QString path);
    void setAgentElipseSize(qreal size);
    qreal getAgentElipseSize();
    void setEmotionColor(QString emotion, QColor color);
    QHash<QString, QColor> getEmotionColorDict();

    //Iterator for the frames
    void first();
    void last();
    bool next();
    bool hasNext();
    void goTo(qreal f);
    Frame* current();

    QList<Frame*> frame_list;

private:
    QPointF lower_left, upper_right;
    int current_iterator_index;
    QString background_image_path;
    qreal agentElipseSize;
    QHash<QString, QColor> emotion_to_color_dictionary;
};

#endif // MAPPINGRAWDATA_H
