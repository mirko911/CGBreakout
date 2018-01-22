#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>

#include "node.h"
#include "idleobserver.h"
#include "inputregistry.h"
#include "color.h"
#include "window.h"

#include "GeometryHandler.h"
#include "ItemDropDrawable.h"
#include "Ball.h"
#include "Platform.h"
#include "Brick.h"
#include "ItemDrop.h"
#include "HUDElement.h"
#include "HUDHeart.h"

struct Settings {
	int width;
	int height;
	int num_bricks_x;
	int num_bricks_y;
	int brick_width;
	int brick_height;
	int brick_depth;
	int brick_offset_x;
	int brick_offset_y;
	int start_lives;
    int platform_width;
    int platform_height;
    int platform_depth;
    float platform_velocity;
    int ball_radius;
    float ball_velocity;
    int score_multiplicator;
};

class Game : public IdleObserver
{
private:
    Settings settings;
    KeyboardInput *keyboard_input;
    std::vector<Ball*> balls;
    std::vector<Brick*> bricks;
    std::vector<ItemDrop> activeItemDrops;
    std::vector<ItemDropDrawable*> itemDrops;
    Platform * platform;
    QVector3D center;
    int lives;
    int score;
    float score_multiplicator;
    HUDElement score_hud;
    HUDElement lives_hud;
    HUDHeart * heart_hud;
    Node * gameSceneRootNode;
    void onBrickCollision(Brick* brick);
    void onItemDropCatch(ItemDrop &itemDrop);
    void onItemDropLimitReached(ItemDrop &itemDrop);
    bool running = false;
public:
	Game(Settings &settings);
	Node * initStartScene();
	Node * initGameScene();
	Node * initEndScene();
	virtual void doIt() override;
};



#endif // !GAME_H
