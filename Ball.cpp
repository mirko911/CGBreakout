#include "Ball.h"

Ball::Ball(const float radius, const QVector3D position, const float velocity, const QVector3D direction) :
    GameObject(position, GeometryHandler::instance().getGeometry("pokeball")),
radius(radius), velocity(velocity), direction(direction)
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

void Ball::setVelocity(const float _velocity)
{
    velocity = _velocity;
}

float Ball::getVelocity() const
{
    return velocity;
}

float Ball::getRadius() const
{
    return radius;
}
