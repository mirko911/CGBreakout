#ifndef ITEMDROPDRAWABLE_H
#define ITEMDROPDRAWABLE_H

#include "GameObject.h"
#include "ItemDrop.h"

class ItemDropDrawable :
    public GameObject
{
private:
    ItemDrop itemDrop;
public:
    ItemDropDrawable(QVector3D position, Geometry * geometry, ItemDrop itemDrop);
    ItemDrop &getItemDrop();
};

#endif // !ITEMDROPDRAWABLE_H
