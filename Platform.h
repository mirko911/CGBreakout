#ifndef PLATFORM_H
#define PLATFORM_H


#include "GameObject.h"

#include "simplecube.h"
#include "inputregistry.h"
#include "idleobserver.h"

#include <iostream>

class Platform :
	public GameObject, IdleObserver
{
private:
	float width;
	float height;
	float depth;
public:
	Platform(const float width, const float height, const float depth, const QVector3D position);
	virtual void doIt() override;
};

#endif // !PLATFORM_H
