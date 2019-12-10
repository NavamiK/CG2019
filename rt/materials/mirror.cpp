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
    //TODO: this should not be here. this is for dielectrics.
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
    //copied from cookTorrance.
    // return mirror sample reflectance.
    Vector reflectionDirection = -outDir + 2.f * dot(outDir, normal) * normal;
    //slide# 31.
    float mirrorBrdf = 1.f / dot(normal, outDir); // TODO: don't know if this is correct.
    RGBColor reflectance = RGBColor::rep(mirrorBrdf);

    SampleReflectance ref;
    ref.direction = reflectionDirection;
    ref.reflectance = reflectance;
    return ref;
}

Material::Sampling MirrorMaterial::useSampling() const {
    /* TODO */
    return SAMPLING_ALL;
}

}