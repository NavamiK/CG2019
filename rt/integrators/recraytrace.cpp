#include <rt/integrators/recraytrace.h>
#include <rt/intersection.h>
#include <rt/lights/light.h>
#include <rt/world.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>


namespace rt {

RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray) const {
    /* TODO */
    int dept = 6; // TODO: increase later
    RGBColor totalRadiance = RGBColor::rep(0.0f);
    RGBColor emission, reflectance, intensity, irradiance;
    Material::Sampling sampling;

    Intersection intersection = world->scene->intersect(ray);
    if(intersection){
        emission = intersection.solid->material->getEmission(intersection.local(), intersection.normal(), -ray.d);
        sampling = intersection.solid->material->useSampling();
        totalRadiance = totalRadiance + emission;
        for(int i = 0; i < world->light.size(); i++){
            LightHit lightHit = world->light[i]->getLightHit(intersection.hitPoint());
            //Shift the ray origin towards it's direction by an offset, to avoid self intersection
            Ray shadowRay(intersection.hitPoint() + intersection.normal() * OFFSET, lightHit.direction);
            if(dot(intersection.normal(), shadowRay.d) > 0.0f){
                Intersection shaIntersec = world->scene->intersect(shadowRay, lightHit.distance);
                //If no intersection of shadow ray, or the intersection distnace greater than distance to light source, update radiance
                if(!shaIntersec){
                    intensity = world->light[i]->getIntensity(lightHit);
                    reflectance = intersection.solid->material->getReflectance(intersection.local(), intersection.normal(),  -ray.d, -shadowRay.d);

                    if(sampling == Material::SAMPLING_NOT_NEEDED)
                        totalRadiance = totalRadiance + intensity * reflectance;
                    else{
                        // assume 'sampling_all' for now.
                        irradiance = getIrradiance(intersection.ray, dept);
                        totalRadiance = totalRadiance + irradiance;
                    }
                }
            }
        }
    }

    return totalRadiance;
}

RGBColor RecursiveRayTracingIntegrator::getIrradiance(const rt::Ray &ray, int dept) const {
    /* TODO */
    if(dept == 0){
        return RGBColor::rep(0.f);
    }
    else{
        RGBColor totalRadiance = RGBColor::rep(0.0f);
        RGBColor emission, reflectance, intensity;
        Intersection intersection = world->scene->intersect(ray);
        if(intersection){
            emission = intersection.solid->material->getEmission(intersection.local(), intersection.normal(), -ray.d);

            totalRadiance = totalRadiance + emission;
            for(int i = 0; i < world->light.size(); i++){
                LightHit lightHit = world->light[i]->getLightHit(intersection.hitPoint());
                //Shift the ray origin towards it's direction by an offset, to avoid self intersection
                Ray shadowRay(intersection.hitPoint() + intersection.normal() * OFFSET, lightHit.direction);
                if(dot(intersection.normal(), shadowRay.d) > 0.0f){
                    Intersection shaIntersec = world->scene->intersect(shadowRay, lightHit.distance);
                    //If no intersection of shadow ray, or the intersection distnace greater than distance to light source, update radiance
                    if(!shaIntersec){
                        intensity = world->light[i]->getIntensity(lightHit);
                        reflectance = intersection.solid->material->getReflectance(intersection.local(), intersection.normal(),  -ray.d, -shadowRay.d);
                        totalRadiance = totalRadiance + intensity * reflectance;
                        totalRadiance = totalRadiance + getIrradiance(intersection.ray, dept-1);
                    }
                }
            }
        }

        return totalRadiance;

    }
}

}