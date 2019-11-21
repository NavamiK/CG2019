#include <rt/primmod/instance.h>

namespace rt {

Instance::Instance(Primitive* content)
{
    archetype = content;
    transformation = Matrix::identity();
}

Primitive* Instance::content() {
    /* TODO */
    return archetype;
}

void Instance::reset() {
    /* TODO */
    transformation = Matrix::identity();
}

void Instance::translate(const Vector& t) {
    /* TODO */
    Matrix tMatrix{
            Float4(1.f, 0.f, 0.f, t.x),
            Float4(0.f, 1.f, 0.f, t.y),
            Float4(0.f, 0.f, 1.f, t.z),
            Float4(0.f, 0.f, 0.f, 1.f)
    };
    transformation = product(tMatrix, transformation);
}

void Instance::rotate(const Vector& nnaxis, float angle) {
    /* TODO */
    Matrix tMatrix, m1, m2;
    float x = nnaxis.x, y = nnaxis.y, z = nnaxis.z;
    m1 = {
            Float4(x*x, x*y, x*z, 0.f),
            Float4(x*y, y*y, y*z, 0.f),
            Float4(x*z, y*z, z*z, 0.f),
            Float4(0.f, 0.f, 0.f, 1.f)
    };

    m2 = {
            Float4( 0,    -z,   y,   0.f),
            Float4( z,     0,   -x,   0.f),
            Float4(-y,    x,     0,   0.f),
            Float4(0.f, 0.f,   0.f,   1.f)
    };

    //float B = (pi / 180.f) * angle;//convert to radians.
    tMatrix = cos(angle)*(Matrix::identity()) + (1.f - cos(angle))*m1 + sin(angle)*m2;
    transformation = product(tMatrix, transformation);
}

void Instance::scale(float f) {
    /* TODO */ 
    Matrix tMatrix{
            Float4(f, 0.f, 0.f, 0.f),
            Float4(0.f, f, 0.f, 0.f),
            Float4(0.f, 0.f, f, 0.f),
            Float4(0.f, 0.f, 0.f, 1.f)
    };
    transformation = product(tMatrix, transformation);
}

void Instance::scale(const Vector& s) {
    /* TODO */  
    Matrix tMatrix{
            Float4(s.x, 0.f, 0.f, 0.f),
            Float4(0.f, s.y, 0.f, 0.f),
            Float4(0.f, 0.f, s.z, 0.f),
            Float4(0.f, 0.f, 0.f, 1.f)
    };
    transformation = product(tMatrix, transformation);
}

void Instance::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void Instance::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Instance::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */ 
    Matrix invTrans = transformation.invert();

    Ray rayTrans(invTrans * ray.o, invTrans * ray.d);
    // Transform previousBestDistance
    float prevBestDistanceTrans = (ray.o.x - rayTrans.o.x + previousBestDistance * ray.d.x) / rayTrans.d.x;
    Intersection intersectionTrans = this->archetype->intersect(rayTrans, prevBestDistanceTrans);

    if(intersectionTrans){
        Vector normal = transformation * intersectionTrans.normal();
        float hitPointDistance =  (rayTrans.o.x - ray.o.x + intersectionTrans.distance * rayTrans.d.x) / ray.d.x;
        Intersection intersection(hitPointDistance, ray, intersectionTrans.solid, normal, intersectionTrans.local()); 
        return intersection; 
    }
//    else
//        intersectionTrans;

    return intersectionTrans;
}

BBox Instance::getBounds() const {
    /* TODO */
    return archetype->getBounds();
}

}