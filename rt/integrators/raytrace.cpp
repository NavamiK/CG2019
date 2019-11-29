#include <rt/integrators/raytrace.h>
#include <rt/world.h>
#include <rt/lights/light.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>

namespace rt {

RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const {
    /* TODO */
    RGBColor totalRadiance, emission, reflactance, intensity;

    for(int i = 0; i < world->light.size(); i++){
        Intersection intersec = world->scene->intersect(ray);
        if(intersec){
            LightHit lightHit = world->light[i]->getLightHit(intersec.hitPoint());
            Ray shadowRay(intersec.hitPoint(), -lightHit.direction);
            // confirm which side rays leave.
            if(dot(ray.d, shadowRay.d) > 0){
                Intersection shaIntersec = world->scene->intersect(shadowRay);
                if(shaIntersec){
                    intensity = world->light[i]->getIntensity(lightHit);
                    emission = intersec.solid->material->getEmission(intersec.hitPoint(), intersec.normal(), -lightHit.direction);
                    reflactance = intersec.solid->material->getReflectance(intersec.hitPoint(), intersec.normal(), -lightHit.direction, ray.d);
                    totalRadiance = totalRadiance + (emission + intensity * reflactance);//TODO: maybe wrong.
                }
            }
        }
    }

    return totalRadiance;
}

}