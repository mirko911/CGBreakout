#ifndef BALL_H
#define BALL_H

#include <qwidget.h>

#include "idleobserver.h"
#include "simplesphere.h"

#include "GameObject.h"

class Ball : public GameObject, public IdleObserver
{
private:
	float radius;
public:
	Ball(const float radius, const QVector3D position);
	virtual void doIt() override;
};

#endif // !BALL_H
