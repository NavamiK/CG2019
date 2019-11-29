#include <rt/lights/pointlight.h>

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
    lightHit.normal = -lightHit.direction;

    return lightHit;
}

RGBColor PointLight::getIntensity(const LightHit& irr) const {
    /* TODO */
    return intensity * (1.f/irr.distance*irr.distance);
}

}
