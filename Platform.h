#ifndef PLATFORM_H
#define PLATFORM_H


#include "GameObject.h"

#include "simplecube.h"

#include <iostream>

class Platform :
	public GameObject
{
private:
	float width;
	float height;
	float depth;
    float velocity = 0.2f;
public:
	Platform(const float width, const float height, const float depth, const QVector3D position);
    void setVelocity(const float _velocity);
    float getVelocity() const;
	void moveLeft();
	void moveRight();
};

#endif // !PLATFORM_H
