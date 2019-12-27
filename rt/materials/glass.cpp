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


Vector refract(const Vector I, const Vector &N, const float &ior) 
{ 
    float cosi = dot(I, N); 
    float etai = 1, etat = ior; 
    Vector n = N; 
    if (cosi < 0) { cosi = -cosi; } else { std::swap(etai, etat); n = -N; } 
    float eta = etai / etat; 
    float k = 1 - eta * eta * (1 - cosi * cosi); 
    if (k < 0)
        return Vector::rep(0.f);
    else
        return eta * I + (eta * cosi - sqrtf(k)) * n; 
}

float fresnel(const Vector I, const Vector &N, const float &ior) 
{ 
    float kr;
    float cosi = dot(I, N); 
    float etai = 1, etat = ior; 
    if (cosi > 0) { std::swap(etai, etat); } 
    // Compute sini using Snell's law
    float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi)); 
    // Total internal reflection
    if (sint >= 1) { 
        kr = 1; 
    } 
    else { 
        float cost = sqrtf(std::max(0.f, 1 - sint * sint)); 
        cosi = fabsf(cosi); 
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost)); 
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost)); 
        kr = (Rs * Rs + Rp * Rp) / 2; 
    } 
    // As a consequence of the conservation of energy, transmittance is given by:
    // kt = 1 - kr;
    return kr;
} 

Material::SampleReflectance GlassMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */
    // Logic as per 
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel   
    Vector reflDir = (-outDir + (2 * dot(outDir, normal) * normal)).normalize();
    Vector refractionVector = refract(-reflDir, normal, eta);
    float kr = fresnel(-reflDir, normal, eta); 
    if(abs(kr-1)<EPSILON)  
        return SampleReflectance(reflDir, RGBColor::rep(kr));
    else if(random() < 0.5f)
        return SampleReflectance(reflDir, RGBColor::rep(kr));
    else 
        return SampleReflectance(refractionVector, RGBColor::rep((1.f-kr)/sqrt(eta)));
}

Material::Sampling GlassMaterial::useSampling() const {
    /* TODO */
    return SAMPLING_ALL;
}

}