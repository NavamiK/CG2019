#include <core/matrix.h>
#include <core/assert.h>

#include <core/vector.h>
#include <core/point.h>

namespace rt {

Matrix::Matrix(const Float4& r1, const Float4& r2, const Float4& r3, const Float4& r4) {
    /* TODO */
}

Float4& Matrix::operator[](int idx) {
    /* TODO */ NOT_IMPLEMENTED;
}

Float4 Matrix::operator[](int idx) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Matrix Matrix::operator+(const Matrix& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Matrix Matrix::operator-(const Matrix& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Matrix Matrix::transpose() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Matrix Matrix::invert() const {
    /* TODO */ NOT_IMPLEMENTED;
}

bool Matrix::operator==(const Matrix& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

bool Matrix::operator!=(const Matrix& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Matrix product(const Matrix& a, const Matrix& b) {
    /* TODO */ NOT_IMPLEMENTED;
}

Matrix operator*(const Matrix& a, float scalar) {
    /* TODO */ NOT_IMPLEMENTED;
}

Matrix operator*(float scalar, const Matrix& a) {
    /* TODO */ NOT_IMPLEMENTED;
}

Float4 Matrix::operator*(const Float4& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Vector Matrix::operator*(const Vector& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Point Matrix::operator*(const Point& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

float Matrix::det() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Matrix Matrix::zero() {
    /* TODO */ NOT_IMPLEMENTED;
}

Matrix Matrix::identity() {
    /* TODO */ NOT_IMPLEMENTED;
}

Matrix Matrix::system(const Vector& e1, const Vector& e2, const Vector& e3) {
    /* TODO */ NOT_IMPLEMENTED;
}

}