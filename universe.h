#ifndef UNIVERSE_H
#define UNIVERSE_H

#define PI 3.14159265359
#define GRAVITY_CONSTANT 6.674e-11          // unit m^3/kg/s^2

#define SURFACE_UNCERTAINTY 0.00001

#include <QtCore>
#include <QGraphicsScene>

#include "celestialbody.h"

class Universe : public QObject
{
    Q_OBJECT
public:
    Universe(QGraphicsScene *scene);
    ~Universe();
    void addCelestialBody(CelestialBody *body);
    QPointF gravity(CelestialBody *body);

private:
    QList<CelestialBody *> bodies;
    QGraphicsScene *theScene;
    QPointF getEarthPosition();
    qreal getEarthRadius();
    qreal getEarthAngularVelocityDegrees();
    qreal getEarthAngularVelocityRadians();
    QPointF getMoonPosition();
    qreal getMoonRadius();
    bool touchedBody(QPointF pBody, qreal rBody, QPointF p);
    void intersectionBodySurface(QPointF *intersection, QPointF pBody, qreal rBody, QPointF pOld);
    static qreal angle(QPointF v);

public slots:
    void advance();
};

#endif // UNIVERSE_H
