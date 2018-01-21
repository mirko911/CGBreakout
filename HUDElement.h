#ifndef HUDELEMENT_H

#include <qvector3d.h>
#include <string.h>
#include "GeometryHandler.h"
#include "node.h"
#include "GameObject.h"
#include <vector>
#include "color.h"

class HUDElement
{
private:
    QVector3D position;
    int value = 0;
    int length;
    std::string text;
    std::vector<GameObject *> gameObjects;
public:
    HUDElement() {};
    HUDElement(const QVector3D position, const int length);
    Node * setup();
    void setValue(const int value_);
};

#endif // !HUDELEMENT_H

