#include "celestialbody.h"

#include <QDebug>
#include <QtMath>

CelestialBody::CelestialBody(qreal mass, qreal radius, qreal posX, qreal posY, qreal av, QColor color,
                             qreal sizefactor, qreal t_step, qreal t_lapse)
{
    this->mass = mass;
    this->radius = radius * sizefactor;
    this->positionX = posX;
    this->positionY = posY;
    angle = 0.0;
    angularV = av;
    this->color = color;
    this->dt = t_step * t_lapse / 1000.0;
    setPos(positionX, positionY);
    time = 0.0;
    path.addEllipse(boundingRect());
}

QRectF CelestialBody::boundingRect() const
{
    return QRect(- radius, - radius, 2.0 * radius, 2.0 * radius);
}

void CelestialBody::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush(color);
    QPen penBody(color);
    painter->setBrush(brush);
    painter->setPen(penBody);
    painter->drawPath(path);
}


void CelestialBody::advance(int phase)
{
    if ( ! phase ) return;
    time += dt;
}
