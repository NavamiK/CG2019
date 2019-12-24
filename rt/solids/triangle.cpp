#include <rt/solids/triangle.h>
#include <core/random.h>

namespace rt {

Triangle::Triangle(Point vertices[3], CoordMapper* texMapper, Material* material)
{
    /* TODO */
    this->v1 = vertices[0];
    this->v2 = vertices[1];
    this->v3 = vertices[2];
    this->material = material;
    if(texMapper!=nullptr) this->texMapper = texMapper;
    this->area = getArea();
}

Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material)
{
    /* TODO */
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
    this->material = material;
    if(texMapper!=nullptr) this->texMapper = texMapper;
    this->area = getArea();
}

BBox Triangle::getBounds() const {
    /* TODO */ 
    Point min, max;
    min.x = rt::min(v1.x, v2.x, v3.x);
    min.y = rt::min(v1.y, v2.y, v3.y);
    min.z = rt::min(v1.z, v2.z, v3.z);

    max.x = rt::max(v1.x, v2.x, v3.x);
    max.y = rt::max(v1.y, v2.y, v3.y);
    max.z = rt::max(v1.z, v2.z, v3.z);

    return BBox(min, max);
}

Intersection Triangle::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */
    Vector edge1, edge2, h, s, q;
    Vector rayVector = ray.d;
    Point rayOrigin = ray.o;
    float a,f,u,v;
    edge1 = v2 - v1;
    edge2 = v3 - v1;
    h = cross(rayVector, edge2);
    a = dot(edge1, h);
    if (a > -EPSILON && a < EPSILON)
        return Intersection::failure();   // This ray is parallel to this triangle.
    f = 1.0/a;
    s = rayOrigin - v1;
    u = f * dot(s, h);
    if (u < 0.0 || u > 1.0)
        return Intersection::failure();
    q = cross(s, edge1);
    v = f * dot(rayVector, q);
    if (v < 0.0 || u + v > 1.0)
       return Intersection::failure();
    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = f * dot(edge2, q);
    if ((t > EPSILON)&& (t < previousBestDistance)) // ray intersection
    {
        Vector normal = cross(edge1, edge2);
        Intersection intersection(t, ray, this, normal.normalize(), getBaryCoords(ray.getPoint(t)));
        return intersection;
    }
    else // This means that there is a line intersection but not a ray intersection.
        return  Intersection::failure();
}

Point Triangle::getBaryCoords(const Point& p) const{
    Point bary;
    bary.x = getArea(v2 - p, v3 - p) / area;
    bary.y = getArea(v1 - p, v3 - p) / area;
    bary.z = getArea(v1 - p, v2 - p) / area;
    assert(bary.x >=0  && bary.y >=0 && bary.z >=0);
    return bary;
}

Solid::Sample Triangle::sample() const {
    /* TODO */
    Vector s1, s2, s3;// sides of the triangle.
//    s1 = v1 - v2;
//    s2 = v2 - v3;
//    s3 = v3 - v1;

    ///test...
    s1 = v2 - v1;
    s2 = v3 - v1;
    ///test...

    //create a random vector in the triangle, and make points from it.
//    Vector vt = random() * s1 + random() * s2 + random() * s3;
//    Point p(vt.x, vt.y, vt.z);
//
//    // create 3 triangles with this point.
//    Triangle t1(v1, v2, p, nullptr, nullptr);
//    Triangle t2(v1, v3, p, nullptr, nullptr);
//    Triangle t3(v2, v3, p, nullptr, nullptr);
//
//    // calculate the lambdas.
//    float b1 = t1.getArea() / getArea();
//    float b2  = t2.getArea() / getArea();
//    float b3 = t3.getArea() / getArea();
//    float lambda1 = b1 / (b1 + b2 + b3);
//    float lambda2 = b2 / (b1 + b2 + b3);
//    float lambda3 = 1.f - (lambda1 + lambda2);

/////////////////////////////////try this.
    float r = random();
    float t = random();

    if((r + t) >= 1.f){
        r = 1.f - r;
        t = 1.f - t;
    }

    Point trianglePoint = v1 + (s1 * r) + s2 * t;
////////////////////////////////try this.

   // Point trianglePoint = lambda1*v1 + lambda2*v2 + lambda3*v3;
    Vector normal = cross(s1, s2);


    Sample sample;
    sample.point = trianglePoint;
    sample.normal = normal;
    return sample;

}

float Triangle::getArea(const Vector& edge1, const Vector& edge2) const{
    return cross(edge1, edge2).length()/2;
}

float Triangle::getArea() const {
    /* TODO */ 
    Vector edge1 = v2 - v1;
    Vector edge2 = v3 - v1;
    return getArea(edge1, edge2);
}

}
