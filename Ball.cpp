#include "Ball.h"


Ball::Ball(const float radius, const QVector3D position) : GameObject(position, new SimpleSphere(radius)),
radius(radius)
{
	setPosition(position);
}


void Ball::doIt()
{
	position.setX(position.x() + 0.05);
	setPosition(position);
}Ball::Ball(const float radius, const QVector3D position, const QVector3D direction) : GameObject(position, new SimpleSphere(radius)),
    radius(radius), direction(direction)
    {
            setPosition(position);
    }


    void Ball::doIt()
    {
        position.setX(position.x() + direction.x() * 0.05);
        position.setY(position.y() + direction.y() * 0.05);
            setPosition(position);
        if(position.x() < 0 || position.x() > 86)
            direction = hit(direction, QVector3D(0,1,0));
        if(position.y() > 70)
            direction = hit(direction, QVector3D(1,0,0));
    }

    QVector3D Ball::hit(QVector3D dir, QVector3D vec)
    {
        return -(dir - (vec * (2 * (QVector3D::dotProduct(dir, vec)))));
    }

