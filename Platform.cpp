#include "Platform.h"



Platform::Platform(const float width, const float height, const float depth, const QVector3D position)
	: GameObject(position, new SimpleCube(width, height, depth)), width(width), height(height), depth(depth)
{
}

void Platform::doIt()
{
	KeyboardInput *keyboard_input = InputRegistry::getInstance().getKeyboardInput();

	if (keyboard_input->isKeyPressed('a')) {
		position.setX(position.x() - velocity);
		std::cout << position.x() << " " << position.y() << std::endl;
	}
	else if (keyboard_input->isKeyPressed('d')) {
		position.setX(position.x() + velocity);
		std::cout << position.x() << " " << position.y() << std::endl;
	}

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

