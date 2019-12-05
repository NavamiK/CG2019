#include <rt/materials/mirror.h>
#include <core/scalar.h>

namespace rt {

MirrorMaterial::MirrorMaterial(float eta, float kappa)
{
    this->eta = eta;
    this->kappa = kappa;
}

RGBColor MirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    /* TODO */
    //TODO; you may flip the normal to face the same direction as the in and our vecs.
    float cosThetaIn = dot(inDir, normal);
    float cosThetaOut = dot(outDir, normal);
    float delta = fabs(cosThetaIn - cosThetaOut) == 0.f ? 1.f : 0.f;

    float denom = 1.f/(kappa*cosThetaIn + eta*cosThetaOut);
    float r1 = (kappa*cosThetaIn - eta*cosThetaOut) * denom;
    float r2 = (eta*cosThetaIn - kappa*cosThetaOut) * denom;
    float Fr = 0.5f * (r1 + r2);
    float brdf = Fr * delta/fabs(cosThetaIn);

    return RGBColor::rep(brdf);
}

RGBColor MirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */
    //TODO: verify.
    return RGBColor::rep(0.f); // I don't think mirrors emit light.
}

Material::SampleReflectance MirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */
    if(useSampling() == SAMPLING_NOT_NEEDED){
        SampleReflectance sampleRef;
        sampleRef.direction = outDir;
        sampleRef.reflectance = RGBColor::rep(0.f);
        return sampleRef;
    }
    NOT_IMPLEMENTED; //TODO: check the other conditions.
}

Material::Sampling MirrorMaterial::useSampling() const {
    /* TODO */
    return SAMPLING_ALL;
}

}