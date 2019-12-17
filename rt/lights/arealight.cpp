#include <rt/lights/arealight.h>
#include <core/color.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>

namespace rt {

LightHit AreaLight::getLightHit(const Point& p) const {
    /* TODO */
    LightHit lightHit;
    Solid::Sample sample = source->sample();

    lightHit.direction = (sample.point - p).normalize();
    lightHit.normal = -lightHit.direction;
    lightHit.distance = lightHit.direction.length();

    return lightHit;
}

RGBColor AreaLight::getIntensity(const LightHit& irr) const {
    /* TODO */
    RGBColor emission = source->material->getEmission(Point::rep(0.f), Vector::rep(0.f), Vector::rep(0.f));
    return (emission/4.f*pi) * dot(irr.normal, irr.direction) / (irr.distance*irr.distance);
}

AreaLight::AreaLight(Solid* source)
{
    /* TODO */
    this->source = source;
}

}