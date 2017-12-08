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

    Platform * platform = new Platform(3, 1, 1, QVector3D(0, 0, 0));
    mainNode->addChild(platform->getNode());


    for (unsigned j = 0; j < 10; j++) {
        for (unsigned i = 0; i < 22; i++) {
            Brick * brick = new Brick(2, 1, 1, QVector3D(0 + i * 3, 30 + j * 2, 0));
            bricks.push_back(brick);
            mainNode->addChild(brick->getNode());
        }
    }

    /*
    for (unsigned i = 0; i < 10; i++) {
        for (unsigned j = 0; j < 6; j++) {
            Brick * brick = new Brick(2, 1, 1, QVector3D(i * 3, j * 3, 0));
            brick->getProperty<Color>()->setValue(0, 255, 255);
            bricks.push_back(brick);
            mainNode->addChild(brick->getNode());
        }
    }
    */

    return mainNode;
}
