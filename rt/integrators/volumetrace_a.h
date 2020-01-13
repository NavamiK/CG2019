#ifndef CG1RAYTRACER_INTEGRATORS_VOLUMETRACING_A_HEADER
#define CG1RAYTRACER_INTEGRATORS_VOLUMETRACING_A_HEADER

#include <rt/integrators/integrator.h>

namespace rt {
class World;
class Ray;
class RGBColor;

class VolumeTracingAIntegrator : public Integrator {
public:
    VolumeTracingAIntegrator(World* world) : Integrator(world) {}
    virtual RGBColor getRadiance(const Ray& ray) const;
private:
    float offset =  0.0001f;
    float stepSize = 5.0f;
    float fogDensity = 0.7;
    RGBColor fogColor = RGBColor::rep(1.0f);
};

}

#endif