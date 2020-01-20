#ifndef CG1_RAYTRACER_CYLINDER_H
#define CG1_RAYTRACER_CYLINDER_H

#include <rt/solids/solid.h>

namespace rt{
    class Cylinder : public Solid{
    public:
        Cylinder(float radius, float yMin, float yMax, float phiMax, CoordMapper* texMapper, Material* material);

        virtual BBox getBounds() const;
        virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
        virtual Sample sample() const;
        virtual float getArea() const;

        float radius, yMin, yMax, phiMax;
        CoordMapper *texMapper;
        Material *material;
    };
}

#endif //CG1_RAYTRACER_CYLINDER_H
