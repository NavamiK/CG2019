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
    
    //1. transform with m
    //3. rotate around x
    //4. transform back with mt

    //create a system of matrices.
    Vector r = nnaxis.normalize();
    float x = r.x, y = r.y, z = r.z;
    Vector s;

    float minVal = min(abs(x), abs(y), abs(z));
    if(x == minVal)
        s = Vector(0.f, -z, y);
    else if(y == minVal)
        s = Vector(-z, 0.f, x);
    else if(z == minVal)
        s = Vector(-y, x, 0.f);

    s = s.normalize();

    assert(s != Vector::rep(0.f));
    assert(dot(s, r) == 0); // must be orthogonal.

    Vector t = cross(r, s);
    
    Matrix m = Matrix::system(r, s, t);
    Matrix Rx{
        Float4(1.f, 0.f    , 0.f      ,0.f),
        Float4(0.f, cos(angle) , -sin(angle)  ,0.f),
        Float4(0.f, sin(angle), cos(angle)  ,0.f),
        Float4(0.f, 0.f    , 0.f     ,1.f)
    };
    transformation = product(product(m, Rx), m.transpose()); 
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
    Point prevHitPointTrans = invTrans * ray.getPoint(previousBestDistance);
    float prevBestDistanceTrans = (prevHitPointTrans - rayTrans.o).length();

    Intersection intersectionTrans = this->archetype->intersect(rayTrans, prevBestDistanceTrans);

    if(intersectionTrans){      
        Vector normal = transformation * intersectionTrans.normal();
        Point hitPoint = transformation * rayTrans.getPoint(intersectionTrans.distance);
        float distance = (hitPoint - ray.o).length();

        Intersection intersection(distance, ray, intersectionTrans.solid, normal, intersectionTrans.local()); 
        return intersection; 
    }
    else
        return intersectionTrans;  
}

BBox Instance::getBounds() const {
    /* TODO */
    return archetype->getBounds();
}

}