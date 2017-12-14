#include "Brick.h"


Brick::Brick(const float width, const float height, const float depth, const QVector3D position) :
    GameObject(position, new SimpleCube(width, height, depth)),
    width(width), height(height), depth(depth), health(100),
    visible(true)
{
    setPosition(position);
}

bool Brick::isVisible() const
{
    return visible;
}

void Brick::setInvisible()
{
    visible = false;
    Color * color = getProperty<Color>();
    color->setValue(0.5f,0.5f,0.5f,0.3f);
}

void Brick::decreaseHealth(const float ammount)
{
    health -= ammount;
    if (health <= 0) {
        setInvisible();
    }
}
