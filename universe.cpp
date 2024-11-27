#include "universe.h"

#include <QtDebug>

Universe::Universe(QGraphicsScene *scene)
{
    theScene = scene;
}

Universe::~Universe()
{

}

/*
 * Method calculates the gravity acting on a body in the gravity field of
 * other celestial bodies.
 */
QPointF Universe::gravity(CelestialBody *body)
{
/*
    qreal rxEarth = p.x() - positionEarth.x();
    qreal ryEarth = p.y() - positionEarth.y();
    qreal rxMoon = p.x() - positionMoon.x();
    qreal ryMoon = p.y() - positionMoon.y();
    if ( ( rxEarth == 0.0 && ryEarth == 0.0 ) || ( rxMoon == 0.0 && ryMoon == 0.0 ) ) {
        return QPoint(INFINITY, INFINITY);
    }
    QPointF aEarth, aMoon;
    qreal aabsEarth = GRAVITY_CONSTANT * MASS_EARTH / ( rxEarth * rxEarth + ryEarth * ryEarth );
    qreal aabsMoon = GRAVITY_CONSTANT * MASS_MOON / ( rxMoon * rxMoon + ryMoon * ryMoon );
    if ( rxEarth == 0.0 ) {
        aEarth.setX(0.0);
        aEarth.setY(aabsEarth * ( ryEarth > 0.0 ? -1.0 : 1.0));
    } else {
        qreal w = qAtan(ryEarth / rxEarth);
        qreal f = rxEarth > 0.0 ? -1.0 : 1.0;
        aEarth.setX(f * aabsEarth * qCos(w));
        aEarth.setY(f * aabsEarth * qSin(w));
    }
    if ( rxMoon == 0.0 ) {
        aMoon.setX(0.0);
        aMoon.setY(aabsMoon * ( ryMoon > 0.0 ? -1.0 : 1.0));
    } else {
        qreal w = qAtan(ryMoon / rxMoon);
        qreal f = rxMoon > 0.0 ? -1.0 : 1.0;
        aMoon.setX(f * aabsMoon * qCos(w));
        aMoon.setY(f * aabsMoon * qSin(w));
    }
    return aEarth + aMoon;
*/
    return QPointF(0.0, 0.0);
}

/*
 * Method returns the position of earth in the universe.
 */
QPointF Universe::getEarthPosition() {
    return positionEarth;
}

/*
 * Method returns the position of moon in the universe.
 */
QPointF Universe::getMoonPosition() {
    return positionMoon;
}

/*
 * Method returns the radius of earth.
 */
qreal Universe::getEarthRadius() {
    return radiusEarth;
}

/*
 * Method returns the radius of moon.
 */
qreal Universe::getMoonRadius() {
    return radiusMoon;
}

/*
 * Method returns the angular velocity of the earth (radians per second).

qreal Universe::getEarthAngularVelocityRadians() {
    return ANGULAR_VELOCITY_EARTH;
}
*/

/*
 * Method returns the angular velocity of the earth (degrees per second).
qreal Universe::getEarthAngularVelocityDegrees() {
    return ANGULAR_VELOCITY_EARTH * 360.0 / 2.0 / PI;
}
 */

/*
 * Method calculates whether a position of an object is inside the celestial body.
 * @param pBody is the location of the celestial body
 * @param rBody is the radius of the celestial body
 * @param p is the location of the object
 */
bool Universe::touchedBody(QPointF pBody, qreal rBody, QPointF p)
{
    QPointF prel = p - pBody;
    qreal d = sqrt( prel.x() * prel.x() + prel.y() * prel.y() );
    qreal r = rBody + SURFACE_UNCERTAINTY;
    char sd[256], sr[256];
    sprintf(sd, "%15lf", d);
    sprintf(sr, "%15lf", r);
    qDebug() << "    touchedBody? position_rel =" << prel << "squ. dist. from center =" << sd
             << " squ. radius =" << sr;
    return ( d <= r );
}

/*
 * Method calculates the point where an object touches the surface of a celestial body.
 * @param intersection is the location of the intersection to be calculated
 *        at the time of method call intersection passes the virtual location of the
 *        object after penetrating the surface of the body
 * @param pBody is the location of the celestial body
 * @param rBody is the radius of the celestial body
 * @param pOld is the location of the object before touching the surface of the body
 */
void Universe::intersectionBodySurface(QPointF *intersection,
                                       QPointF pBody, qreal rBody, QPointF pOld)
{
    qreal x1 = pOld.x() - pBody.x();          // transform into body coordinates
    qreal y1 = pOld.y() - pBody.y();          // transform into body coordinates
    qreal x2 = intersection->x() - pBody.x(); // transform into body coordinates
    qreal y2 = intersection->y() - pBody.y(); // transform into body coordinates
    qreal r = rBody;
    if ( x1 == x2 ) {
        intersection->setX(x1 + pBody.x());    // transform into universe coordinates
        intersection->setY(pBody.y() + rBody * ( y2 > y1 ? -1.0 : 1.0 ));
    } else {
        qreal m = ( y2 - y1 ) / (x2 - x1 );
        qreal y0 = y1 - m * x1;
        qreal m2 = 1.0 + m * m;
        qreal x3a = sqrt( ( m * m ) * ( y0 * y0 ) / m2 / m2 + ( ( r * r ) - ( y0 * y0 ) ) / m2 ) -
                    m * y0 / m2;
        qreal x3b = - sqrt( ( m * m ) * ( y0 * y0 ) / m2 / m2 + ( ( r * r ) - ( y0 * y0 ) ) / m2 ) -
                    m * y0 / m2;
        qreal y3a = y0 + m * x3a;
        qreal y3b = y0 + m * x3b;
        if ( ( x1 - x3a ) * ( x1 - x3a ) + ( y1 - y3a ) * ( y1 - y3a ) <   // select the right solution
             ( x1 - x3b ) * ( x1 - x3b ) + ( y1 - y3b ) * ( y1 - y3b ) ) { // which should be the nearest to pOld
            intersection->setX(x3a + pBody.x()); // transform into universe coordinates
            intersection->setY(y3a + pBody.y()); // transform into universe coordinates
        } else {
            intersection->setX(x3b + pBody.x()); // transform into universe coordinates
            intersection->setY(y3b + pBody.y()); // transform into universe coordinates
        }
    }
}

/*
 * Method calculates the angle (DEC) of a vector with the x axis.
 * Gives wrong result for zero length vector.
 */
qreal Universe::angle(QPointF v) {
    if ( v.x() == 0.0 ) {
        return ( v.y() > 0.0 ? 90.0 : -90.0 );
    } else {
        return qRadiansToDegrees(qAtan( v.y() / v.x() )) +
                                        ( v.x() > 0.0 ? 0.0 : ( v.y() > 0.0 ? 180.0 : -180.0 ) );
    }
}

/*
 * Method calculates the gravity for each celestial body and
 * finally invokes the redraw mechanism of the graphics scene.
 */
void Universe::advance()
{
    // calculate the gravity acting on each celestial body
    theScene->advance();
}

