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
    QVector3D velocity;
    QVector3D direction;
public:
	Ball(const float radius, const QVector3D position, const QVector3D direction);
	virtual void doIt() override;
    QVector3D hit(QVector3D vec, QVector3D dir);
};

#endif // !BALL_H
