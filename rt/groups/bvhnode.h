#ifndef BVHNODE_H
#define BVHNODE_H

#include <rt/bbox.h>
#include <iostream>
#include <rt/primitive.h>
namespace rt {

class  BVHNode
{
public:
    BVHNode(){}

    BBox boundingBox ;
    bool isLeaf;
    BVHNode * leftChild;
    BVHNode * rightChild;

    void extend(const BBox & newBox){
        boundingBox.extend(newBox);
    }					//append bbox to existing bbox or empty node

    typedef std::vector<Primitive*> Primitives;
    Primitives primitives;

};

}

#endif