#ifndef UNIVERSE_H
#define UNIVERSE_H

#define PI 3.14159265359
#define GRAVITY_CONSTANT 6.674e-11          // Still m !!!!
#define DISTANCE_EARTH_MOON 390.0e3         // km
#define DISTANCE_SUN_EARTH 148.9e6          // km
#define MASS_SUN 1.988e30
#define RADIUS_SUN 6.99e5                   // km
#define POSITION_X_SUN 0.0                  // km related to origin of solar system
#define POSITION_Y_SUN 0.0                  // km related to origin of solar system
#define VELOCITY_X_SUN 0.0                  // km/s
#define VELOCITY_Y_SUN 0.0                  // km/s
#define MASS_EARTH 5.974e24
#define RADIUS_EARTH 6.37e3                 // km
#define POSITION_X_EARTH -148.9e6           // km related to origin of solar system
#define POSITION_Y_EARTH 0.0                // km related to origin of solar system
#define VELOCITY_X_EARTH 0.0                // km/s
#define VELOCITY_Y_EARTH 29.8               // km/s
// #define ANGULAR_VELOCITY_EARTH 7.2722E-5    // Still m !!!!
#define MASS_MOON 7.349e22
#define RADIUS_MOON 1.738e3                 // km
#define POSITION_X_MOON POSITION_X_EARTH - DISTANCE_EARTH_MOON
#define POSITION_Y_MOON 0.0                 // km related to origin of solar system
#define VELOCITY_X_MOON 0.0                 // km/s
#define VELOCITY_Y_MOON 30.82               // km/s
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

    // Hier eine QList oder sowas, die alle Himmelskoerper speichert

    QGraphicsScene *theScene;
    QPointF positionSun, positionEarth, positionMoon;
    qreal radiusSun, radiusEarth, radiusMoon;
    QPointF gravity(CelestialBody *body);
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
