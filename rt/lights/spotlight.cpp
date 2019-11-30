#include <rt/lights/spotlight.h>

namespace rt {

SpotLight::SpotLight(const Point& position, const Vector& direction, float angle, float power, const RGBColor& intensity)
{
    this->position = position;
    this->direction = direction;
    this->angle = angle;
    this->exp = power;
    this->intensity = intensity;
}

RGBColor SpotLight::getIntensity(const LightHit& irr) const {
    /* TODO */
    return (intensity * 1.f /(irr.distance * irr.distance));
}

}
