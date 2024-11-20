#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#define PI 3.14159265359

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainterPath>

class CelestialBody : public QGraphicsItem
{
public:
    CelestialBody(qreal mass, qreal radius, qreal posX, qreal posY, qreal av, QColor color,
                  qreal sizefactor, qreal t_step, qreal t_lapse);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void advance(int phase);

private:
    qreal radius;
    qreal mass;
    qreal positionX;
    qreal positionY;
    qreal angle;
    qreal angularV;
    qreal time;
    qreal dt;
    QColor color;
    QPainterPath path;
};

#endif // CELESTIALBODY_H
