#include <rt/integrators/raytrace.h>
#include <rt/world.h>
#include <rt/lights/light.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>

namespace rt {

RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const {
    /* TODO */
    RGBColor totalRadiance = RGBColor::rep(0.0f);   
    RGBColor emission, reflectance, intensity;
    Intersection intersection = world->scene->intersect(ray);
    if(intersection){
        for(int i = 0; i < world->light.size(); i++){
            LightHit lightHit = world->light[i]->getLightHit(intersection.hitPoint());
            Ray shadowRay(intersection.hitPoint(), lightHit.direction);
            if(dot(intersection.normal(), shadowRay.d) > 0){
                Intersection shaIntersec = world->scene->intersect(shadowRay);
                //If no intersection of shadow ray, or the intersection distnace greater than distance to light source, update radiance
                if((!shaIntersec) || (shaIntersec.distance >= lightHit.distance)){
                    intensity = world->light[i]->getIntensity(lightHit);
                    emission = intersection.solid->material->getEmission(intersection.local(), intersection.normal(), -ray.d);
                    reflectance = intersection.solid->material->getReflectance(intersection.local(), intersection.normal(),  -ray.d, -lightHit.direction);
                    //totalRadiance = totalRadiance + emission + intensity * reflectance;
                    totalRadiance = totalRadiance + emission + intensity;
                }
            }
        }
        return totalRadiance;
    }
    else
        return RGBColor::rep(0.0f);   
}

}