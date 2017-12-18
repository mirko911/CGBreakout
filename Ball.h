#ifndef BALL_H
#define BALL_H

#include "simplesphere.h"

#include "GameObject.h"

class Ball : public GameObject
{
private:
    float radius;
    float velocity;
    QVector3D direction;
public:
    Ball(const float radius, const QVector3D position, const float velocity, const QVector3D direction);
    QVector3D hit(const QVector3D dir) const;
    QVector3D getDirection() const;
    void setDirection(const QVector3D _direction);
    void setVelocity(const float _velocity);
    float getVelocity() const;
    float getRadius() const;
};

#endif // !BALL_H
