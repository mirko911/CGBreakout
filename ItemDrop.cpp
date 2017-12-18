#include "ItemDrop.h"

ItemDrop::ItemDrop(const int type, const int duration, const float value) :
    timer(0), type(type), duration(duration), value(value)
{
}

bool ItemDrop::isTimeLimitReached() const
{
    return timer >= duration;
}

int ItemDrop::getType() const
{
    return type;
}

float ItemDrop::getDuration() const
{
    return duration;
}

float ItemDrop::getValue() const
{
    return value;
}

ItemDrop ItemDrop::spawnRandomItemDrop()
{
    int type = getRandomNumber() % 5;
    int duration = 10000 + (getRandomNumber() % 20) * 200; //Something between 10 and 30 seconds
    int value = 0;
    return ItemDrop(type, duration, value);
}

void ItemDrop::increaseTimer()
{
    timer++;
}

int ItemDrop::getTimer() const
{
    return timer;
}
