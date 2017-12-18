#ifndef BRICK_H
#define BRICK_H

#include "color.h"
#include "GameObject.h"
#include "GeometryHandler.h"


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
    bool visible;
public:

    Brick(const float width, const float height, const float depth, const QVector3D position);
    bool isVisible() const;
    void setInvisible();
    void decreaseHealth(const float ammount);
};

#endif // !BRICK_H
