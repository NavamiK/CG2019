#include <rt/primmod/bmap.h>
#include <core/assert.h>
#include <rt/solids/triangle.h>
#include <rt/textures/texture.h>
#include <rt/coordmappers/tmapper.h>
#include <core/matrix.h>

namespace rt {

BumpMapper::BumpMapper(Triangle* base, Texture* bumpmap, const Point& bv1, const Point& bv2, const Point& bv3, float vscale)
{
    this->base = base;
    this->bumpMap = bumpmap;
    this->bv1 = bv1;
    this->bv2 = bv2;
    this->bv3 = bv3;
    tbv12 = bv2 - bv1;
    tbv13 = bv3 - bv1;
    tNormal = cross(tbv12, tbv13);
}

BBox BumpMapper::getBounds() const {
    /* TODO */
    return base->getBounds(); //TODO: may add the texture bounds here.
}

Intersection BumpMapper::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */
    Intersection intersection = base->intersect(ray, previousBestDistance);

    if(intersection){
        //texture coordinates.
        Point local = intersection.local();
        Point hitTex = local.x * bv1 + local.y * bv2 + local.z * bv3;
        RGBColor dx = bumpMap->getColorDX(hitTex);
        RGBColor dy = bumpMap->getColorDY(hitTex);

         != RGBColor::rep(0.f)){
            std::cout << "it's not zero\n";
        }

        //from texture base, to world space.
        //TODO: I think this is wrong.
        Matrix tm(Float4(tbv12.x, tbv13.x, tNormal.x, bv1.x),
                  Float4(tbv12.y, tbv13.y, tNormal.y, bv1.y),
                  Float4(tbv12.z, tbv13.z, tNormal.z, bv1.z),
                  Float4(0,       0,       0,         1.f));
        //tm = tm.invert();
        //TODO: I think this too.
        Vector w1 = tm * tbv12;
        Vector w2 = tm * tbv13;



        //Multiply world vectors and the gradient to perturb the normal in world space.
        Vector u = cross(w1, dx);
        Vector v = cross(w2, dy);
        Vector N = intersection.normal();

        Vector D = cross(N, v) - cross(N, u);
        N = (N + D).normalize();
        intersection.setNormal(N);
    }
    return intersection;
}

void BumpMapper::setMaterial(Material* m) {
    /* TODO */
    material = m;
}

void BumpMapper::setCoordMapper(CoordMapper* cm) {
    /* TODO */
    coordMapper = cm;
}

}