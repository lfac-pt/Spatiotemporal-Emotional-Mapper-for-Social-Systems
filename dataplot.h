#ifndef DATAPLOT_H
#define DATAPLOT_H

#include <QtGui>
#include "clickableqgraphicsscene.h"

class DataPlot : public QWidget
{
    Q_OBJECT

public:
    DataPlot(QString plot_name, qreal max_yy, qreal max_xx, QString yyLabel="Intensity",  QWidget *parent=0);
    void addPointSeries(QList<QPointF*>* v,QString series_name="", QColor color=Qt::black, bool progressive_show=false);
    void addLineSeries(QList<QPointF*>* v,QString series_name="", QColor color=Qt::black, bool progressive_show=false);
    void setTitle(QString s);
    qreal getUnusedYInd();
    void ensureYLabels();
    ~DataPlot();

public slots:
    void showInd(int ind);
    void exportToImage();
    void showAllInds();
    void zoomIn();
    void zoomOut();

protected:
    void closeEvent ( QCloseEvent * event );

private:
    ClickableQGraphicsScene * scene;
    QGraphicsView * view;
    QList<QColor> available_class_colors, available_class_colors_for_line;
    qreal x_offset,y_offset, plot_width, plot_height, class_labels_offset;
    QList<QList<QPointF*>*> incomplete_series;
    QList<QColor> incomplete_series_colors;
    QList<bool> incomplete_series_isPointSeries;
    int current_progressive_show_ind;
    QGraphicsTextItem * title_text_item;
    int initial_width, initial_height;
    qreal max_xx,max_yy;
    QLabel * currentCoordXLabel;
    QLabel * currentCoordYLabel;
    QList<qreal> availabel_yy_inds;
    QString yyLabel;

    void paintPoint(int i, QColor color, QList<QPointF*>*v);
    void paintLineSeg(int i, QColor color, QList<QPointF*>*v);
    qreal calcDotSize(int len);

private slots:
    void mouseMovedInScene(QPointF point);

};

#endif // DATAPLOT_H
