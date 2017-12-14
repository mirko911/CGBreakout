#ifndef BALL_H
#define BALL_H

#include "simplesphere.h"

#include "GameObject.h"

class Ball : public GameObject
{
private:
    float radius;
    QVector3D velocity;
    QVector3D direction;
public:
    Ball(const float radius, const QVector3D position, const QVector3D direction);
    QVector3D hit(const QVector3D dir) const;
    QVector3D getDirection() const;
    void setDirection(const QVector3D _direction);
    float getRadius() const;
};

#endif // !BALL_H
