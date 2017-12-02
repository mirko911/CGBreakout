#ifndef BALL_H
#define BALL_H

#include <qwidget.h>

#include "idleobserver.h"
#include "drawable.h"
#include "transformation.h"
#include "simplesphere.h"

class Ball : public Drawable, public IdleObserver
{
private:
	float radius;
	QVector3D position;

	Transformation * transformation;
	Node * node;
public:
	Ball(const float radius, const QVector3D position);

	//Sets the position of the brick
	void setPosition(const QVector3D position);
	//Sets the position of the brick
	void setPosition(const float x, const float y, const float z);

	virtual void beforeTraverseChilds(SGObjectVisitor& visitor) override;
	virtual void afterTraverseChilds() override;
	virtual void doIt() override;
	Node* getNode();
};

#endif // !BALL_H
