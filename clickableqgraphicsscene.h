#ifndef CLICKABLEQGRAPHICSSCENE_H
#define CLICKABLEQGRAPHICSSCENE_H

#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>

class ClickableQGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    ClickableQGraphicsScene(QObject * parent = 0);
    ClickableQGraphicsScene(const QRectF & sceneRect, QObject * parent = 0);
    void setMouseTracking(bool b);
signals:
    void objectClicked(QGraphicsItem* item);
    void mouseMoved(QPointF);
protected:
     void mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent );
     void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent );
private:
     bool mouseTracking;
};

#endif // CLICKABLEQGRAPHICSSCENE_H
