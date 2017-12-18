#include "GeometryHandler.h"

GeometryHandler & GeometryHandler::instance()
{
    static GeometryHandler instance;
    return instance;
}

void GeometryHandler::addGeometry(const QString name, Geometry * geometry)
{
    storage.insert({ name, geometry });
}

Geometry * GeometryHandler::getGeometry(const QString name)
{
    if (storage.find(name) == storage.end()) {
        std::cout << "GeometryHandler: Geometry " << name.toStdString() << " doesn't exist" << std::endl;
        assert(false);
    }

    return storage[name];
}
