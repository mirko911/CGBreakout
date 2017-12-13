#include "GameObject.h"



GameObject::GameObject(Geometry * geometry) : Drawable(geometry), position(0, 0, 0), transformation(new Transformation), node(new Node(this))
{
}

GameObject::GameObject(const QVector3D position, Geometry * geometry) : Drawable(geometry), position(position), transformation(new Transformation), node(new Node(this))
{
}


void GameObject::setPosition(const QVector3D _position)
{
	position = _position;
	transformation->resetTrafo();
	transformation->translate(_position.x(), _position.y(), _position.z());
}

void GameObject::setPosition(const float x, const float y, const float z)
{
	position = QVector3D(x,y,z);
	transformation->resetTrafo();
	transformation->translate(x, y, z);
}

void GameObject::beforeTraverseChilds(SGObjectVisitor & visitor)
{
	transformation->activate();
	Drawable::beforeTraverseChilds(visitor);
}

void GameObject::afterTraverseChilds()
{
	transformation->deActivate();
}

Node * GameObject::getNode()
{
	return node;
}

QVector3D GameObject::getPosition() const
{
	return position;
}

Transformation * GameObject::getTransformation() const
{
	return transformation;
}
