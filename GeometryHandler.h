#ifndef OBJECTHANDLER_H
#define OBJECTHANDLER_H

#include "geometry.h"

#include <map>
#include <qstring.h>
#include <assert.h>

class GeometryHandler
{
private:
    std::map<QString, Geometry*> storage;
public:
    static GeometryHandler &instance();
    void addGeometry(const QString name, Geometry * geometry);
    Geometry * getGeometry(const QString name);
};

#endif // !OBJECTHANDLER_H
