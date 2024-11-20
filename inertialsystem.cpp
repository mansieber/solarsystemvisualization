#include "inertialsystem.h"

InertialSystem::InertialSystem(qreal posX, qreal posY, qreal av, qreal t_step, qreal t_lapse)
{
    this->positionX = posX;
    this->positionY = posY;
    angle = 0.0;
    angularV = av;
    this->dt = t_step * t_lapse / 1000.0;
    setPos(mapToParent(positionX, positionY));
    time = 0.0;
}

void InertialSystem::advance(int phase)
{
    if ( ! phase ) return;
    setRotation(angle += angularV * dt);
    time += dt;
}

