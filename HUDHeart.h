#ifndef HUDHEART_H
#define HUDHEART_H

#include "GameObject.h"
#include "GeometryHandler.h"

class HUDHeart :
    public GameObject
{
public:
    HUDHeart(QVector3D position, Geometry * geometry);
};

#endif // HUDHEART_H
