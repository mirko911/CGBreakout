#include "Game.h"



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

    platform = new Platform(10, 1, 1, QVector3D(center.x(), 1, 0));
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
    //Calculate new ball positions
    for (Ball * ball : balls) {
        QVector3D newPosition = (ball->getPosition() + ball->getDirection() * 0.05);

        if (newPosition.x() < 0 || newPosition.x() > settings.width) {
            ball->setDirection(ball->hit(QVector3D(0, 1, 0)));
        }
        else if (newPosition.y() < 0 || newPosition.y() > settings.height) {
            ball->setDirection(ball->hit(QVector3D(1, 0, 0)));
        }
        else {
            ball->setPosition(newPosition);
        }
    }

    for (auto it = balls.begin(); it != balls.end(); )
    //for (Ball * ball : balls)
    {

        QVector3D posBall = (*it)->getPosition();
        float radiusBall = (*it)->getRadius();
        for (auto br = bricks.begin(); br != bricks.end(); )
        {
            QVector3D posBrick = (*br)->getPosition();

            // Check collission between ball and horizontal brick sides
            if ((posBall.x() >= posBrick.x() - settings.brick_width/2) && (posBall.x() <= posBrick.x() + settings.brick_width/2))
            {
                if ((posBall.y() + radiusBall >= posBrick.y() - settings.brick_height/2) &&
                        (posBall.y() - radiusBall <= posBrick.y() + settings.brick_height/2))
                {
                    (*it)->setDirection((*it)->hit(QVector3D(1, 0, 0)));
                    posBall = (*it)->getDirection();
                    //br = hitBrick(br);
                    continue;
                }
            }

            // Check collission between ball and vertical brick sides
            if (((*it)->getPosition().y() >= (*br)->getPosition().y() - settings.brick_height/2) &&
                    ((*it)->getPosition().y() <= (*br)->getPosition().y() + settings.brick_height/2))
            {
                //if (((*it)->getPosition().x() + (*it)->getRadius() >= (*br)->getPosition().x() - settings.brick_width/2) &&
                        //((*it)->getPosition().x() - (*it)->getRadius() <= (*br)->getPosition().x() + settings.brick_width/2))
                if ((posBall.x() + radiusBall >= (*br)->getPosition().x() - settings.brick_width/2) &&
                        (posBall.x() - radiusBall <= (*br)->getPosition().x() + settings.brick_width/2))
                {
                    (*it)->setDirection((*it)->hit(QVector3D(0, 1, 0)));
                    posBall = (*it)->getDirection();
                    //br = hitBrick(br);
                    continue;
                }
            }
            ++br;
        }

        // Check collission between platform and bottom point of ball
        if ((posBall.x() + radiusBall >= platform->getPosition().x() - platform->getWidth()/2) &&
                (posBall.x() - radiusBall <= platform->getPosition().x() + platform->getWidth()/2))
        {
            if ((posBall.y() + radiusBall >= platform->getPosition().y() - settings.brick_height/4) &&
                    (posBall.y() - radiusBall <= platform->getPosition().y() + settings.brick_height/4))
            {
                (*it)->setDirection((*it)->hit(QVector3D(1, 0, 0)));
                (*it)->setPosition(posBall.x() + 0.1, posBall.y() + 0.1, 0);
                continue;
            }
        }
        ++it;

    }

    if (keyboard_input->isKeyPressed('a') && platform->getPosition().x() > 0) {
        platform->moveLeft();
    }
    else if (keyboard_input->isKeyPressed('d') && platform->getPosition().x() < settings.width) {
        platform->moveRight();
    }

}
