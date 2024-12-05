#include "celestialbody.h"

#include <QDebug>
#include <QtMath>
#include <QVector2D>

CelestialBody::CelestialBody(QString s, qreal m, qreal r, qreal posX, qreal posY, qreal vX, qreal vY,
                             QColor c, qreal sf, qreal t_step, qreal t_lapse)
{
    name = s;
    mass = m;
    radius = r;
    position.setX(posX);
    position.setY(posY);
    this->velocity.setX(vX);
    this->velocity.setY(vY);
    gravity.setX(0.0);
    gravity.setY(0.0);
    color = c;
    virtualSizeF = sf;
    dt = t_step * t_lapse / 1000.0;
    setPos(position);
    time = 0.0;
    path.addEllipse(boundingRect());
}

QRectF CelestialBody::boundingRect() const
{
    qreal virtualRadius = radius * virtualSizeF;
    return QRect(- virtualRadius, - virtualRadius, 2.0 * virtualRadius, 2.0 * virtualRadius);
}

void CelestialBody::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush(color);
    QPen penBody(color);
    painter->setBrush(brush);
    painter->setPen(penBody);
    painter->drawPath(path);
}

/*
 * Return the name of the celestial body.
 */
QString CelestialBody::getName()
{
    return this->name;
}

/*
 * Return the mass of the celestial body (given in 10^9 kg).
 */
qreal CelestialBody::getMass()
{
    return this->mass;
}

/*
 * Return the position of the celestial body.
 */
QPointF CelestialBody::getPosition()
{
    return this->position;
}

/*
 * Set the gravity acting on the celestial body.
 */
void CelestialBody::setGravity(QPointF g)
{
    this->gravity = g;
}

/*
 * Move the celestial body according to the velocity of the body and the gravity of all
 * other bodies of the universe.
 */
void CelestialBody::advance(int phase)
{
    if ( ! phase ) return;

//    QVector2D currentRelativeVelocity;
    velocity += gravity * dt;
    position += velocity * dt;
    time += dt;
    qDebug() << "t = " << time << ": object " << name << ", position = " << position
             <<  " gravity = " << gravity << " velocity = " << velocity;                // gravity.manhattanLength()
    setPos(position);

    /*
        if ( universe->touchedBody(universe->getEarthPosition(), universe->getEarthRadius(), position) ) {
            universe->intersectionBodySurface(&position, universe->getEarthPosition(),
                                          universe->getEarthRadius(), position0);
            velocity.setX(0.0);
            velocity.setY(0.0);
            setPos(position);
        } else {
            setPos(position);
            setRotation( absThrust > 0.0 ? angle(currentThrust.toPointF()) : angle(velocity) );
            qDebug() << "t = " << time << ": object " << id << " position and rotation set";
        }
    */
}
