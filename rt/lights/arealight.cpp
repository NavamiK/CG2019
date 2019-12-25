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
    lightHit.normal = sample.normal;
    lightHit.distance = (sample.point - p).length() - offset;

    return lightHit;
}

RGBColor AreaLight::getIntensity(const LightHit& irr) const {
    /* TODO */
    RGBColor emission = source->material->getEmission(Point::rep(0.f), Vector::rep(0.f), Vector::rep(0.f));
    RGBColor power = emission * source->getArea();
    return power  * (dot(irr.normal, -irr.direction) / (irr.distance*irr.distance));
}

AreaLight::AreaLight(Solid* source)
{
    /* TODO */
    this->source = source;
}

}