#include <rt/integrators/volumetrace_c.h>
#include <rt/world.h>
#include <rt/lights/light.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/solids/environmentSolid.h>
#include <rt/materials/flatmaterial.h>

namespace rt {

VolumeTracingCIntegrator::VolumeTracingCIntegrator(World* world) : Integrator(world) {
    fogDensityMax = 0.9;
    fogDensityMin = 0.1;
    addOctave(0.5f, 5.0f);
    addOctave(0.25f, 10.0f);
    addOctave(0.125f, 20.0f);
    addOctave(0.125f, 40.0f);
}

RGBColor VolumeTracingCIntegrator::getVolumeReflectance(Vector outDir, Vector inDir) const{
    //Henyey-Greenstein phase function
    float numer = 1 - g_sq;
    float denom = 4 * pi * pow((1 + g_sq + 2 * g * dot(outDir, inDir)), 1.5f);
    return RGBColor::rep(numer/ denom);
    //Isotropic phase function to get reflectance at volume point
    //return RGBColor::rep(isoPhaseFunctionVal);
}

static inline float noise(int x, int y, int z) {
    int n = x + y * 57 + z * 997;
    n = (n << 13) ^ n;
    return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

float VolumeTracingCIntegrator::getDensity(Point coord) const{
    /* TODO */ 
    Point p;
    float total = 0.0f;
    int lu, lv, lw;
    float fu, fv, fw;
    float n1, n2, n3, n4, n5, n6, n7, n8;
    for (int i = 0; i < amplitudes.size(); i++){
        p = frequencies[i] * coord;
        lu = floor(p.x); lv = floor(p.y); lw = floor(p.z);
        fu = p.x - lu; fv = p.y - lv; fw = p.z - lw;
        n1 = fabs(noise(lu, lv, lw));
        n2 = fabs(noise(lu + 1, lv, lw));
        n3 = fabs(noise(lu, lv + 1, lw));
        n4 = fabs(noise(lu + 1, lv + 1, lw));
        n5 = fabs(noise(lu, lv, lw + 1));
        n6 = fabs(noise(lu + 1, lv, lw + 1));
        n7 = fabs(noise(lu, lv + 1, lw + 1));
        n8 = fabs(noise(lu + 1, lv + 1, lw + 1));
        total = total + (lerp3d(n1, n2, n3, n4, n5, n6, n7, n8, fu, fv, fw) * amplitudes[i]); 
    }    
    return lerp(fogDensityMin, fogDensityMax, total);
}

void VolumeTracingCIntegrator::addOctave(float amplitude, float frequency) {
    /* TODO */ 
    amplitudes.push_back(amplitude);
    frequencies.push_back(frequency);
}

RGBColor VolumeTracingCIntegrator::getRadiance(const Ray& ray) const {
    /* TODO */
    RGBColor totalRadiance = RGBColor::rep(0.0f);
    RGBColor emission, reflectance, intensity;
    Intersection intersection = world->scene->intersect(ray);
    Point texPoint;
    
    if(intersection){
            
        //March along primary ray
        float volumePointDistance = stepSize; 
        float volumePointAttenuation = 1;

        for(; volumePointDistance <= intersection.distance; volumePointDistance += stepSize){            
            Point volumePoint = ray.o + volumePointDistance * ray.d;
            //Evalute density and hence attenuation using perlin noise
            float fogStepAttenuation = exp(-1 * stepSize * getDensity(volumePoint));
            RGBColor volumePointRadiance = RGBColor::rep(0.0f);
            
            for(int i = 0; i < world->light.size(); i++){
                LightHit lightHit = world->light[i]->getLightHit(volumePoint);
                Ray shadowRay(volumePoint, lightHit.direction);
                Intersection shaIntersec = world->scene->intersect(shadowRay, lightHit.distance);
                //If no intersection of shadow ray, or the intersection distance greater than distance to light source, update radiance
                if(!shaIntersec){
                    intensity = world->light[i]->getIntensity(lightHit);
                    //Estimate attenuation along the shadow ray - homogenous, e^(-(a-b)*mu) - lecture notes, page #27
                    float fogShadowAttenuation = exp(-1 * lightHit.distance * getDensity(volumePoint));
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
                    float fogShadowAttenuation = exp(-1 * lightHit.distance * getDensity(intersection.hitPoint()));
                    intensity = intensity * fogShadowAttenuation;
                    //End attenuation 
                    reflectance = intersection.solid->material->getReflectance(texPoint, intersection.normal(),  -ray.d, -shadowRay.d);
                    surfaceRadiance = surfaceRadiance + intensity * reflectance;
                }
            }
        }
        //Estimate attenuation along the primary ray - homogenous, e^(-(a-b)*mu) - lecture notes, page #27
        float surfaceRadianceAttenuation = exp(-1 * intersection.distance * getDensity(intersection.hitPoint()));
        // Interpolate
        totalRadiance = totalRadiance + surfaceRadiance * surfaceRadianceAttenuation;
    }
    return totalRadiance;    
}

}