#include <rt/integrators/raytracefire.h>
#include <rt/world.h>
#include <rt/lights/light.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/materials/flatmaterial.h>
#include <math.h>

namespace rt {
RayTraceFireIntegrator::RayTraceFireIntegrator(World* world, VGroup* vGroup) : Integrator(world) {
    this->vGroup = vGroup;
}

RGBColor RayTraceFireIntegrator::getRadiance(const Ray& ray) const {
    /* TODO */
    RGBColor totalRadiance = RGBColor::rep(0.0f);
    
    for (auto iter = vGroup->vInstances.begin(); iter != vGroup->vInstances.end(); ++iter){
        auto[isIntersect, entryDistance, exitDistance] = (*iter)->intersect(ray);
        if(isIntersect){
            //std::cout<<entryDistance << " "<<exitDistance<<std::endl;
            //With attenuation            
            //float volumePointAttenuation = fireStepAttenuation;//Computed in header file
            for(float volumePointDistance = entryDistance; volumePointDistance < exitDistance; volumePointDistance += stepSize){            
                //volumePointAttenuation = fireStepAttenuation * volumePointAttenuation;
                totalRadiance = totalRadiance + volumePointRadiance ;// * volumePointAttenuation; 
            }
           //Without attenuation
            /*
            float numberOfSteps = (exitDistance - entryDistance)/stepSize;
            if(!isnan(numberOfSteps))
                totalRadiance = totalRadiance + volumePointRadiance * numberOfSteps; 
            */
        }
     }

    
    
    
    
    
    
    //RGBColor totalRadiance = RGBColor::rep(0.0f);
    
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
                    reflectance = intersection.solid->material->getReflectance(texPoint, intersection.normal(),  -ray.d, -shadowRay.d);
                    totalRadiance = totalRadiance + intensity * reflectance;
                }
            }
        }   
    }

   // if (totalRadiance.r == 0.f) 
     //   return RGBColor(0, 0.05f, 0.05f);
    
    return totalRadiance;    
}
}
