#include "Game.h"

#include "scenemanager.h"
#include "FixedCamera.h"
#include "color.h"


Game::Game(Settings &settings) : IdleObserver(0), settings(settings) {
    keyboard_input = InputRegistry::getInstance().getKeyboardInput();
    balls.reserve(1);
    bricks.reserve(settings.num_bricks_x * settings.num_bricks_y);
    center = QVector3D(settings.width / 2.0f, settings.height / 2.0f, 0);
    lives = settings.start_lives;
}

Node * Game::initGameScene()
{
    Node * mainNode = new Node();

    Ball * ball = new Ball(settings.ball_radius, QVector3D(30, 3, 0), QVector3D(0, -1, 0));
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
    //Render new positions of itemdrops
    int i = -1; //Start with -1, because I don't know where the loop ends
    for (ItemDropBall *ball : itemDrops) {
        i++;
        QVector3D newPosition = (ball->getPosition() + ball->getDirection() * 0.05);

        if (newPosition.y() < 0) {
            ball->setEnabled(false);
            itemDrops.erase(itemDrops.begin() + i);
            continue;
        }
        // Check collission between platform and bottom point of ball
        else if ((newPosition.x() + ball->getRadius() >= platform->getPosition().x() - 10 / 2) &&
            (newPosition.x() - ball->getRadius() <= platform->getPosition().x() + 10 / 2) &&
            (newPosition.y() + ball->getRadius() >= platform->getPosition().y() - settings.brick_height / 4) &&
            (newPosition.y() - ball->getRadius() <= platform->getPosition().y() + settings.brick_height / 4))
        {
            ball->setEnabled(false);
            itemDrops.erase(itemDrops.begin() + i);
            onItemDropCatch(ball->getItemDrop());
            continue;
        }

        ball->setPosition(newPosition);
    }

    //Calculate new ball positions
    for (Ball * ball : balls) {
        QVector3D newPosition = (ball->getPosition() + ball->getDirection() * settings.ball_velocity);

        //Check collision with walls
        if (newPosition.x() < 0 || newPosition.x() > settings.width) {
            ball->setDirection(ball->hit(QVector3D(0, 1, 0)));
            continue;
        }
        else if (newPosition.y() < 0 || newPosition.y() > settings.height) {
            ball->setDirection(ball->hit(QVector3D(1, 0, 0)));
            continue;
        }
        // Check collission between platform and bottom point of ball
        else if ((newPosition.x() + ball->getRadius() >= platform->getPosition().x() - 10 / 2) &&
            (newPosition.x() - ball->getRadius() <= platform->getPosition().x() + 10 / 2) &&
            (newPosition.y() + ball->getRadius() >= platform->getPosition().y() - settings.brick_height / 4) &&
            (newPosition.y() - ball->getRadius() <= platform->getPosition().y() + settings.brick_height / 4))
        {
            float platformHit = newPosition.x() - platform->getPosition().x();
            std::cout << platformHit << std::endl;
            if(platformHit < -5 || platformHit < 5) {
                platformHit = (int) platformHit;
            }
            QVector3D direction = QVector3D(0 + platformHit / (platform->getWidth() / 2 + ball->getRadius()), 1 -  platformHit / (platform->getWidth() / 2 + ball->getRadius()), 0);
            if(platformHit < 0) {
                direction.setY(1 + platformHit / (platform->getWidth() / 2 + ball->getRadius()));
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
    ItemDropBall * dropBall = new ItemDropBall(brick->getPosition());
    Color * color = dropBall->getProperty<Color>();
    color->setValue(255,255,0);
    itemDrops.push_back(dropBall);
    gameSceneRootNode->addChild(dropBall->getNode());
}

void Game::onItemDropCatch(ItemDrop &itemDrop) {
    activeItemDrops.push_back(itemDrop);
    switch (itemDrop.getType()) {
    case ITEM_EXTRABALL: {

        Ball * ball = new Ball(settings.ball_radius, QVector3D(getRandomNumber() % settings.width, 3, 0), QVector3D(0, -1, 0));
        balls.push_back(ball);
        gameSceneRootNode->addChild(ball->getNode());
        break;
    }
    case ITEM_SPEED: {
        for (Ball *ball : balls) {
            //@todo implement
        }
        break;
    }
    case ITEM_ROTATECAM: {
        Camera *cam = SceneManager::instance()->getActiveContext()->getCamera();
        //cam->rotate(0, 180, 0);
        break;
    }
    }
    std::cout << "Got ItemDrop Type:" << itemDrop.getType() << std::endl;
}
