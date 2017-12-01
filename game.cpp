#include "opengl.h"
#include "window.h"
#include "screenrenderer.h"
#include "scenemanager.h"
#include "transformation.h"
#include "keyboardtransformation.h"
#include "controllablecamera.h"
#include "color.h"

#include "ui_dockwidget.h"

#include <vector>
#include "Brick.h"
#include "transformation.h"
#include "simplesphere.h"

Node *initScene1();

void SceneManager::initScenes()
{
    Ui_FPSWidget *lDock;
    QDockWidget *lDockWidget = new QDockWidget(QString("FPS"), SceneManager::getMainWindow());

    ControllableCamera *cam = new ControllableCamera();
    RenderingContext *myContext=new RenderingContext(cam);
    unsigned int myContextNr = SceneManager::instance()->addContext(myContext);
    unsigned int myScene = SceneManager::instance()->addScene(initScene1());
    ScreenRenderer *myRenderer = new ScreenRenderer(myContextNr, myScene);

    //Vorsicht: Die Szene muss initialisiert sein, bevor das Fenster verändert wird (Fullscreen)
    SceneManager::instance()->setActiveScene(myScene);
    SceneManager::instance()->setActiveContext(myContextNr);
    //SceneManager::instance()->setFullScreen();

    lDock = new Ui_FPSWidget();
    lDock->setupUi(lDockWidget);
    lDockWidget->resize(1280,720);
    SceneManager::getMainWindow()->addDockWidget(Qt::RightDockWidgetArea, lDockWidget);
    lDockWidget->show();
    QObject::connect(Window::getInstance(), SIGNAL(sigFPS(int)), lDock->lcdNumber, SLOT(display(int)));
}

Node *initScene1()
{
	std::vector<Brick *> bricks;
	bricks.reserve(30);

	Node * mainNode = new Node();

    Drawable * centerPoint = new Drawable(new SimpleSphere(1));
    Node * centerPointNode = new Node(centerPoint);
    mainNode->addChild(centerPointNode);


    for (unsigned i = 0; i < 10; i++) {
        for (unsigned j = 0; j < 6; j++) {
            Brick * brick = new Brick(2, 1, 1, QVector3D(i * 3, j * 3, 0));
			bricks.push_back(brick);
            mainNode->addChild(brick->getNode());
		}
	}

    return mainNode;
}
