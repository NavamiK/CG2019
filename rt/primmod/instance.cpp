#include <rt/primmod/instance.h>

namespace rt {

Instance::Instance(Primitive* content)
{
    archetype = content;
    transformation = Matrix::identity();
    invTrans = transformation;
}

Primitive* Instance::content() {
    /* TODO */
    return archetype;
}

void Instance::reset() {
    /* TODO */
    transformation = Matrix::identity();
    invTrans = transformation;
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
    invTrans = transformation.invert();
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
    invTrans = transformation.invert();
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
    invTrans = transformation.invert();
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
    invTrans = transformation.invert();
}

void Instance::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void Instance::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Instance::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */ 
    Point invRayOrig = invTrans * ray.o;
    Vector invRayDir = invTrans * ray.d;

    float dirLength = invRayDir.length();
    Ray rayTrans(invRayOrig, invRayDir.normalize());

    Intersection intersectionTrans = this->archetype->intersect(rayTrans, previousBestDistance * dirLength);

    if(intersectionTrans){      
        Vector normal = invTrans.transpose() * intersectionTrans.normal();
        Intersection intersection(intersectionTrans.distance/dirLength, ray, intersectionTrans.solid, normal.normalize(), intersectionTrans.local()); 
        return intersection; 
    }
    else
        return intersectionTrans;  
}

BBox Instance::getBounds() const {
    /* TODO */
    BBox bound = archetype->getBounds();
    Point c1(bound.min.x, bound.min.y, bound.min.z);
    Point c2(bound.max.x, bound.min.y, bound.min.z);
    Point c3(bound.min.x, bound.max.y, bound.min.z);
    Point c4(bound.min.x, bound.min.y, bound.max.z);
    Point c5(bound.min.x, bound.max.y, bound.max.z);
    Point c6(bound.max.x, bound.max.y, bound.min.z);
    Point c7(bound.max.x, bound.min.y, bound.max.z);
    Point c8(bound.max.x, bound.max.y, bound.max.z);
    Point c1Trans = invTrans * c1; 
    Point c2Trans = invTrans * c2; 
    Point c3Trans = invTrans * c3; 
    Point c4Trans = invTrans * c4; 
    Point c5Trans = invTrans * c5; 
    Point c6Trans = invTrans * c6; 
    Point c7Trans = invTrans * c7; 
    Point c8Trans = invTrans * c8; 
    float minx = min(
              min(c1Trans.x, c2Trans.x, c3Trans.x), 
              min(c4Trans.x, c5Trans.x, c6Trans.x), 
              min(c7Trans.x, c8Trans.x));
    float miny = min(
              min(c1Trans.y, c2Trans.y, c3Trans.y), 
              min(c4Trans.y, c5Trans.y, c6Trans.y), 
              min(c7Trans.y, c8Trans.y));
    float minz = min(
              min(c1Trans.z, c2Trans.z, c3Trans.z), 
              min(c4Trans.z, c5Trans.z, c6Trans.z), 
              min(c7Trans.z, c8Trans.z));              
    float maxx = max(
              max(c1Trans.x, c2Trans.x, c3Trans.x), 
              max(c4Trans.x, c5Trans.x, c6Trans.x), 
              max(c7Trans.x, c8Trans.x));
    float maxy = max(
              max(c1Trans.y, c2Trans.y, c3Trans.y), 
              max(c4Trans.y, c5Trans.y, c6Trans.y), 
              max(c7Trans.y, c8Trans.y));
    float maxz = max(
              max(c1Trans.z, c2Trans.z, c3Trans.z), 
              max(c4Trans.z, c5Trans.z, c6Trans.z), 
              max(c7Trans.z, c8Trans.z));
   
    return BBox(Point(minx, miny, minz), Point(maxx, maxy, maxz));

}

}