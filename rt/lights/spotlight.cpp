#include <rt/lights/spotlight.h>

namespace rt {

SpotLight::SpotLight(const Point& position, const Vector& direction, float angle, float power, const RGBColor& intensity)
{
    this->position = position;
    this->direction = direction.normalize();
    this->angle = angle;
    this->exp = power;
    this->intensity = intensity;
}


LightHit SpotLight::getLightHit(const Point& p) const {
   
    LightHit lightHit;
    Vector hitPointToLight = position - p;
    lightHit.distance = hitPointToLight.length();
    lightHit.direction = hitPointToLight.normalize();
    lightHit.normal = Vector::rep(0.0f); //Normal for point light is irrelevant
    return lightHit;
}

RGBColor SpotLight::getIntensity(const LightHit& irr) const {
    /* TODO */
    float clobe = dot(-irr.direction, this->direction);
    if(angle > acos(clobe))
        return intensity * (pow(clobe, exp) / (irr.distance*irr.distance));   
    else 
        return RGBColor::rep(0.0f);
}

}
