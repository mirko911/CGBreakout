#ifndef BRICK_H
#define BRICK_H

#include <qwidget.h>

#include "drawable.h"
#include "simplecube.h"
#include "transformation.h"

#include "GameObject.h"

class Brick : public GameObject
{
private:
    //Width of the brick
    float width;
    //Height of the brick
    float height;
    //Depth of the brick
    float depth;
    //Health of the brick
    float health;
    //Is the block visible?
    bool isVisible;
public:

    Brick(const float width, const float height, const float depth, const QVector3D position);
};

#endif // !BRICK_H
