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
            Float4(0.f, 0.f, 0.f, t.z),
            Float4(0.f, 0.f, 0.f,   1)
    };
    transformation = product(transformation, tMatrix);
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

    tMatrix = cos(angle)*(Matrix::identity()) + (1.f - cos(angle))*m1 + sin(angle)*m2;
    transformation = product(transformation, tMatrix);
}

void Instance::scale(float f) {
    /* TODO */ NOT_IMPLEMENTED;
}

void Instance::scale(const Vector& s) {
    /* TODO */ NOT_IMPLEMENTED;
}

void Instance::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void Instance::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Instance::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */ NOT_IMPLEMENTED;
}

BBox Instance::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

}