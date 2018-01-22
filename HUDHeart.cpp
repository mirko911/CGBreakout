#include "HUDHeart.h"

HUDHeart::HUDHeart(QVector3D position, Geometry *geometry) : GameObject(position, geometry)
{
    setPosition(position);
}
