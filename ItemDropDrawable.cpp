#include "ItemDropDrawable.h"

ItemDropDrawable::ItemDropDrawable(QVector3D position, Geometry * geometry, ItemDrop itemDrop) : GameObject(position, geometry), itemDrop(itemDrop)
{
}

ItemDrop & ItemDropDrawable::getItemDrop()
{
    return itemDrop;
}
