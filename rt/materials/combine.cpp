#include <rt/materials/combine.h>

namespace rt {

CombineMaterial::CombineMaterial()
{
    /* TODO */
}

void CombineMaterial::add(Material* m, float w) {
    materials.push_back(std::make_pair(m, w));
}

RGBColor CombineMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    RGBColor reflectance;
    for(auto m : materials){
        reflectance = reflectance + m.first->getReflectance(texPoint, normal, outDir, inDir);
    }

    return reflectance;
}

RGBColor CombineMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    RGBColor emissions = RGBColor::rep(0.f);
    for(size_t i = 0; i < materials.size(); i++){
        emissions = emissions + materials[i].first->getEmission(texPoint, normal, outDir);
    }

    return emissions;
}

Material::SampleReflectance CombineMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */
    Sampling sampling;
    SampleReflectance sampleRef;
    RGBColor reflectance = RGBColor::rep(0.f);
    rt::Vector direction = Vector::rep(0.f);//I really don't know what do with this; so I will just add it up.
    for(auto m : materials){
        sampling = m.first->useSampling();
        if(sampling == Material::SAMPLING_ALL || sampling == Material::SAMPLING_SECONDARY) {
            sampleRef = m.first->getSampleReflectance(texPoint, normal, outDir);
            reflectance = reflectance + sampleRef.reflectance * m.second; // weight the reflectance.
            direction = direction + sampleRef.direction;
        }
    }

    return (SampleReflectance(direction, reflectance));
}

Material::Sampling CombineMaterial::useSampling() const {
    return SAMPLING_SECONDARY;
}

}