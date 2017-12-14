#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <qwidget.h>
#include "drawable.h"
#include "transformation.h"


class GameObject : public Drawable
{
protected:
    QVector3D position;
    Transformation * transformation;
    Node * node;
public:

    GameObject(Geometry * geometry);
    GameObject(const QVector3D position, Geometry * geometry);
    void setPosition(const QVector3D position);
    void setPosition(const float x, const float y, const float z);

    virtual void beforeTraverseChilds(SGObjectVisitor& visitor) override;
    virtual void afterTraverseChilds() override;

    Node* getNode();
    QVector3D getPosition() const;
    Transformation * getTransformation() const;
};

#endif // !GAMEOBJECT_H
