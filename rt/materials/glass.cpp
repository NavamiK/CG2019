#include <rt/materials/glass.h>
#include <core/random.h>
#include <cmath>

namespace rt {

GlassMaterial::GlassMaterial(float eta)
{
    this->eta = eta;
}

RGBColor GlassMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    /* TODO */
    return RGBColor::rep(0.f);
}

RGBColor GlassMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */
    return RGBColor::rep(0.f);
}

Material::SampleReflectance GlassMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */
    float ni = eta;
    Vector outwardNormal;

    Vector reflection_dir = -outDir + (2 * dot(outDir, normal) * normal);

    Vector direction;
    if(dot(normal, outDir) > 0.f){
        direction = reflection_dir;
        outwardNormal = -normal;
    }
    else{
        outwardNormal = normal;
        ni = 1.f/eta;
    }

    Vector refraction_dir = getRefractrationDir(eta, outwardNormal, outDir);

    if(refraction_dir != Vector::rep(0.f)){
        direction = refraction_dir;
    }
    else{
        direction = reflection_dir;
    }

    // slide # 47. materials.
    float cosThetaI = dot(normal, reflection_dir);
    float cosThetaT = dot(outwardNormal, refraction_dir);
    float rParallel = (ni * cosThetaI - ni * cosThetaT) / (ni * cosThetaI + ni * cosThetaT);
    float rPerpendicular = (ni * cosThetaI - ni * cosThetaT) / (ni * cosThetaI + ni * cosThetaT);

    float Fr = 0.5f * (rParallel + rPerpendicular);

    return SampleReflectance(direction, RGBColor::rep(Fr));
}

Material::Sampling GlassMaterial::useSampling() const {
    /* TODO */
    return SAMPLING_ALL;
}

Vector GlassMaterial::getRefractrationDir(float idx, rt::Vector normal, rt::Vector outDir) const {
    //source: https://en.wikipedia.org/wiki/Snell%27s_law
    float discriminant = 1 - (idx*idx) * (1 - dot(normal, outDir)*dot(normal, outDir));
    if(discriminant > 0){//refract vector.
        return idx*(outDir.normalize() - normal * dot(normal, outDir)) - normal * sqrt(discriminant);
    }

    return Vector::rep(0.f);
}

}