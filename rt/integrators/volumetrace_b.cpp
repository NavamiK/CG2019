#include <rt/integrators/volumetrace_b.h>
#include <rt/world.h>
#include <rt/lights/light.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/solids/environmentSolid.h>
#include <rt/materials/flatmaterial.h>

namespace rt {

RGBColor VolumeTracingBIntegrator::getVolumeReflectance(Vector outDir, Vector inDir) const{
    //Henyey-Greenstein phase function
    float numer = 1 - g_sq;
    float denom = 4 * pi * pow((1 + g_sq + 2 * g * dot(outDir, inDir)), 1.5f);
    return RGBColor::rep(numer/ denom);
    //Isotropic phase function to get reflectance at volume point
    //return RGBColor::rep(isoPhaseFunctionVal);
}

RGBColor VolumeTracingBIntegrator::getRadiance(const Ray& ray) const {
    /* TODO */
    RGBColor totalRadiance = RGBColor::rep(0.0f);
    RGBColor emission, reflectance, intensity;
    Intersection intersection = world->scene->intersect(ray);
    Point texPoint;
    
    if(intersection){
            
        //March along primary ray
        float volumePointAttenuation = fogStepAttenuation;//Computed in header file
        float volumePointDistance = stepSize; 

        for(; volumePointDistance <= intersection.distance; volumePointDistance += stepSize){            
            Point volumePoint = ray.o + volumePointDistance * ray.d;
            RGBColor volumePointRadiance = RGBColor::rep(0.0f);
            
            for(int i = 0; i < world->light.size(); i++){
                LightHit lightHit = world->light[i]->getLightHit(volumePoint);
                Ray shadowRay(volumePoint, lightHit.direction);
                Intersection shaIntersec = world->scene->intersect(shadowRay, lightHit.distance);
                //If no intersection of shadow ray, or the intersection distance greater than distance to light source, update radiance
                if(!shaIntersec){
                    intensity = world->light[i]->getIntensity(lightHit);
                    //Estimate attenuation along the shadow ray - homogenous, e^(-(a-b)*mu) - lecture notes, page #27
                    float fogShadowAttenuation = exp(-1 * lightHit.distance * fogDensity);
                    intensity = intensity * fogShadowAttenuation;
                    volumePointRadiance = volumePointRadiance + intensity * getVolumeReflectance(-ray.d,-shadowRay.d);
                }
            //Incremental update of attenuation when marching along primary ray 
            volumePointAttenuation = fogStepAttenuation * volumePointAttenuation;
            //Estimate attenuation along the primary ray upto marching distance
            totalRadiance = totalRadiance + volumePointRadiance * volumePointAttenuation;
            }
        }

        //Now compute color due to surface interaction ( as usual/before)
        RGBColor surfaceRadiance = RGBColor::rep(0.0f);
        texPoint = intersection.solid->texMapper->getCoords(intersection);
        emission = intersection.solid->material->getEmission(texPoint, intersection.normal(), -ray.d);
        surfaceRadiance = surfaceRadiance + emission; 

        // Get the radiance at hit point as usual
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
                    surfaceRadiance = surfaceRadiance + intensity * reflectance;
                }
            }
        }
        //Estimate attenuation along the primary ray - homogenous, e^(-(a-b)*mu) - lecture notes, page #27
        float surfaceRadianceAttenuation = exp(-1 * intersection.distance * fogDensity);
        // Interpolate
        totalRadiance = totalRadiance + surfaceRadiance * surfaceRadianceAttenuation;
    }
    return totalRadiance;    
}

}