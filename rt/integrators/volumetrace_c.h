#ifndef CG1RAYTRACER_INTEGRATORS_VOLUMETRACING_C_HEADER
#define CG1RAYTRACER_INTEGRATORS_VOLUMETRACING_C_HEADER

#include <rt/integrators/integrator.h>
#include <core/scalar.h>
#include <core/interpolate.h>
#include <vector>

namespace rt {
class World;
class Ray;
class RGBColor;
class Vector;

class VolumeTracingCIntegrator : public Integrator {
public:
    VolumeTracingCIntegrator(World* world);
    virtual RGBColor getRadiance(const Ray& ray) const;
    RGBColor getVolumeReflectance(Vector outDir, Vector inDir) const;

    void addOctave(float amplitude, float frequency);
    float getDensity(Point coord) const;

private:
    float offset =  0.0001f;
    float stepSize = 5.0f;
    //float fogDensity = 0.4;
    float isoPhaseFunctionVal = 1.f / (4 * pi);
    float g = -0.5;
    float g_sq = g * g;
    //float fogStepAttenuation = exp(-1 * stepSize * fogDensity);

    float fogDensityMax, fogDensityMin;
    std::vector<float> amplitudes;
    std::vector<float> frequencies;
};

}

#endif