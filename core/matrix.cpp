#include <core/matrix.h>
#include <core/assert.h>

#include <core/vector.h>
#include <core/point.h>

namespace rt {

Matrix::Matrix(const Float4& r1, const Float4& r2, const Float4& r3, const Float4& r4) {
    /* TODO */
    row1 = r1;
    row2 = r2;
    row3 = r3;
    row4 = r4;
}

Float4& Matrix::operator[](int idx) {
    /* TODO */
    assert(idx >= 0 && idx <=3);

    switch(idx){
        case 0:
            return row1;
        case 1:
            return row2;
        case 2:
            return row3;
        default:
            return row4;
    }
}

Float4 Matrix::operator[](int idx) const {
    /* TODO */
    assert(idx >= 0 && idx <=3);

    switch(idx){
        case 0:
            return row1; //(Float4(row1[0], row1[1], row1[2], row1[3]));
        case 1:
            return row2;//(Float4(row2[0], row2[1], row2[2], row2[3]));;
        case 2:
            return row3; //(Float4(row3[0], row3[1], row3[2], row3[3]));;
        default:
            return row4; //(Float4(row4[0], row4[1], row4[2], row4[3]));;
    }

}

Matrix Matrix::operator+(const Matrix& b) const {
    /* TODO */
    Float4 r1 = row1 + b[0];
    Float4 r2 = row2 + b[1];
    Float4 r3 = row3 + b[2];
    Float4 r4 = row4 + b[3];
    return (Matrix(r1, r2, r3, r4));
}

Matrix Matrix::operator-(const Matrix& b) const {
    /* TODO */
    Float4 r1 = row1 - b[0];
    Float4 r2 = row2 - b[1];
    Float4 r3 = row3 - b[2];
    Float4 r4 = row4 - b[3];
    return (Matrix(r1, r2, r3, r4));
}

Matrix Matrix::transpose() const {
    /* TODO */
    Float4 r1 = Float4(row1[0], row2[0], row3[0], row4[0]);
    Float4 r2 = Float4(row1[1], row2[1], row3[1], row4[1]);
    Float4 r3 = Float4(row1[2], row2[2], row3[2], row4[2]);
    Float4 r4 = Float4(row1[3], row2[3], row3[3], row4[3]);
    return (Matrix(r1, r2, r3, r4));
}

Matrix Matrix::invert() const {
    Matrix result;
    const Matrix& m = *this;

    // Taken and modified from http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
    result[0][0] =  m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2] + m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];
    result[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] + m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] - m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];
    result[2][0] =  m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] + m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];
    result[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] + m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] - m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

    float det = m[0][0] * result[0][0] + m[0][1] * result[1][0] + m[0][2] * result[2][0] + m[0][3] * result[3][0];
    if (det == 0)
        return Matrix::zero();

    result[0][1] = -m[0][1] * m[2][2] * m[3][3] + m[0][1] * m[2][3] * m[3][2] + m[2][1] * m[0][2] * m[3][3] - m[2][1] * m[0][3] * m[3][2] - m[3][1] * m[0][2] * m[2][3] + m[3][1] * m[0][3] * m[2][2];
    result[1][1] =  m[0][0] * m[2][2] * m[3][3] - m[0][0] * m[2][3] * m[3][2] - m[2][0] * m[0][2] * m[3][3] + m[2][0] * m[0][3] * m[3][2] + m[3][0] * m[0][2] * m[2][3] - m[3][0] * m[0][3] * m[2][2];
    result[2][1] = -m[0][0] * m[2][1] * m[3][3] + m[0][0] * m[2][3] * m[3][1] + m[2][0] * m[0][1] * m[3][3] - m[2][0] * m[0][3] * m[3][1] - m[3][0] * m[0][1] * m[2][3] + m[3][0] * m[0][3] * m[2][1];
    result[3][1] =  m[0][0] * m[2][1] * m[3][2] - m[0][0] * m[2][2] * m[3][1] - m[2][0] * m[0][1] * m[3][2] + m[2][0] * m[0][2] * m[3][1] + m[3][0] * m[0][1] * m[2][2] - m[3][0] * m[0][2] * m[2][1];
    result[0][2] =  m[0][1] * m[1][2] * m[3][3] - m[0][1] * m[1][3] * m[3][2] - m[1][1] * m[0][2] * m[3][3] + m[1][1] * m[0][3] * m[3][2] + m[3][1] * m[0][2] * m[1][3] - m[3][1] * m[0][3] * m[1][2];
    result[1][2] = -m[0][0] * m[1][2] * m[3][3] + m[0][0] * m[1][3] * m[3][2] + m[1][0] * m[0][2] * m[3][3] - m[1][0] * m[0][3] * m[3][2] - m[3][0] * m[0][2] * m[1][3] + m[3][0] * m[0][3] * m[1][2];
    result[2][2] =  m[0][0] * m[1][1] * m[3][3] - m[0][0] * m[1][3] * m[3][1] - m[1][0] * m[0][1] * m[3][3] + m[1][0] * m[0][3] * m[3][1] + m[3][0] * m[0][1] * m[1][3] - m[3][0] * m[0][3] * m[1][1];
    result[3][2] = -m[0][0] * m[1][1] * m[3][2] + m[0][0] * m[1][2] * m[3][1] + m[1][0] * m[0][1] * m[3][2] - m[1][0] * m[0][2] * m[3][1] - m[3][0] * m[0][1] * m[1][2] + m[3][0] * m[0][2] * m[1][1];
    result[0][3] = -m[0][1] * m[1][2] * m[2][3] + m[0][1] * m[1][3] * m[2][2] + m[1][1] * m[0][2] * m[2][3] - m[1][1] * m[0][3] * m[2][2] - m[2][1] * m[0][2] * m[1][3] + m[2][1] * m[0][3] * m[1][2];
    result[1][3] =  m[0][0] * m[1][2] * m[2][3] - m[0][0] * m[1][3] * m[2][2] - m[1][0] * m[0][2] * m[2][3] + m[1][0] * m[0][3] * m[2][2] + m[2][0] * m[0][2] * m[1][3] - m[2][0] * m[0][3] * m[1][2];
    result[2][3] = -m[0][0] * m[1][1] * m[2][3] + m[0][0] * m[1][3] * m[2][1] + m[1][0] * m[0][1] * m[2][3] - m[1][0] * m[0][3] * m[2][1] - m[2][0] * m[0][1] * m[1][3] + m[2][0] * m[0][3] * m[1][1];
    result[3][3] =  m[0][0] * m[1][1] * m[2][2] - m[0][0] * m[1][2] * m[2][1] - m[1][0] * m[0][1] * m[2][2] + m[1][0] * m[0][2] * m[2][1] + m[2][0] * m[0][1] * m[1][2] - m[2][0] * m[0][2] * m[1][1];

    result = result*(1.0f/det);
    return result;
}

bool Matrix::operator==(const Matrix& b) const {
    /* TODO */
    const Matrix m = *this;
    for(int r = 0; r < 4; r++){
        for(int c = 0; c < 4; c++){
            if(m[r][c] != b[r][c]){
                return false;
            }
        }
    }

    return true;
}

bool Matrix::operator!=(const Matrix& b) const {
    /* TODO */
    const Matrix m = *this;
    for(int r = 0; r < 4; r++){
        for(int c = 0; c < 4; c++){
            if(m[r][c] != b[r][c]){
                return false;
            }
        }
    }

    return true;
}

Matrix product(const Matrix& a, const Matrix& b) {
    /* TODO */
    float r00 = a[0][0]*b[0][0] + a[0][1]*b[1][0] + a[0][2]*b[2][0] + a[0][3]*b[3][0];
    float r01 = a[0][0]*b[0][1] + a[0][1]*b[1][1] + a[0][2]*b[2][1] + a[0][3]*b[3][1];
    float r02 = a[0][0]*b[0][2] + a[0][1]*b[1][2] + a[0][2]*b[2][2] + a[0][3]*b[3][2];
    float r03 = a[0][0]*b[0][3] + a[0][1]*b[1][3] + a[0][2]*b[2][3] + a[0][3]*b[3][3];
    Float4 r1(r00, r01, r02, r03);

    float r10 = a[1][0]*b[0][0] + a[1][1]*b[1][0] + a[1][2]*b[2][0] + a[1][3]*b[3][0];
    float r11 = a[1][0]*b[0][1] + a[1][1]*b[1][1] + a[0][2]*b[2][1] + a[0][3]*b[3][1];
    float r12 = a[1][0]*b[0][2] + a[1][1]*b[1][2] + a[0][2]*b[2][2] + a[0][3]*b[3][2];
    float r13 = a[1][0]*b[0][3] + a[1][1]*b[1][3] + a[0][2]*b[2][3] + a[0][3]*b[3][3];
    Float4 r2(r10, r11, r12, r13);

    float r20 = a[2][0]*b[0][0] + a[2][1]*b[1][0] + a[2][2]*b[2][0] + a[2][3]*b[3][0];
    float r21 = a[2][0]*b[0][1] + a[2][1]*b[1][1] + a[2][2]*b[2][1] + a[2][3]*b[3][1];
    float r22 = a[2][0]*b[0][2] + a[2][1]*b[1][2] + a[2][2]*b[2][2] + a[2][3]*b[3][2];
    float r23 = a[2][0]*b[0][3] + a[2][1]*b[1][3] + a[2][2]*b[2][3] + a[2][3]*b[3][3];
    Float4 r3(r20, r21, r22, r23);

    float r30 = a[3][0]*b[0][0] + a[3][1]*b[1][0] + a[3][2]*b[2][0] + a[3][3]*b[3][0];
    float r31 = a[3][0]*b[0][1] + a[3][1]*b[1][1] + a[3][2]*b[2][1] + a[3][3]*b[3][1];
    float r32 = a[3][0]*b[0][2] + a[3][1]*b[1][2] + a[3][2]*b[2][2] + a[3][3]*b[3][2];
    float r33 = a[3][0]*b[0][3] + a[3][1]*b[1][3] + a[3][2]*b[2][3] + a[3][3]*b[3][3];
    Float4 r4(r30, r31, r32, r33);

    return (Matrix(r1, r2, r3, r4));
}

Matrix operator*(const Matrix& a, float scalar) {
    /* TODO */
    Float4 r1 = scalar * a[0];
    Float4 r2 = scalar * a[1];
    Float4 r3 = scalar * a[2];
    Float4 r4 = scalar * a[3];
    return (Matrix(r1, r2, r3, r4));
}

Matrix operator*(float scalar, const Matrix& a) {
    /* TODO */
    Float4 r1 = scalar * a[0];
    Float4 r2 = scalar * a[1];
    Float4 r3 = scalar * a[2];
    Float4 r4 = scalar * a[3];
    return (Matrix(r1, r2, r3, r4));
}

Float4 Matrix::operator*(const Float4& b) const {
    /* TODO */
    float f1 = row1[0]*b[0] + row1[1]*b[1] + row1[2]*b[2] + row1[3]*b[3];
    float f2 = row2[0]*b[0] + row2[1]*b[1] + row2[2]*b[2] + row2[3]*b[3];
    float f3 = row3[0]*b[0] + row3[1]*b[1] + row3[2]*b[2] + row3[3]*b[3];
    float f4 = row4[0]*b[0] + row4[1]*b[1] + row4[2]*b[2] + row4[3]*b[3];
    return (Float4(f1, f2, f3, f4));
}

Vector Matrix::operator*(const Vector& b) const {
    /* TODO */
    // make it homogenious cords.
    float f1 = row1[0]*b.x + row1[1]*b.y + row1[2]*b.z + row1[3];
    float f2 = row2[0]*b.x + row2[1]*b.y + row2[2]*b.z + row2[3];
    float f3 = row3[0]*b.x + row3[1]*b.y + row3[2]*b.z + row3[3];
    float f4 = row4[0]*b.x + row4[1]*b.y + row4[2]*b.z + row4[3];
    return (Vector(f1/f4, f2/f4, f3/f4)); // normalize cords.
}

Point Matrix::operator*(const Point& b) const {
    /* TODO */
    // make it homogenious cords.
    float p1 = row1[0]*b.x + row1[1]*b.y + row1[2]*b.z + row1[3];
    float p2 = row2[0]*b.x + row2[1]*b.y + row2[2]*b.z + row2[3];
    float p3 = row3[0]*b.x + row3[1]*b.y + row3[2]*b.z + row3[3];
    float p4 = row4[0]*b.x + row4[1]*b.y + row4[2]*b.z + row4[3];
    return (Point (p1/p4, p2/p4, p3/p4)); // normalize cords.
}

float Matrix::det() const {
    /* TODO */
    Matrix result;
    const Matrix& m = *this;
    //copied from the inverse function above.
    result[0][0] =  m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2] + m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];
    result[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] + m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] - m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];
    result[2][0] =  m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] + m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];
    result[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] + m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] - m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

    float det = m[0][0] * result[0][0] + m[0][1] * result[1][0] + m[0][2] * result[2][0] + m[0][3] * result[3][0];
    return det;
}

Matrix Matrix::zero() {
    /* TODO */
    Float4 f = Float4::rep(0.f);
    return (Matrix(f, f, f, f));
}

Matrix Matrix::identity() {
    /* TODO */
    Float4 r1(1.f, 0.f, 0.f, 0.f);
    Float4 r2(0.f, 1.f, 0.f, 0.f);
    Float4 r3(0.f, 0.f, 1.f, 0.f);
    Float4 r4(0.f, 0.f, 0.f, 1.f);
    return (Matrix(r1, r2, r3, r4));
}

Matrix Matrix::system(const Vector& e1, const Vector& e2, const Vector& e3) {
    /* TODO */
    //TODO: test (debug.)
    //basis vectors.
    Vector b1(1.f, 0.f, 0.f);
    Vector b2(0.f, 1.f, 0.f);
    Vector b3(0.f, 0.f, 1.f);

    Vector col1 = rowReduce(e1, e2, e3, b1);
    Vector col2 = rowReduce(e1, e2, e3, b2);
    Vector col3 = rowReduce(e1, e2, e3, b3);

    //rows..
    Float4 r1(col1.x, col2.x, col3.x, 0);
    Float4 r2(col1.y, col2.y, col3.y, 0);
    Float4 r3(col1.z, col2.z, col3.z, 0);
    Float4 r4(0     ,0      ,0      , 1);

    return (Matrix(r1, r2, r3, r4));
}

//taken and modified from:
//https://stackoverflow.com/questions/31756413/solving-a-simple-matrix-in-row-reduced-form-in-c
Vector Matrix::rowReduce (const Vector& e1, const Vector& e2, const Vector& e3, Vector basis){
        float A[3][4] = {
        e1.x,e1.x,e3.x,basis.x,
        e1.y,e2.y,e3.y,basis.y,
        e1.z, e2.z,e3.z,basis.z,
    };

    const int nrows = 3; // number of rows
    const int ncols = 4; // number of columns

    int lead = 0;

    while (lead < nrows) {
        float d, m;

        for (int r = 0; r < nrows; r++) { // for each row ...
            /* calculate divisor and multiplier */
            d = A[lead][lead];
            m = A[r][lead] / A[lead][lead];

            for (int c = 0; c < ncols; c++) { // for each column ...
                if (r == lead)
                    A[r][c] /= d;               // make pivot = 1
                else
                    A[r][c] -= A[lead][c] * m;  // make other = 0
            }
        }

        lead++;
    }

    return (Vector(A[0][3], A[1][3], A[2][3]));// verify that this is the last col.
}

}