// myitem.h

#ifndef MYITEM_H
#define MYITEM_H

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>

class MyItem : public QGraphicsItem
{
public:
    MyItem(int, int, bool);
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

protected:
    void advance(int phase);

private:
    qreal angle, speed;
    int lastX, lastY;
    void doCollision();
    bool myPlayer;
};

#endif // MYITEM_H
