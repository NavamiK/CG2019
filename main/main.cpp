void a_julia();
void a_cameras();
void a_solids();
void a_indexing();
void a_instancing();
void a_lighting();
void a_materials();
void a_textures();
void a_local();
void a_mappers();
void a_distributed();
void a_smooth();
void a_bumpmappers();

#include <stdexcept>
#include <iostream>
#include <core/assert.h>
#include <core/vector.h>
using namespace rt;

int main(int argc, char* argv[])
{
    //a_julia();
    //a_cameras();
    
    Vector v1(2.0f, -1.2f, 4.5f);
    std::cout << "v1: "; 
    v1.print();

    Vector v2(-2.3f, 0.0f, 1.9f);
    std::cout << "v2: ";
    v2.print();

    Vector sum = v1 + v2; 
    std::cout<<"Sum: ";
    sum.print();

    Vector diff = v1 - v2; 
    std::cout<<"Diff: ";
    diff.print();

    Vector neg = -v1; 
    std::cout<<"Neg: ";
    neg.print();
    
    Vector v1_normal = v1.normalize(); 
    std::cout<<"v1 normalized: ";
    v1_normal.print();

    std::cout<<"v1 length square: "<< v1.lensqr()<< std::endl;

    std::cout<<"v1 length: "<<v1.length()<<std::endl;

    float scalar = 3.2f;
    Vector scaled1v1 = scalar * v1; 
    std::cout<<"v1 scaled on left: ";
    scaled1v1.print();

    Vector scaled2v1 = v1 * scalar; 
    std::cout<<"v1 scaled on right: ";
    scaled2v1.print();
    
    Vector scaled3v1 = v1 / scalar; 
    std::cout<<"v1 scaled down: ";
    scaled3v1.print();

    Vector cross_prod = cross(v1, v2); 
    std::cout<<"cross product of v1 and v2: ";
    cross_prod.print();

    std::cout<<"dot product of v1 and v2: "<< dot(v1, v2) <<std::endl;

    return 0;
}