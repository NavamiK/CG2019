#include <rt/solids/environmentSolid.h>

namespace rt{

EnvironmentSolid::EnvironmentSolid(rt::CoordMapper *texMapper, rt::Material *material) {
    this->texMapper = texMapper;
    this->material = material;
}

Intersection EnvironmentSolid::intersect(const rt::Ray &ray, float previousBestDistance) const {
    // always intersect at infinity.
    return (Intersection(FLT_MAX, ray, this, Vector(0.f, 0.f, 0.f), Point(0.f, 0.f, 0.f)));
}

BBox EnvironmentSolid::getBounds() const {
    return BBox(Point::rep(NEG_INF), Point::rep(FLT_MAX));
}

float EnvironmentSolid::getArea() const {
    return FLT_MAX;
}

Solid::Sample EnvironmentSolid::sample() const {
    NOT_IMPLEMENTED;
}

};