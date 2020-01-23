#include <rt/integrators/raytracefire.h>
#include <rt/world.h>
#include <rt/lights/light.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/materials/flatmaterial.h>

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
            float volumePointAttenuation = fireStepAttenuation;//Computed in header file
            
            for(float volumePointDistance = entryDistance; volumePointDistance < exitDistance; volumePointDistance += stepSize){            
                volumePointAttenuation = fireStepAttenuation * volumePointAttenuation;
                totalRadiance = totalRadiance + volumePointRadiance * volumePointAttenuation; 
            }
        }
     }
    return totalRadiance;    
}
}
