#include "Brick.h"


Brick::Brick(const float width, const float height, const float depth, const QVector3D position) :
	GameObject(position, new SimpleCube(width, height, depth)),
	width(width), height(height), depth(depth), health(100),
	isVisible(true)
{
	setPosition(position);
}
