// myitem.cpp

#include "myitem.h"

MyItem::MyItem(int x, int y, bool player)
{
    int transX = 6-x;
    int transY = y;
    myPlayer = player;
    angle = (180);
    setRotation(angle);
    speed = 0.5;
    int    startX = -346 + 50 * transX;
    int    startY = -0;
    setPos(mapToParent(startX, startY));
    lastX = -346 + 50 * transX;
    lastY = 50*(transY+1);
}

QRectF MyItem::boundingRect() const
{
    return QRect(0,0,43,43);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QPen pen(Qt::red, 5);
    QPen pen2(Qt::yellow, 5);
    if(myPlayer)
        painter->setPen(pen);
    else
        painter->setPen(pen2);
    if(this->pos().y() >= lastY)
        doCollision();
    painter->drawEllipse(rect);
}

void MyItem::advance(int phase)
{
    if(!phase) return;
    QPointF location = this->pos();
    setPos(mapToParent(0, -speed));
}

void MyItem::doCollision()
{
    speed = 0;
}
