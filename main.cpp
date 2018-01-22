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

#include "Game.h"

Node *initScene1();


void SceneManager::initScenes()
{
	Settings settings;
	settings.width = 90;
	settings.height = 70;
	settings.brick_height = 2;
	settings.brick_width = 4;
	settings.brick_depth = 2;
	settings.num_bricks_x = 14;
	settings.num_bricks_y = 10;
	settings.brick_offset_x = 2;
	settings.brick_offset_y = 2;
	settings.start_lives = 3;
    settings.platform_width = 10;
    settings.platform_height = 1;
    settings.platform_depth = 1;
    settings.platform_velocity = 0.1f;
    settings.ball_radius = 1;
    settings.ball_velocity = 0.05f;
    settings.score_multiplicator = 1.0f;

    Game * game = new Game(settings);

    FixedCamera *cam = new FixedCamera();
    RenderingContext *myContext = new RenderingContext(cam);

    unsigned int myContextNr = SceneManager::instance()->addContext(myContext);
    unsigned int myScene = SceneManager::instance()->addScene(game->initGameScene());
    /*ScreenRenderer *myRenderer =*/ new ScreenRenderer(myContextNr, myScene);

    //Vorsicht: Die Szene muss initialisiert sein, bevor das Fenster verändert wird (Fullscreen)
    SceneManager::instance()->setActiveScene(myScene);
    SceneManager::instance()->setActiveContext(myContextNr);
    SceneManager::instance()->getActiveContext()->setCamera(cam);

    SceneManager::instance()->setFullScreen();
} 
