#include <rt/materials/dummy.h>
#include <core/assert.h>

namespace rt {

DummyMaterial::DummyMaterial() {
    /* TODO */
    this->brdf  = 1.0f;
}

RGBColor DummyMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    /* TODO */ 
    float reflectance = this->brdf * dot(normal, inDir);
    return RGBColor::rep(abs(reflectance));

}

RGBColor DummyMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */ 
    return RGBColor::rep(0.0f);
}

Material::SampleReflectance DummyMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */ NOT_IMPLEMENTED;
}

}