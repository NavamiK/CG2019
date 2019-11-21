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
    //1. translate p to origin (what's p)?
    //2. translate m
    //3. rotate around x
    //4. transform back with mt
    //5. translate back to p.

    //////////////// crate a system of matrices.
    float x = nnaxis.x, y = nnaxis.y, z = nnaxis.z;
    Vector s = Vector::rep(0.f);
    float minVal = min(min(x, y), z);
    if(x == minVal){
        s = Vector(0, -z, y);
    }
    if(y == minVal){
        s = Vector(-z, 0, x);
    }
    if(z == minVal){
        s = Vector(-y, x, 0);
    }
    s = s.normalize();


    //failed.
    assert(s != Vector::rep(0.f));
    assert(dot(s, nnaxis) == 0); // must be orthogonal.

    Vector t = cross(nnaxis, s);
    Vector e1 = nnaxis, e2 = s, e3 = t;
    Matrix m = Matrix::system(e1, e2, e3);
    Matrix mt = m.invert();
    float B = (pi/180.f) * angle;
    //////////////// crate a system of matrices.
    Matrix Rx{
        Float4(1.f, 0.f    , 0.f      ,0.f),
        Float4(0.f, cos(B) , -sin(B)  ,0.f),
        Float4(0.f, sin(B), cos(B)  ,0.f),
        Float4(0.f, 0.f    , 0.f     ,1.f)
    };

    transformation = product(product(m, Rx), mt); // the formula on slide 30, missing point tho.
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