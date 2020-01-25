#ifndef CG1_RAYTRACER_CYLINDER_H
#define CG1_RAYTRACER_CYLINDER_H

#include <rt/solids/solid.h>
#include <core/matrix.h>

namespace rt{
    class Cylinder : public Solid{
    public:
        Cylinder(Point origin, float radius, float yMin, float yMax, CoordMapper* texMapper, Material* material);

        virtual BBox getBounds() const;
        virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
        virtual Sample sample() const;
        virtual float getArea() const;

        virtual void setMaterial(Material* m);
        virtual void setCoordMapper(CoordMapper* cm);

    private:
        float radius, yMin, yMax;
        Point origin; // optional, can set the bottom origin of the cylinder.
    };
}

#endif //CG1_RAYTRACER_CYLINDER_H