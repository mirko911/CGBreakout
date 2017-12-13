#include "Platform.h"



Platform::Platform(const float width, const float height, const float depth, const QVector3D position)
	: GameObject(position, new SimpleCube(width, height, depth)), width(width), height(height), depth(depth)
{
    setPosition(position);

}

void Platform::setVelocity(const float _velocity)
{
	velocity = _velocity;
}

float Platform::getVelocity() const
{
	return velocity;
}

void Platform::moveLeft()
{
	position.setX(position.x() - velocity);
	setPosition(position);
}

void Platform::moveRight()
{
	position.setX(position.x() + velocity);
	setPosition(position);
}

