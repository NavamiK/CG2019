#include <rt/solids/striangle.h>
#include <rt/intersection.h>
#include <core/interpolate.h>

namespace rt {

SmoothTriangle::SmoothTriangle(Point vertices[3], Vector normals[3], CoordMapper* texMapper, Material* material)
{
    /* TODO */
    this->v1 = vertices[0];
    this->v2 = vertices[1];
    this->v3 = vertices[2];
    this->n1 = normals[0];
    this->n2 = normals[1];
    this->n3 = normals[2];
    this->material = material;
    if(texMapper!=nullptr) this->texMapper = texMapper;
    this->edge1 = v2 - v1;
    this->edge2 = v3 - v1;
    this->area = this->getAreaSmoothT(edge1, edge2);   
}

SmoothTriangle::SmoothTriangle(const Point& v1, const Point& v2, const Point& v3, const Vector& n1, const Vector& n2, const Vector& n3, CoordMapper* texMapper, Material* material)
{
    /* TODO */
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
    this->n1 = n1;
    this->n2 = n2;
    this->n3 = n3;
    this->material = material;
    if(texMapper!=nullptr) this->texMapper = texMapper;
    this->edge1 = v2 - v1;
    this->edge2 = v3 - v1;
    this->area = this->getAreaSmoothT(edge1, edge2);
}

Intersection SmoothTriangle::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */  Vector h, s, q;
    Vector rayVector = ray.d;
    Point rayOrigin = ray.o;
    float a,f,u,v;
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
    if ((t > EPSILON)&& (t < previousBestDistance)) {
        Point baryPoint = this->getBaryCoordsSmoothT(ray.getPoint(t));
        Vector normal = lerpbar(n1, n2, n3, baryPoint.x, baryPoint.y).normalize();
        return Intersection(t, ray, this, normal, baryPoint);
    }
    else 
        return  Intersection::failure();
}

Point SmoothTriangle::getBaryCoordsSmoothT(const Point& p) const{
    Point bary;
    bary.x = getAreaSmoothT(v2 - p, v3 - p) / area;
    bary.y = getAreaSmoothT(v1 - p, v3 - p) / area;
    bary.z = getAreaSmoothT(v1 - p, v2 - p) / area;
    assert(bary.x >=0  && bary.y >=0 && bary.z >=0);
    return bary;
}

float SmoothTriangle::getAreaSmoothT(const Vector& edge1, const Vector& edge2) const{
    return cross(edge1, edge2).length()/2;
}

}