#include <QtGui/QApplication>
#include "emmainwindow.h"
#include <QDebug>

#include "dataplot.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    /*QList<QPointF*> * v = new QList<QPointF*>;
    v->append(new QPointF(0,0.0));
    v->append(new QPointF(1,0.2));
    v->append(new QPointF(2,0.3));
    v->append(new QPointF(3,0.4));
    v->append(new QPointF(4,0.5));
    DataPlot w("Test plot",1.0,4);
    w.addPointSeries(v,"Test Serie 1");
    w.addPointSeries(v,"Test Serie 1");
    w.show();
    */

    EMMainWindow w;
    w.showMaximized();
    if(w.mustQuit)
        return 0;


    return a.exec();
}
