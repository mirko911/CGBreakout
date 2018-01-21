#include "HUDElement.h"
#include "Ball.h"

HUDElement::HUDElement(const QVector3D position, const int length) : position(position), length(length)
{
    GeometryHandler &handler = GeometryHandler::instance();
    for (int i = 0; i < length; i++) {
        GameObject * go = new GameObject(position + QVector3D(i * 3, 0, 0), handler.getGeometry("letter_0"));
        go->setPosition(position + QVector3D(i * 2, 0, 0));
        Color * color = go->getProperty<Color>();
        color->setValue(1, 1, 1);
        gameObjects.push_back(go);
    }
    int x = 0;
    x++;
}

Node * HUDElement::setup()
{
    Node * hudNode = new Node();
    for (GameObject * obj : gameObjects) {
        hudNode->addChild(obj->getNode());
    }
    return hudNode;
}

void HUDElement::setValue(const int value_)
{
    GeometryHandler &handler = GeometryHandler::instance();

    value = value_;
    text = std::to_string(value);
    //Fill with leading zeros
    text.insert(text.begin(), length - text.length(), '0');
    std::cout << text << std::endl;

    int i = 0;
    for(char &c : text){

       std::string letter = "letter_";
       letter += c;

       Geometry * geo = handler.getGeometry(QString::fromStdString(letter));
       gameObjects.at(i)->setGeometry(geo);

       i++;
    }
}
