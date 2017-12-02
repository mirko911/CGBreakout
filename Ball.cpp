#include "Ball.h"


Ball::Ball(const float radius, const QVector3D position) :  Drawable(new SimpleSphere(radius)),
	radius(radius), position(position), transformation(new Transformation()), node(new Node(this))
{
	setPosition(position);
}

void Ball::setPosition(const QVector3D position)
{
	transformation->resetTrafo();
	transformation->translate(position.x(), position.y(), position.z());
}

void Ball::setPosition(const float x, const float y, const float z)
{
	transformation->resetTrafo();
	transformation->translate(x, y, z);
}

void Ball::beforeTraverseChilds(SGObjectVisitor & visitor)
{
	transformation->activate();
	Drawable::beforeTraverseChilds(visitor);
}

void Ball::afterTraverseChilds()
{
	transformation->deActivate();
}

void Ball::doIt()
{
	position.setX(position.x() + 0.05);
	setPosition(position);
}

Node * Ball::getNode()
{
	return node;
}