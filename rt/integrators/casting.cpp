#include <rt/integrators/casting.h>
#include <rt/world.h>

namespace rt {

RGBColor RayCastingIntegrator::getRadiance(const Ray& ray) const {
    /* TODO */ 
    Intersection intersection = world->scene->intersect(ray);
    if(intersection){
        float value = dot(ray.d, intersection.normal());
        RGBColor grayValue = RGBColor::rep(value);
        return grayValue;
    }
    /*
    else{
        RGBColor noValue(0.0f, 0.0f, 1.0f);
        return noValue;
    }*/
}

}
