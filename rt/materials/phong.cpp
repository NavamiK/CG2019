#include <rt/materials/phong.h>
#include <cmath>
#include <rt/textures/texture.h>

namespace rt {

PhongMaterial::PhongMaterial(Texture* specular, float exponent)
{
    /* TODO */
    this->specular = specular;
    this->exponent = exponent;
}

RGBColor PhongMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    /* TODO */
    //TODO: verify formula is correct. and check cosTheta > 0.
    Vector reflDir = (inDir - 2 * dot(inDir, normal) * normal).normalize();
    float cosTheta = dot(reflDir, outDir);
    return specular->getColor(texPoint) * pow(cosTheta, exponent) / dot(inDir, normal);
    //return specular->getColor(texPoint) * pow(cosTheta, exponent);
}

RGBColor PhongMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */
    //return specular->getColor(texPoint);
    //No self-emission unless mentioned
    return RGBColor::rep(0.0f);
}

Material::SampleReflectance PhongMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	UNREACHABLE;
}

Material::Sampling PhongMaterial::useSampling() const {
	/* TODO */
	return SAMPLING_NOT_NEEDED;
}

}