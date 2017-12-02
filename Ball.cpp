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
}

