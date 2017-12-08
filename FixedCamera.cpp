#include "FixedCamera.h"


void FixedCamera::doIt()
{
    //Allow cam modifications when you press m
    KeyboardInput* keyIn = InputRegistry::getInstance().getKeyboardInput();
    if (keyIn->isKeyPressed('m'))
    {
        modify_cam = true;
    }else if(keyIn->isKeyPressed('b')){
        CamData data = getCamData();
        int x = 0; //Set breakpoint here to get the CamData Struct
        x++; //Needed to avoid the unused var warning
    }



    if(modify_cam){
        ControllableCamera::doIt();
    }

	//Set position once
    if (!executed) {
        setPosition(45, 33, 56);
        executed = true;
	}
}
