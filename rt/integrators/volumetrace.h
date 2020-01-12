#ifndef CG1RAYTRACER_INTEGRATORS_VOLUMETRACING_HEADER
#define CG1RAYTRACER_INTEGRATORS_VOLUMETRACING_HEADER

#include <rt/integrators/integrator.h>

namespace rt {
class World;
class Ray;
class RGBColor;

class VolumeTracingIntegrator : public Integrator {
public:
    VolumeTracingIntegrator(World* world) : Integrator(world) {}
    virtual RGBColor getRadiance(const Ray& ray) const;
private:
    float offset =  0.0001f;
};

}

#endif