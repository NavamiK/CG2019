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
    /*
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
    */
    O_u = Vector(1, 0, 0);
    O_v = Vector(0, 1, 0);     
}

BBox BumpMapper::getBounds() const {
    /* TODO */
    return base->getBounds();
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
        
        Vector N = intersection.normal();
        Vector D = dx.g * cross(N, O_v) - dy.g * cross(N, O_u);
        
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