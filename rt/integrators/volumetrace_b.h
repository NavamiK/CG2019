#ifndef CG1RAYTRACER_INTEGRATORS_VOLUMETRACING_B_HEADER
#define CG1RAYTRACER_INTEGRATORS_VOLUMETRACING_B_HEADER

#include <rt/integrators/integrator.h>
#include <core/scalar.h>

namespace rt {
class World;
class Ray;
class RGBColor;
class Vector;

class VolumeTracingBIntegrator : public Integrator {
public:
    VolumeTracingBIntegrator(World* world) : Integrator(world) {}
    virtual RGBColor getRadiance(const Ray& ray) const;
    RGBColor getVolumeReflectance(Vector outDir, Vector inDir) const;
private:
    float offset =  0.0001f;
    float stepSize = 5.0f;
    float fogDensity = 0.4;
    float isoPhaseFunctionVal = 1.f / (4 * pi);
    float g = 0.3;
    float g_sq = g * g;
    float fogStepAttenuation = exp(-1 * stepSize * fogDensity);
};

}

#endif