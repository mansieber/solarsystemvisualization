#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#define PI 3.14159265359

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainterPath>
#include <QPointF>

class CelestialBody : public QGraphicsItem
{
public:
    CelestialBody(QString s, qreal m, qreal r, qreal posX, qreal posY, qreal vX, qreal vY,
                  QColor c, qreal sf, qreal t_step, qreal t_lapse);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void advance(int phase);

private:
    QString name;
    qreal radius;
    qreal mass;
    QPointF position;
    QPointF velocity;
    QPointF gravity;
    qreal time;
    qreal dt;
    QColor color;
    qreal virtualSizeF;
    QPainterPath path;
};

#endif // CELESTIALBODY_H
