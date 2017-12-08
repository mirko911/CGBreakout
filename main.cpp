#include "opengl.h"
#include "window.h"
#include "screenrenderer.h"
#include "scenemanager.h"
#include "transformation.h"
#include "keyboardtransformation.h"
#include "camera.h"
#include "color.h"
#include "controllablecamera.h"
#include "ui_dockwidget.h"

#include <vector>
#include "Brick.h"
#include "Ball.h"
#include "Platform.h"
#include "FixedCamera.h"

#include "window.h"
#include "simplesphere.h"

Node *initScene1();


void SceneManager::initScenes()
{
    FixedCamera *cam = new FixedCamera();
    RenderingContext *myContext = new RenderingContext(cam);

    unsigned int myContextNr = SceneManager::instance()->addContext(myContext);
    unsigned int myScene = SceneManager::instance()->addScene(initScene1());
    ScreenRenderer *myRenderer = new ScreenRenderer(myContextNr, myScene);

    //Vorsicht: Die Szene muss initialisiert sein, bevor das Fenster verändert wird (Fullscreen)
    SceneManager::instance()->setActiveScene(myScene);
    SceneManager::instance()->setActiveContext(myContextNr);
    SceneManager::instance()->getActiveContext()->setCamera(cam);
    //SceneManager::instance()->setFullScreen();
}

Node *initScene1()
{
    std::vector<Brick *> bricks;
    bricks.reserve(30);

    Node * mainNode = new Node();


    Ball * ball = new Ball(1, QVector3D(0, 0, 0));
    mainNode->addChild(ball->getNode());


    Drawable * centerBall = new Drawable(new SimpleSphere(0.1));
    Node * centerNode = new Node(centerBall);
    mainNode->addChild(centerNode);



    Platform * platform = new Platform(0.1f, 0.1f, 1, QVector3D(0, 0, 0));
    mainNode->addChild(platform->getNode());

    Color* color;

    int width = 90; //estimated value
    int height = 56; //estimated value

    //@todo move the complete brick generation to extra function?
    int brick_width = 4;
    int brick_height = 2;
    int brick_offset_x = 2;
    int brick_offset_y = 2;
    int brick_amount_x = 14;
    int brick_amount_y = 10;

    int center_x = width / 2;
    int center_y = height / 2;
    int offset_center_x = center_x - (brick_amount_x / 2 * (brick_width + brick_offset_x)) + 2; //the bricks should be centered

    int x_position;
    int y_position;


    for (unsigned j = 0; j < brick_amount_y; j++) {
        for (unsigned i = 0; i < brick_amount_x; i++) {

            x_position = offset_center_x + (i * brick_width) + (i * brick_offset_x);
            y_position = center_y + (j * brick_height) + (j * brick_offset_y);

            Brick * brick = new Brick(4, 2, 2, QVector3D(x_position, y_position, 0));
            color = brick->getProperty<Color>();
            color->setValue(1.0f, 1.0f * (1.f - (float)j/(brick_amount_y -1.f)),0); //Color gradient yellow to red
            bricks.push_back(brick);
            mainNode->addChild(brick->getNode());
        }
    }



    return mainNode;
}
