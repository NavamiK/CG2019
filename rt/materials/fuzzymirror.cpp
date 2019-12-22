#include <rt/materials/fuzzymirror.h>
#include <rt/solids/disc.h>

namespace rt {

FuzzyMirrorMaterial::FuzzyMirrorMaterial(float eta, float kappa, float fuzzyangle)
{
    this->eta = eta;
    this->kappa = kappa;
    this->fuzzyAngle = fuzzyangle;
}

RGBColor FuzzyMirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    /* TODO */
    return RGBColor::rep(0.f);
}

RGBColor FuzzyMirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */
    return RGBColor::rep(0.f);
}

Material::SampleReflectance FuzzyMirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {

    Vector perfectReflection = -outDir + 2.f * dot(outDir, normal) * normal;

    //TODO: disk may not be at unit distance.
    //TODO: what do they mean by "ray direction" in the description.
    float radius = fabs(dot(perfectReflection, normal) - fuzzyAngle);
    Disc disc(texPoint, -perfectReflection.normalize(), radius, nullptr, nullptr);

    Vector direction = disc.sample().point - texPoint;

    // Slide # 46 (metals).
    float cosIn = dot(normal, outDir);
    float rParallel = ((eta*eta + kappa*kappa)*cosIn*cosIn - 2.f*cosIn + 1) /
            ((eta*eta + kappa*kappa)*cosIn*cosIn + 2.f*cosIn + 1);

    float rPerpendicular = ((eta*eta + kappa*kappa) - 2.f*eta*cosIn + cosIn*cosIn)/
            ((eta*eta + kappa*kappa) + 2.f*eta*cosIn + cosIn*cosIn);

    float Fr = 0.5f * (rParallel + rPerpendicular);

    return SampleReflectance(direction, RGBColor::rep(Fr));


}

Material::Sampling FuzzyMirrorMaterial::useSampling() const {
    /* TODO */
    return SAMPLING_ALL;
}

}
