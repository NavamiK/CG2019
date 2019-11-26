#include <rt/lights/pointlight.h>

#include <core/vector.h>

namespace rt {

PointLight::PointLight(const Point& position, const RGBColor& intensity)
{
    /* TODO */
    this->position = position;
    this->intensity = intensity;
}

LightHit PointLight::getLightHit(const Point& p) const {
    /* TODO */
    LightHit lightHit;
    lightHit.direction = p - position;
    lightHit.distance = (p - position).length();
    Vector v1, v2;

    v1 = p - Point(0, 0, p.z);
    v2 = Vector(p.x * drand48(), p.y * drand48(), p.z);
    lightHit.normal = cross(v1, v2);

    assert(dot(v1, lightHit.normal) == 0); // TODO: make sure.

    return lightHit;
}

RGBColor PointLight::getIntensity(const LightHit& irr) const {
    /* TODO */
    return intensity;
}

}
