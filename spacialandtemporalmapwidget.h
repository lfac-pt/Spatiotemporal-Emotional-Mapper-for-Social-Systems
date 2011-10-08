#ifndef SPACIALANDTEMPORALMAPWIDGET_H
#define SPACIALANDTEMPORALMAPWIDGET_H

#include <QWidget>
#include <QtGui>
#include "mappingrawdata.h"
#include "clickableqgraphicsscene.h"

class SpacialAndTemporalMapWidget : public QWidget
{
    Q_OBJECT
public:
    SpacialAndTemporalMapWidget(MappingRawData* mrd, QSize size);
    qreal getFrameRate();
    int getSelectedAgent();
    bool isPlaying();
    QColor getColorForEmotion(QString emotion);
signals:
    void adicionalInfoChanged(Agent* a);
    void tick(qreal t);
public slots:
    void tooglePlay();
    void stop();
    void seek(qreal f);
    void setFrameRate(int f);
    void setZoom(int v);
    void exportToImage();
    void viewSizeChanged();
private:
    MappingRawData* mapping_raw_data;
    QTimer *timer;
    ClickableQGraphicsScene * scene;
    QGraphicsView * view;
    QList<QGraphicsItem*> agents_circles;
    QHash<QString, QColor> emotion_to_color_dictionary;
    int n_select_agent;
    int timer_intreval;
    int last_zoom_value;
    bool at_the_end;
    QGraphicsItem* current_agent_selected_circle;
    QGraphicsPixmapItem * background_item;
    QRect last_view_size;
    qreal agent_elipse_size;

    void updateAgent(Agent* a);
    void zoomIn();
    void zoomOut();
private slots:
    void update();
    void objectClickedInScene(QGraphicsItem* item);

};

#endif // SPACIALANDTEMPORALMAPWIDGET_H
