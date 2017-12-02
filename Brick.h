#ifndef BRICK_H
#define BRICK_H

#include <qwidget.h>

#include "drawable.h"
#include "simplecube.h"
#include "transformation.h"

class Brick : public Drawable
{
private:
    //Width of the brick
	float width;
	//Height of the brick
	float height;
	//Depth of the brick
	float depth;
	//Health of the brick
	float health;
	//Is the block visible?
	bool isVisible;

	QVector3D position;

	Transformation * transformation;
	Node * node;
public:
	
	Brick(const float width, const float height, const float depth, const QVector3D position);

	//Sets the position of the brick
	void setPosition(const QVector3D position);
	//Sets the position of the brick
	void setPosition(const float x, const float y, const float z);

	virtual void beforeTraverseChilds(SGObjectVisitor& visitor) override;
    virtual void afterTraverseChilds() override;
	Node* getNode();
};

#endif // !BRICK_H
