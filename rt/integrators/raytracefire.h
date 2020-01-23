#ifndef CG1RAYTRACER_INTEGRATORS_RAYTRACING_FIRE_HEADER
#define CG1RAYTRACER_INTEGRATORS_RAYTRACING_FIRE_HEADER

#include <rt/integrators/integrator.h>
#include <rt/volumes/vsphere.h>
#include <rt/volumes/vcone.h>
#include <core/scalar.h>
#include <rt/primmod/vinstance.h>
#include <rt/groups/vgroup.h>

namespace rt {
class World;
class Ray;
class RGBColor;

class RayTraceFireIntegrator : public Integrator {
public:
    //RayTraceFireIntegrator(World* world, VSphere vSphere);
    //RayTraceFireIntegrator(World* world, VCone vCone);
    //RayTraceFireIntegrator(World* world, VInstance* vCone);
    RayTraceFireIntegrator(World* world, VGroup* vGroup);
    //RayTraceFireIntegrator(World* world, VSphere vSphere) : Integrator(world) {}
    virtual RGBColor getRadiance(const Ray& ray) const;
private:
    float offset =  0.0001f;
    float stepSize = 0.005f;
    float fireDensity = 0.7;
    RGBColor fogColor = RGBColor::rep(1.0f);
    VSphere vSphere;
    VCone vCone;
    VInstance* vInstance;
    VGroup* vGroup;
    RGBColor volumePointRadiance = RGBColor(0.886f, 0.345f, 0.133f); //Color of flame 
    float fireStepAttenuation = exp(-1 * stepSize * fireDensity);
};

}

#endif