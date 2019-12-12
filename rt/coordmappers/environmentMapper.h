#ifndef CG1_RAYTRACER_ENVIRONMENTMAPPER_H
#define CG1_RAYTRACER_ENVIRONMENTMAPPER_H

#include <rt/coordmappers/coordmapper.h>

namespace rt {

    class Vector;

    class EnvironmentMapper : public CoordMapper {
    public:
        EnvironmentMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis);
        virtual Point getCoords(const Intersection& hit) const;
    };

}

#endif //CG1_RAYTRACER_ENVIRONMENTMAPPER_H
