#ifndef EMMAINWINDOW_H
#define EMMAINWINDOW_H

#include <QWidget>
#include "xmlhandler.h"
#include "mappingdatabuilder.h"
#include "spacialandtemporalmapwidget.h"
#include "dataplot.h"

namespace Ui {
    class EMMainWindow;
}

class EMMainWindow : public QWidget {
    Q_OBJECT
public:
    EMMainWindow(QWidget *parent = 0);
    ~EMMainWindow();

    bool mustQuit;

protected:
    void changeEvent(QEvent *e);
    void showEvent ( QShowEvent * event );
    void resizeEvent ( QResizeEvent * event );

private:
    Ui::EMMainWindow *ui;
    MappingRawData * mapping_raw_data;
    SpacialAndTemporalMapWidget* map_widget;
    QString default_input_filename;
    bool btnIsPlay;
    QList<QPointer<DataPlot>> plots_with_progressive_series;
    bool doneFirstShow;
    QString error_log;

    void init(QString existing_emotional_map_path);
    QList<QPointF*>* normalizePointList(QList<QPointF*>* v, int target_size);

private slots:
    void updateAgentAdicionalInfo(Agent* a);
    void mapTicked(qreal t);
    void sliderModed(int p);
    void tooglePlayPauseBtn();
    void toPlayBtn();
    void plotEmotions();
    void plotGoals();
    void plotBeliefs();
    void plotAllEmotions();
};

#endif // EMMAINWINDOW_H
