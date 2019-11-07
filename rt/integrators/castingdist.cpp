#include <rt/integrators/castingdist.h>
#include <rt/world.h>

namespace rt {

RayCastingDistIntegrator::RayCastingDistIntegrator(World* world, const RGBColor& nearColor, float nearDist, const RGBColor& farColor, float farDist)
    : Integrator(world)
{
    /* TODO */
    this->nearColor = nearColor;
    this->nearDist = nearDist;
    this->farColor = farColor;
    this->farDist = farDist;
}

RGBColor RayCastingDistIntegrator::getRadiance(const Ray& ray) const {
    /* TODO */ 
    Intersection intersection = world->scene->intersect(ray);
    RGBColor scalingFactor = (farColor - nearColor) / (farDist - nearDist);

    if(intersection){
        //Not sure why -ve direction of ray, maybe to get +ve color values
        RGBColor interpolColor;
        if(intersection.distance < nearDist)
            interpolColor = nearColor;
        else if(intersection.distance > farDist)
            interpolColor = farColor;
        else 
            interpolColor = scalingFactor * (intersection.distance - nearDist) + nearColor;
        
        float value = dot(-ray.d.normalize(), intersection.normal().normalize()); 
        RGBColor grayValue = RGBColor::rep(value);
        
        return interpolColor * grayValue;
    }
}

}
