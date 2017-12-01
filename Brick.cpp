#include "Brick.h"


Brick::Brick(const float width, const float height, const float depth, const QVector3D position) :
	width(width), height(height), depth(depth), health(100),
	isVisible(true), position(position), node(new Node(this)), Drawable(new SimpleCube(width, height, depth)) 
{
	transformation = new Transformation();
	setPosition(position);
}

void Brick::setPosition(const QVector3D position)
{
	transformation->resetTrafo();
	transformation->translate(position.x(), position.y(), position.z());
}

void Brick::setPosition(const float x, const float y, const float z)
{
	transformation->resetTrafo();
	transformation->translate(x, y, z);
}

void Brick::beforeTraverseChilds(SGObjectVisitor & visitor)
{
	transformation->activate();
    Drawable::beforeTraverseChilds(visitor);
}

void Brick::afterTraverseChilds()
{
    transformation->deActivate();
}

Node * Brick::getNode()
{
	return node;
}

