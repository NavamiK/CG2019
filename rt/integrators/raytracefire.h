#ifndef CG1RAYTRACER_INTEGRATORS_RAYTRACING_FIRE_HEADER
#define CG1RAYTRACER_INTEGRATORS_RAYTRACING_FIRE_HEADER

#include <rt/integrators/integrator.h>
#include <rt/volumes/vsphere.h>
namespace rt {
class World;
class Ray;
class RGBColor;

class RayTraceFireIntegrator : public Integrator {
public:
    RayTraceFireIntegrator(World* world, VSphere vSphere);
    //RayTraceFireIntegrator(World* world, VSphere vSphere) : Integrator(world) {}
    virtual RGBColor getRadiance(const Ray& ray) const;
private:
    float offset =  0.0001f;
    float stepSize = 0.06f;
    float fogDensity = 0.7;
    RGBColor fogColor = RGBColor::rep(1.0f);
    VSphere vSphere;
    RGBColor volumePointRadiance = RGBColor(0.886f, 0.345f, 0.133f); //Color of flame 
};

}

#endif