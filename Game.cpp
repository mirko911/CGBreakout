#include "Game.h"

#include "trianglemesh.h"
#include "simplecube.h"
#include "simplesphere.h"
#include "scenemanager.h"
#include "FixedCamera.h"
#include "color.h"


Game::Game(Settings &settings) : IdleObserver(0), settings(settings) {
    keyboard_input = InputRegistry::getInstance().getKeyboardInput();
    balls.reserve(1);
    bricks.reserve(settings.num_bricks_x * settings.num_bricks_y);
    center = QVector3D(settings.width / 2.0f, settings.height / 2.0f, 0);
    lives = settings.start_lives;
    score = 0;
    score_multiplicator = settings.score_multiplicator;
}

Node * Game::initGameScene()
{
    GeometryHandler &geometryHandler = GeometryHandler::instance();
    geometryHandler.addGeometry("pokeball", new TriangleMesh(static_cast<QString>(SRCDIR) + static_cast<QString>("/obj/pokeball.obj")));
    geometryHandler.addGeometry("ball", new SimpleSphere(settings.ball_radius));
    geometryHandler.addGeometry("platform", new SimpleCube(settings.platform_width, settings.platform_height, settings.platform_depth));
    geometryHandler.addGeometry("platform_wide", new SimpleCube(settings.platform_width * 2, settings.platform_height, settings.platform_depth));
    geometryHandler.addGeometry("brick", new SimpleCube(settings.brick_width, settings.brick_height, settings.brick_depth));
    geometryHandler.addGeometry("heart", new TriangleMesh(static_cast<QString>(SRCDIR) + static_cast<QString>("/obj/heart.obj")));
    geometryHandler.addGeometry("x2", new TriangleMesh(static_cast<QString>(SRCDIR) + static_cast<QString>("/obj/x2.obj")));

    Node * mainNode = new Node();

    Ball * ball = new Ball(settings.ball_radius, QVector3D(30, 3, 0), settings.ball_velocity, QVector3D(0, 1, 0));
    mainNode->addChild(ball->getNode());
    balls.push_back(ball);

    platform = new Platform(settings.platform_width, settings.platform_height, settings.platform_depth, QVector3D(center.x(), 1, 0), settings.platform_velocity);
    mainNode->addChild(platform->getNode());

    int brick_width_with_offset = settings.brick_width + settings.brick_offset_x;
    int brick_height_with_offset = settings.brick_height + settings.brick_offset_y;

    int offset_center_x = center.x() - (settings.num_bricks_x * brick_width_with_offset / 2) + 2; //the bricks should be centered

    Color* color;

    float x_position, y_position;
    for (int j = 0; j < settings.num_bricks_y; j++) {
        for (int i = 0; i < settings.num_bricks_x; i++) {
            x_position = offset_center_x + (i * brick_width_with_offset);
            y_position = center.y() - 10 + (j * brick_height_with_offset);

            Brick * brick = new Brick(
                settings.brick_width, settings.brick_height, settings.brick_depth,
                QVector3D(x_position, y_position, 0)
            );
            color = brick->getProperty<Color>();
            color->setValue(1.0f, 1.0f * (1.f - (float)j / (settings.num_bricks_y - 1.f)), 0); //Color gradient yellow to red
            bricks.push_back(brick);
            mainNode->addChild(brick->getNode());
        }
    }


    gameSceneRootNode = mainNode;
    return mainNode;
}

Node * Game::initStartScene()
{
    Node * mainNode = new Node();
    return mainNode;
}

Node * Game::initEndScene()
{
    Node * mainNode = new Node();

    return mainNode;
}

void Game::doIt()
{
    if (lives <= 0) {
        //Game is over
        return;
    }

    int i = 0;

    //Loop through all active item drops [wide_platform,speed,score]
    for (ItemDrop &drop : activeItemDrops) {
        if (drop.isTimeLimitReached()) {
            onItemDropLimitReached(drop);
            activeItemDrops.erase(activeItemDrops.begin() + i);
        }
        drop.increaseTimer();
        i++;
    }

    //Render new positions of itemdrops
    i = -1; //Start with -1, because I don't know where the loop ends
    for (ItemDropDrawable *itemDropDrawable : itemDrops) {
        i++;
        QVector3D newPosition = (itemDropDrawable->getPosition() + QVector3D(0,-1,0) * 0.05);

        if (newPosition.y() < 0) {
            itemDropDrawable->setEnabled(false);
            itemDrops.erase(itemDrops.begin() + i);
            continue;
        }
        // Check collission between platform and bottom point of Item
        else if ((newPosition.x() + 1 >= platform->getPosition().x() - platform->getWidth() / 2) &&
            (newPosition.x() -1 <= platform->getPosition().x() + platform->getWidth() / 2) &&
            (newPosition.y() + 1 >= platform->getPosition().y() - settings.platform_height / 2) &&
            (newPosition.y() - 1 <= platform->getPosition().y() + settings.platform_height / 2))
        {
            itemDropDrawable->setEnabled(false);
            itemDrops.erase(itemDrops.begin() + i);
            onItemDropCatch(itemDropDrawable->getItemDrop());
            continue;
        }

        itemDropDrawable->setPosition(newPosition);
    }

    //Calculate new ball positions
    i = -1;
    for (Ball * ball : balls) {
        i++;
        QVector3D newPosition = (ball->getPosition() + ball->getDirection() * settings.ball_velocity);

        //Check collision with walls
        if (newPosition.x() < 0 || newPosition.x() > settings.width) {
            ball->setDirection(ball->hit(QVector3D(0, 1, 0)));
            continue;
        }
        else if (/*newPosition.y() < 0 || */ newPosition.y() > settings.height) {
            ball->setDirection(ball->hit(QVector3D(1, 0, 0)));
            continue;
        }
        else if (newPosition.y() < 0) {
            ball->setEnabled(0);
            balls.erase(balls.begin() + i);
        }
        // Check collission between platform and bottom point of ball
        else if ((newPosition.x() + ball->getRadius() >= platform->getPosition().x() - platform->getWidth() / 2) &&
            (newPosition.x() - ball->getRadius() <= platform->getPosition().x() + platform->getWidth() / 2) &&
            (newPosition.y() + ball->getRadius() >= platform->getPosition().y() - settings.platform_height / 2) &&
            (newPosition.y() - ball->getRadius() <= platform->getPosition().y() + settings.platform_height / 2))
        {
            float platformHit = newPosition.x() - platform->getPosition().x();
            if (platformHit < -5 || platformHit < 5) {
                platformHit = (int)platformHit;
            }
            QVector3D direction = QVector3D(0 + platformHit / (platform->getWidth() / 2 + ball->getRadius()), 1 - platformHit / (platform->getWidth() / 2 + ball->getRadius()), 0);
            if (platformHit < 0) {
                direction.setY(1 + (platformHit + platform->getWidth() / settings.platform_width) / (platform->getWidth() / 2 + ball->getRadius()));
            }
            ball->setDirection(direction.normalized());
            continue;
        }

        bool foundColission = false;
        for (Brick * brick : bricks) {

            //Skip invisible bricks
            if (!brick->isVisible()) {
                continue;
            };

            // Check collission between ball and horizontal brick sides
            if ((newPosition.x() + ball->getRadius() >= brick->getPosition().x() - settings.brick_width / 2) &&
                (newPosition.x() - ball->getRadius() <= brick->getPosition().x() + settings.brick_width / 2) &&
                (newPosition.y() + ball->getRadius() >= brick->getPosition().y() - settings.brick_height / 2) &&
                (newPosition.y() - ball->getRadius() <= brick->getPosition().y() + settings.brick_height / 2))
            {
                ball->setDirection(ball->hit(QVector3D(1, 0, 0)));
                onBrickCollision(brick);
                foundColission = true;
                break;
            }

            // Check collission between ball and vertical brick sides
            if ((newPosition.y() + ball->getRadius() >= brick->getPosition().y() - settings.brick_height / 2) &&
                (newPosition.y() - ball->getRadius() <= brick->getPosition().y() + settings.brick_height / 2) &&
                (newPosition.x() + ball->getRadius() >= brick->getPosition().x() - settings.brick_width / 2) &&
                (newPosition.x() - ball->getRadius() <= brick->getPosition().x() + settings.brick_width / 2))
            {
                ball->setDirection(ball->hit(QVector3D(0, 1, 0)));
                onBrickCollision(brick);
                foundColission = true;
                break;
            }
        }

        if (!foundColission) {
            ball->setPosition(newPosition);
        }
    }

    if (balls.empty() && lives > 0) {
        lives--;
        Ball * ball = new Ball(settings.ball_radius, QVector3D(30, 3, 0), settings.ball_velocity, QVector3D(0, 1, 0));
        gameSceneRootNode->addChild(ball->getNode());
        balls.push_back(ball);
    }
    else if (balls.empty() && lives <= 0) {
        std::cout << "GAME OVER!" << std::endl;
        return;
    }

    if (keyboard_input->isKeyPressed('a') && platform->getPosition().x() > 0) {
        platform->moveLeft();
    }
    else if (keyboard_input->isKeyPressed('d') && platform->getPosition().x() < settings.width) {
        platform->moveRight();
    }
    else if (keyboard_input->isKeyPressed('t')) {
        int x = 0;
        x++;
    }
}

void Game::onBrickCollision(Brick *brick) {
    brick->decreaseHealth(100);
    score += (score_multiplicator * 5);
   // std::cout << "Score: " + score << " " << "Lives: " + lives << std::endl;

    ItemDrop drop = ItemDrop::spawnRandomItemDrop();
    ItemDropDrawable * itemDropDrawable;
    switch (drop.getType()) {
    case ITEM_EXTRALIVE:{
        itemDropDrawable = new ItemDropDrawable(brick->getPosition(), GeometryHandler::instance().getGeometry("heart"), drop);
        Color * color = itemDropDrawable->getProperty<Color>();
        color->setValue(1, 0, 0);
        break;}
    case ITEM_SCORE:{
        itemDropDrawable = new ItemDropDrawable(brick->getPosition(), GeometryHandler::instance().getGeometry("x2"), drop);
        Color * color = itemDropDrawable->getProperty<Color>();
        color->setValue(1, 1, 1);
        break;}
    case ITEM_EXTRABALL:{
        itemDropDrawable = new ItemDropDrawable(brick->getPosition(), GeometryHandler::instance().getGeometry("ball"), drop);
        Color * color = itemDropDrawable->getProperty<Color>();
        color->setValue(1, 1, 0);
        break;}
    default:{
        itemDropDrawable = new ItemDropDrawable(brick->getPosition(), GeometryHandler::instance().getGeometry("ball"), drop);
        Color * color = itemDropDrawable->getProperty<Color>();
        color->setValue(1, 0, 0);
        break;
    }
    }

    itemDrops.push_back(itemDropDrawable);
    gameSceneRootNode->addChild(itemDropDrawable->getNode());
}

void Game::onItemDropCatch(ItemDrop &itemDrop) {
    //Only push the item drop into the list when the drop has a limited time
    switch (itemDrop.getType()) {
    case ITEM_SPEED: {
        for (Ball *ball : balls) {
            ball->setVelocity(settings.ball_velocity * 2);
        }
        activeItemDrops.push_back(itemDrop);
        break;
    }
    case ITEM_WIDEPLATFORM: {
        platform->setProperty<Geometry>(GeometryHandler::instance().getGeometry("platform_wide"));
        platform->setWidth(settings.platform_width * 2);
        activeItemDrops.push_back(itemDrop);
        break;
    }

    case ITEM_SCORE: {
        score_multiplicator = 2;
        activeItemDrops.push_back(itemDrop);
        break;
    }

    case ITEM_EXTRABALL: {
        Ball * ball = new Ball(settings.ball_radius, QVector3D(platform->getPosition().x(), platform->getPosition().y() + 1, 0), settings.ball_velocity, QVector3D(0, -1, 0));
        balls.push_back(ball);
        gameSceneRootNode->addChild(ball->getNode());
        break;
    }
    case ITEM_EXTRALIVE: {
        lives++;
        break;
    }
    }
    std::cout << "Got ItemDrop Type:" << itemDrop.getType() << std::endl;
}

void Game::onItemDropLimitReached(ItemDrop & itemDrop)
{
    switch (itemDrop.getType()) {
    case ITEM_SPEED: {
        for (Ball *ball : balls) {
            ball->setVelocity(settings.ball_velocity);
        }
        break;
    }
    case ITEM_WIDEPLATFORM: {
        platform->setProperty<Geometry>(GeometryHandler::instance().getGeometry("platform"));
        platform->setWidth(settings.platform_width);
        break;
    }
    case ITEM_SCORE: {
        score_multiplicator = settings.score_multiplicator;
        break;
    }
    }
}
