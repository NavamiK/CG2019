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
    mTexToLocal = Matrix(
                  Float4(tbv12.x, tbv13.x, 0, bv1.x),
                  Float4(tbv12.y, tbv13.y, 0, bv1.y),
                  Float4(0,       0,       1, 0),
                  Float4(0,       0,       0, 1)).invert();
    Vector v12 = base->v2 - base->v1;
    Vector v13 = base->v3 - base->v1;
    Vector normal = cross(v12, v13); 
    mLocalToWorld = Matrix(
        Float4(v12.x, v13.x, normal.x, (base->v1).x),
        Float4(v12.y, v13.y, normal.y, (base->v1).y),
        Float4(v12.z, v13.z, normal.z, (base->v1).z),
        Float4(0,     0,     0,        1)
    );
    mTexToWorld = product(mLocalToWorld, mTexToLocal);
    wx = mTexToWorld * tbv12;
    wy = mTexToWorld * tbv13;
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
        //dy =  RGBColor::rep(0.f);

        /*
        if(dx != RGBColor::rep(0.f)){
            std::cout << "it's not zero\n";
        }
        */

        //from texture base, to world space.
        //TODO: I think this is wrong.
        /*
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
        */
        Vector O_u(1, 0, 0);
        Vector O_v(0, 1, 0); 
        Vector N = intersection.normal();
        Vector D = dx.g * cross(N, O_v) - dy.g * cross(N, O_u);
        //Vector D = dx.g * wx + dy.g * wy;
        
        N = (N - D).normalize();
        intersection.setNormal(N);
    }
    return intersection;
}

void BumpMapper::setMaterial(Material* m) {
    /* TODO */
    base->setMaterial(m);
}

void BumpMapper::setCoordMapper(CoordMapper* cm) {
    /* TODO */
    base->setCoordMapper(cm);
}

}