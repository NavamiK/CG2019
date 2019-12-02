#include <rt/lights/projectivelight.h>
#include <rt/ray.h>
#include <cmath>
#include <iostream>
using namespace rt;
//rt::RGBColor a1computeColor(rt::uint x, rt::uint y, rt::uint width, rt::uint height);
RGBColor a1computeColor(uint x, uint y, uint width, uint height);

namespace rt {

ProjectiveLight::ProjectiveLight(const Point& position, const RGBColor& intensity)
{
    /* TODO */
    this->position = position;
    this->intensity = intensity;
}

LightHit ProjectiveLight::getLightHit(const Point& p) const {
    /* TODO */
    LightHit lightHit;
    Vector hitPointToLight = position - p;
    lightHit.distance = hitPointToLight.length();
    lightHit.direction = hitPointToLight.normalize();
    lightHit.normal = -hitPointToLight; 
    return lightHit;
}

RGBColor ProjectiveLight::getIntensity(const LightHit& irr) const {
    /* TODO */
    Vector dir=irr.direction;
    int res = 800;
    Vector r1 =Vector(1,0,0);
    Vector r2 =Vector(0,1,0);
    RGBColor color = a1computeColor(abs(dot(dir, r1 * res)), abs(dot(dir, r2 * res)), res, res);
    RGBColor julia_color = intensity - color;
    return julia_color * (1.f / (irr.distance*irr.distance)); 
}

}