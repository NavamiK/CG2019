#include <rt/lights/directional.h>
#include <core/scalar.h>
#include <core/vector.h>
#include <core/point.h>

namespace rt {

DirectionalLight::DirectionalLight(const Vector& direction, const RGBColor& color)
{
    /* TODO */
    this->direction = direction;
    this->color = color;
}

LightHit DirectionalLight::getLightHit(const Point& p) const {
    /* TODO */
    LightHit lightHit;
    lightHit.direction = direction;
    lightHit.distance = INFINITY;
    lightHit.normal = -direction;
    return lightHit;
}

RGBColor DirectionalLight::getIntensity(const LightHit& irr) const {
    /* TODO */
    return color;
}

}
