#include <rt/integrators/raytrace.h>
#include <rt/world.h>
#include <rt/lights/light.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>

namespace rt {

RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const {
    /* TODO */
//<<<<<<< HEAD
//    RGBColor totalRadiance, emission, reflactance, intensity;
//
//    for(int i = 0; i < world->light.size(); i++){
//        Intersection intersec = world->scene->intersect(ray);
//        if(intersec){
//            LightHit lightHit = world->light[i]->getLightHit(intersec.hitPoint());
//            Ray shadowRay(intersec.hitPoint(), -lightHit.direction);
//            // confirm which side rays leave.
//            if(dot(ray.d, shadowRay.d) > 0){
//                Intersection shaIntersec = world->scene->intersect(shadowRay);
//                if(shaIntersec){
//                    intensity = world->light[i]->getIntensity(lightHit);
//                    emission = intersec.solid->material->getEmission(intersec.hitPoint(), intersec.normal(), -lightHit.direction);
//                    reflactance = intersec.solid->material->getReflectance(intersec.hitPoint(), intersec.normal(), -lightHit.direction, ray.d);
//                    totalRadiance = totalRadiance + (emission + intensity * reflactance);//TODO: maybe wrong.
//                }
//            }
//        }
//    }
//
//    return totalRadiance;
//=======
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
                    Vector t = cross(lightHit.direction,intersection.normal());
                    emission = intersection.solid->material->getEmission(intersection.local(), intersection.normal(), -ray.d);
                    reflectance = intersection.solid->material->getReflectance(intersection.local(), intersection.normal(),  -ray.d, t);
                    //totalRadiance = totalRadiance + emission + intensity * reflectance;
                    totalRadiance = totalRadiance + emission + intensity;
                }
            }
        }
        return totalRadiance;
    }
    else
        return RGBColor::rep(0.0f);
//>>>>>>> navami
}

}