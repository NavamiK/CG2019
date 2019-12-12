#include <rt/coordmappers/plane.h>

namespace rt {

PlaneCoordMapper::PlaneCoordMapper(const Vector& e1, const Vector& e2) {
    /* TODO */
    this->e1 = e1;
    this->e2 = e2;
    this->origin = Point::rep(0.0f);
    this->normal = cross(e1, e2).normalize();
}

Point PlaneCoordMapper::getCoords(const Intersection& hit) const {
    /* TODO */
    Vector hitPointVector = hit.local() - origin;
    float hitPlaneDist = dot(hitPointVector, normal);
    Vector texCoord = hitPointVector - hitPlaneDist * normal;
    return Point(texCoord.x, texCoord.y, texCoord.z);
}

}