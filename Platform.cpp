#include "Platform.h"



Platform::Platform(const float width, const float height, const float depth, const QVector3D position)
	: GameObject(position, new SimpleCube(width, height, depth)), width(width), height(height), depth(depth)
{
}

void Platform::doIt()
{
	KeyboardInput *keyboard_input = InputRegistry::getInstance().getKeyboardInput();

	if (keyboard_input->isKeyPressed('h')) {
		position.setX(position.x() - 0.05);
	}
	else if (keyboard_input->isKeyPressed('j')) {
		position.setX(position.x() + 0.05);
	}
	setPosition(position);
}

