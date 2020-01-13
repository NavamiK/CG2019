#include <rt/integrators/volumetrace_a.h>
#include <rt/world.h>
#include <rt/lights/light.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/solids/environmentSolid.h>
#include <rt/materials/flatmaterial.h>

namespace rt {
/*
VolumeTracingIntegrator::VolumeTracingIntegrator(World* world, VolumeTracingIntegrator::FogType ft) : Integrator(world) {
    this->fogType = ft;
}
*/

RGBColor VolumeTracingAIntegrator::getRadiance(const Ray& ray) const {
    /* TODO */
    RGBColor totalRadiance = RGBColor::rep(0.0f);
    RGBColor emission, reflectance, intensity;
    Intersection intersection = world->scene->intersect(ray);
    Point texPoint;
    
    if(intersection){
        texPoint = intersection.solid->texMapper->getCoords(intersection);
        emission = intersection.solid->material->getEmission(texPoint, intersection.normal(), -ray.d);
        totalRadiance = totalRadiance + emission; 

        for(int i = 0; i < world->light.size(); i++){
            LightHit lightHit = world->light[i]->getLightHit(intersection.hitPoint());
            //Shift the ray origin towards it's direction by an offset, to avoid self intersection
            Ray shadowRay(intersection.hitPoint() + intersection.normal() * offset, lightHit.direction);
            
            if(dot(intersection.normal(), shadowRay.d) > 0.0f){
                Intersection shaIntersec = world->scene->intersect(shadowRay, lightHit.distance);
                //If no intersection of shadow ray, or the intersection distnace greater than distance to light source, update radiance
                if(!shaIntersec){
                    intensity = world->light[i]->getIntensity(lightHit);
                    //Estimate attenuation along the shadow ray - homogenous, e^(-(a-b)*mu) - lecture notes, page #27
                    float fogShadowAttenuation = exp(-1 * lightHit.distance * fogDensity);
                    intensity = intensity * fogShadowAttenuation;
                    //End attenuation 
                    reflectance = intersection.solid->material->getReflectance(texPoint, intersection.normal(),  -ray.d, -shadowRay.d);
                    totalRadiance = totalRadiance + intensity * reflectance;
                }
            } 
        }
        //Estimate attenuation along the primary ray - homogenous, e^(-(a-b)*mu) - lecture notes, page #27
        float fogPrimaryAttenuation = exp(-1 * intersection.distance * fogDensity);
        // Interpolate, fogColor represents color of fog particles due to ambient light
        totalRadiance = totalRadiance * fogPrimaryAttenuation + fogColor * fogPrimaryAttenuation;
    }
    return totalRadiance;    
}
}
