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
    float refract_index = eta;
    if(dot(normal, outDir) > 0.f){
        refract_index = 1.f/eta;
    }

    Vector reflection_dir = -outDir + (2 * dot(outDir, normal) * normal);
    Vector refraction_dir = getRefractrationDir(refract_index, normal, outDir);

    Vector direction;
    if(refraction_dir != Vector::rep(0.f)){
        // randomly choose one direction.
        if(random() < 0.5)
            direction = reflection_dir;
        else
            direction = refraction_dir;
    }else{
        direction = reflection_dir;
    }

    // slide # 46. materials.
    float cosTheta = dot(normal, outDir.normalize());
    float rParallel = ((eta*eta)* cosTheta*cosTheta - 2.f * eta * cosTheta + 1) /
                      ((eta*eta)* cosTheta*cosTheta + 2.f * eta * cosTheta + 1);
    float rPerpendicular = ((eta*eta) - 2*eta*cosTheta + cosTheta*cosTheta) /
            ((eta*eta) + 2*eta*cosTheta + cosTheta*cosTheta);

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