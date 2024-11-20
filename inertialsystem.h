#ifndef INERTIALSYSTEM_H
#define INERTIALSYSTEM_H

#include <QGraphicsItemGroup>

class InertialSystem : public QGraphicsItemGroup
{
public:
    InertialSystem(qreal posX, qreal posY, qreal av, qreal t_step, qreal t_lapse);

protected:
    void advance(int phase);

private:
    qreal positionX;
    qreal positionY;
    qreal angle;
    qreal angularV;
    qreal time;
    qreal dt;
};

#endif // INERTIALSYSTEM_H
