#ifndef ITEMDROP_H
#define ITEMDROP_H

#include <random>
#include <Ball.h>

inline int getRandomNumber() {
    thread_local std::mt19937 gen{ std::random_device{}() };
    thread_local std::uniform_int_distribution<int> pick{ 0, 1000 };
    return pick(gen);
}
//       CAR           PLATFORM         x2             Ball Symbol   Heart Symbol
enum { ITEM_SPEED, ITEM_WIDEPLATFORM, ITEM_SCORE, ITEM_EXTRABALL, ITEM_EXTRALIVE };

class ItemDrop {
private:
    int timer;
    int type;
    int duration;
    float value;
public:
    ItemDrop(const int type, const int duration, const float value);
    bool isTimeLimitReached() const;
    int getType() const;
    float getDuration() const;
    float getValue() const;
    static ItemDrop spawnRandomItemDrop();
    void increaseTimer();
    int getTimer() const;
};


#endif // !ITEMDROP_H
