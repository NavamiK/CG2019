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
    this->intOccurs = true;
}

Intersection::Intersection() {
    this->intOccurs = false;
}

Intersection::operator bool() {
    /* TODO */ 
    return this->intOccurs;
}

Intersection Intersection::failure() {
    /* TODO */ 
    return Intersection();
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

Vector Intersection::setNormal(const Vector n) {
    normalVector = n;
}

Point Intersection::local() const {
    /* TODO */ 
    return localPoint;
}

}
