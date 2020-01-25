#include <rt/solids/cylinder.h>
#include <cmath>

namespace rt{
    Cylinder::Cylinder(Point origin, float radius, float yMin, float yMax, rt::CoordMapper *texMapper, rt::Material *material) {
        this->origin = origin;
        this->radius = radius;
        this->yMin = yMin;
        this->yMax = yMax;
        if(texMapper != nullptr) this->texMapper = texMapper;
        this->material = material;
    }

    Intersection Cylinder::intersect(const rt::Ray &ray, float previousBestDistance) const {
        // logic from pbrt book.
        float a = (ray.d.x * ray.d.x) + (ray.d.z * ray.d.z);
        float b = 2.f * (ray.d.x * ray.o.x + ray.d.z * ray.o.z - origin.x*ray.d.x - origin.z*ray.d.z);
        float c = (ray.o.x * ray.o.x) + (ray.o.z * ray.o.z) - radius * radius +
                (-2.f * origin.x*ray.o.x) + (-2.f * origin.z * ray.d.z) + (origin.x*origin.x + origin.z*origin.z);

        //solve qaudratic equation for t.
        float discriminant = b * b - 4.f * a * c;
        if(discriminant < 0){
            return Intersection::failure();
        }

        float t0 = (-b - sqrt(discriminant)) / (2.f * a);
        float t1 = (-b + sqrt(discriminant)) / (2.f * a);
        float distance;

        if(t0 > previousBestDistance  || t1 < 0.f){
            return Intersection::failure();
        }

        distance = t0;
        if(distance <= 0.f){
            distance = t1;
            if(distance > previousBestDistance)
                return Intersection::failure();
        }

        Point hitPoint = ray.getPoint(distance);

        // Test cylinder intersection against clipping parameters
        if (hitPoint.y < yMin || hitPoint.y > yMax) {
            if (distance == t1) return Intersection::failure();
            distance = t1;
            if (t1 > previousBestDistance) return Intersection::failure();
            // Compute cylinder hit point and $\phi$
            hitPoint = ray.getPoint(distance);

            if (hitPoint.y < yMin || hitPoint.y > yMax) return Intersection::failure();
        }

        // normal idea taken here:
        //https://stackoverflow.com/questions/36266357/how-can-i-compute-normal-on-the-surface-of-a-cylinder
        Vector normal = (hitPoint - Point(0.f, hitPoint.y, 0.f)).normalize();

        //TODO: I should have to calculate the parametric version ofthe points. do later.
        Intersection intersection(distance, ray, this, normal, hitPoint);

        return intersection;

    }

    BBox Cylinder::getBounds() const {
        Point pMin(-radius, -radius, yMin);
        Point pMax(radius, radius, yMax);
        return (BBox(pMin, pMax));
    }

    float Cylinder::getArea() const {
        NOT_IMPLEMENTED;
        //similar to width*height.
       // return (yMax - yMin) * radius * phiMax;
    }

    Solid::Sample Cylinder::sample() const {
        NOT_IMPLEMENTED;
    }

    void Cylinder::setCoordMapper(rt::CoordMapper *cm) {
        texMapper = cm;
    }

    void Cylinder::setMaterial(rt::Material *m) {
        material = m;
    }
};