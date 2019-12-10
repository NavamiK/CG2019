
#include <rt/materials/cookTorrance.h>
#include <rt/textures/texture.h>
#include <core/scalar.h>
#include <cmath>
#include <algorithm>


namespace rt {
    CookTorrance::CookTorrance(rt::Texture *glossy, rt::Texture *diffuse, float kappa, float eta) {
        this->glossy = glossy;
        this->diffuse = diffuse;
        this->kappa = kappa;
        this->eta = eta;
    }

    RGBColor CookTorrance::getReflectance(const rt::Point &texPoint, const rt::Vector &normal, const rt::Vector &outDir,const rt::Vector &inDir) const {
        RGBColor Fr = getFresnel(normal, inDir, outDir);
        float G = getGeometricAttenuation(normal, inDir, outDir);
        float D = getMicrofacetDistribution(normal, inDir, outDir);
        RGBColor kGlossy = Fr * D * G / (pi * dot(normal, outDir) * dot(normal, inDir));
        RGBColor kDiffuse = (1.f/pi) * dot(normal, inDir) * diffuse->getColor(texPoint);

        // glossy and diffuse constants. should sum up to one. //TODO; change later, just a guess for now.
        float Pd = 0.5f, Pg = 0.5f;

        return kGlossy*Pg + kDiffuse*Pd; // = brdf.
    }

    RGBColor CookTorrance::getEmission(const rt::Point &texPoint, const rt::Vector &normal,const rt::Vector &outDir) const {
        return RGBColor::rep(0.f);
    }

    Material::SampleReflectance CookTorrance::getSampleReflectance(const rt::Point &texPoint, const rt::Vector &normal,const rt::Vector &outDir) const {
        // TODO: how should this be implemented with sampling secondary?
        NOT_IMPLEMENTED;
    }

    Material::Sampling CookTorrance::useSampling() const {
        return SAMPLING_SECONDARY;
    }

    RGBColor CookTorrance::getFresnel(const Vector &normal, const Vector &inDir, const Vector &outDir) const {
        //copied from mirror reflectance function.
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

    float CookTorrance::getGeometricAttenuation(const rt::Vector &normal, const rt::Vector &inDir,const rt::Vector &outDir) const {
       Vector H = (inDir + outDir).normalize();
       float gReflected = 2.f * dot(normal, H) * dot(normal, outDir) / dot(outDir, H);
       float gIncident = 2.f * dot(normal, H) * dot(normal, inDir) / dot(outDir, H);

       return std::min(1.f, min(gReflected, gIncident));
    }

    float CookTorrance::getMicrofacetDistribution(const rt::Vector &normal, const rt::Vector &inDir,const rt::Vector &outDir) const {
        // found a formula for H at:
        //https://computergraphics.stackexchange.com/questions/4394/path-tracing-the-cook-torrance-brdf
        Vector H = (inDir + outDir).normalize();
        float theta = dot(normal, H);
        float x = pow(tan(theta) / m, 2);
        float D = (1.f/(pi * m*m * pow(cos(theta), 4))) * exp(-x);
        return D;
    }

}
