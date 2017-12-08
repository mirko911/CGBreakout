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
    float velocity = 0.2f;
public:
	Platform(const float width, const float height, const float depth, const QVector3D position);
	virtual void doIt() override;
    void setVelocity(const float _velocity);
    float getVelocity() const;
};

#endif // !PLATFORM_H
