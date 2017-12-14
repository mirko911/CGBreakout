#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>

#include "node.h"
#include "idleobserver.h"
#include "inputregistry.h"
#include "color.h"

#include "Ball.h"
#include "Platform.h"
#include "Brick.h"
#include "ItemDrop.h"

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
};

class Game : public IdleObserver
{
private:
<<<<<<< HEAD
	Settings settings;
	KeyboardInput *keyboard_input;
	std::vector<Ball*> balls;
	std::vector<Brick*> bricks;
	Platform * platform;
	QVector3D center;
	int lives;
=======
    Settings settings;
    KeyboardInput *keyboard_input;
    std::vector<Ball*> balls;
    std::vector<Brick*> bricks;
    std::vector<ItemDrop> activeItemDrops;
    std::vector<ItemDropBall*> itemDrops;
    Platform * platform;
    QVector3D center;
    int lives;
    Node * gameSceneRootNode;
    void onBrickCollision(Brick* brick);
    void onItemDropCatch(ItemDrop &itemDrop);
>>>>>>> origin/dev
public:
	Game(Settings &settings);
	Node * initStartScene();
	Node * initGameScene();
	Node * initEndScene();
	virtual void doIt() override;
};



#endif // !GAME_H
