#ifndef FIXEDCAMERA_H
#define FIXEDCAMERA_H

#include "controllablecamera.h"
#include "idleobserver.h"
#include "inputregistry.h"

class FixedCamera : public ControllableCamera
{
private:
	bool executed = false;
    bool modify_cam = false;
public:
	virtual void doIt() override;
};


#endif // !FIXEDCAMERA_H


