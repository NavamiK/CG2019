#include <rt/intersection.h>

namespace rt {

Intersection::Intersection(float distance, const Ray& ray, const Solid* solid, const Vector& normal, const Point& local)
{
    /* TODO */
    this->distance = distance;
    this->ray = ray;
    this->solid = solid;
    this->normalVector = normal;
    this->localPoint = local;
}

Intersection::operator bool() {
    /* TODO */ 
    if(distance == FLT_MAX)
        return false;
}

Intersection Intersection::failure() {
    /* TODO */ 
    Intersection intersection;
    return intersection;
}

Point Intersection::hitPoint() const {
    /* TODO */ 
    Point hitPoint = ray.o + distance * ray.d;
    return hitPoint;
}

Vector Intersection::normal() const {
    /* TODO */ 
    return normalVector;

}

Point Intersection::local() const {
    /* TODO */ 
    return localPoint;
}

}
