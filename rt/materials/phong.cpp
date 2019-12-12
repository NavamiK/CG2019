#include <rt/materials/phong.h>
#include <cmath>
#include <rt/textures/texture.h>
#include <core/scalar.h>

namespace rt {

PhongMaterial::PhongMaterial(Texture* specular, float exponent)
{
    /* TODO */
    this->specular = specular;
    this->exponent = exponent;
}

RGBColor PhongMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    /* TODO */
    
    Vector reflDir = (inDir - 2 * dot(inDir, normal) * normal).normalize();
    float cosTheta = dot(reflDir, outDir);
    if (cosTheta < 0 || dot(-inDir, normal) < 0)
    		return RGBColor(0,0,0);
    return specular->getColor(texPoint) * (powf(cosTheta, exponent) * 2 * pi) / ((exponent + 2) *  std::fabs(dot(normal, inDir)));
}

RGBColor PhongMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */
    return RGBColor::rep(0.0f);
}

Material::SampleReflectance PhongMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	return Material::SampleReflectance();
}

Material::Sampling PhongMaterial::useSampling() const {
	/* TODO */
	return SAMPLING_NOT_NEEDED;
}

}