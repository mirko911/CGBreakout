#include "Ball.h"


Ball::Ball(const float radius, const QVector3D position, const QVector3D direction) : GameObject(position, new SimpleSphere(radius)),
radius(radius), direction(direction)
{
    setPosition(position);
}

QVector3D Ball::hit(const QVector3D vec) const
{
    return -(direction - (vec * (2 * (QVector3D::dotProduct(direction, vec)))));
}

QVector3D Ball::getDirection() const
{
    return direction;
}

void Ball::setDirection(const QVector3D _direction)
{
    direction = _direction;
}

float Ball::getRadius() const
{
    return radius;
}
