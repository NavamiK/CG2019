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
    /* TODO */ NOT_IMPLEMENTED;
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