#include <rt/groups/bvh.h>
#include <rt/solids/solid.h>
#include <rt/groups/bvhnode.h>

#include <stdio.h>

namespace rt
{

BVH::BVH()
{
    root = new BVHNode();
}

BVH::~BVH()
{
    delete(root);
}

BBox BVH::getBounds() const
{
      /* TODO */ NOT_IMPLEMENTED;
}

void BVH::rebuildIndex()
{
    root->primitives = primitives;
    buildTree(root);
    return;
}

void BVH::buildTree(BVHNode *node) 
{
    float splitAxisLen;
    Primitive *primitive;
    
    int start = 0;  
    int nPrimitives = node->primitives.size(); 
    int end = nPrimitives - 1;

    if (nPrimitives <= 0)
        return;
    
    node->boundingBox = BBox::empty();

    for (int i = start; i <= end; i++)
        node->extend(node->primitives[i]->getBounds());

    if (nPrimitives < 3)
    {
        node->isLeaf = true;
        return;
    }

    if (nPrimitives >= 3)
    {
        node->isLeaf = false;
        node->leftChild = new BVHNode();
        node->rightChild = new BVHNode();
       
        int splitAxisIndex = node->boundingBox.findBBoxSplitAxis();

        splitAxisLen = node->boundingBox.getBBoxCentroid().getCoordinate(splitAxisIndex);

        if (this->isSAH) 
        {
            float costL = 0, costR = 0, costBest = FLT_MAX, cost, kLen;
            for (int k = 1; k < 10; k++)
            {
                kLen = node->boundingBox.min.getCoordinate(splitAxisIndex) + k * (node->boundingBox.max.getCoordinate(splitAxisIndex) - node->boundingBox.min.getCoordinate(splitAxisIndex)) / 10;
                for (auto j : node->primitives)
                {
                    Solid *solid = dynamic_cast<Solid *>(j);
                    if (j->getBounds().getBBoxCentroid().getCoordinate(splitAxisIndex) < kLen) //assuming x is the longest dimension
                        costL = costL + solid->getArea();
                    else
                        costR = costR + solid->getArea();
                    cost = costL * (kLen - node->boundingBox.min.getCoordinate(splitAxisIndex)) + costR * (node->boundingBox.max.getCoordinate(splitAxisIndex) - kLen);
                }
                if (cost < costBest)
                {
                    costBest = cost;
                    splitAxisLen = kLen;
                }
            }
        }

        // Core logic - if centroid of primitive's BBox smaller than falls on the left of world BBox's centroid,  
        // add to left subtree, else add to right
        for (int i = start; i <= end; i++)
        {
            primitive = node->primitives[i];
            if (primitive->getBounds().getBBoxCentroid().getCoordinate(splitAxisIndex) <= splitAxisLen)
                node->leftChild->primitives.push_back(primitive);
            else
                node->rightChild->primitives.push_back(primitive);               
        }

        // If split causes all children to fall on one side of the tree, tree contruction algo will not terminate 
        //--> segmentation fault
        //Solution 1 - Move one node from the populated side to the empty one
        /*if (node->leftChild->primitives.size() == 0)
        {

            node->leftChild->primitives.push_back(node->rightChild->primitives[0]);
            node->rightChild->primitives.erase(node->rightChild->primitives.begin());
        }

        else if (node->rightChild->primitives.size() == 0)
        {
            node->rightChild->primitives.push_back(node->leftChild->primitives[0]);
            node->leftChild->primitives.erase(node->leftChild->primitives.begin());
        }
        
        //Solution 2 - mark as leaves and terminate
        /*
        if ((node->leftChild->primitives.size() == 0) || (node->rightChild->primitives.size() == 0)){
            node->leftChild->isLeaf = true;
            node->rightChild->isLeaf = true;
            return;
        }
        */

        buildTree(node->leftChild);
        buildTree(node->rightChild);
        return;
    }
}

Intersection BVH::intersect(const Ray &ray, float previousBestDistance) const
{
    BVHNode *node = new BVHNode();
    Intersection nearestIntersection = Intersection::failure();
    Intersection currentIntersection;
    std::vector<BVHNode *> nodes;
    nodes.push_back(this->root);

    while (!nodes.empty())
    {
        node = nodes.back();
        nodes.pop_back();

        if (node->isLeaf)
        {
            for (auto prim : node->primitives)
            {
                currentIntersection = prim->intersect(ray, previousBestDistance);
                if (currentIntersection)
                {
                    previousBestDistance = currentIntersection.distance;
                    nearestIntersection = currentIntersection;
                }
            }
        }
        else
        {
            BBox leftBbox = node->leftChild->boundingBox;
            auto[entryLeft, exitLeft] = leftBbox.intersect(ray);
            if(entryLeft < exitLeft)
                nodes.push_back(node->leftChild);
            
            BBox rightBbox = node->rightChild->boundingBox;
            auto[entryRight, exitRight] = rightBbox.intersect(ray);
            if(entryRight < exitRight)
                nodes.push_back(node->rightChild);  
        }
    }
    return nearestIntersection;
}


void BVH::add(Primitive *p)
{
    primitives.push_back(p);
}

void BVH::setMaterial(Material *m)
{
    /* TODO */ NOT_IMPLEMENTED;
}

void BVH::setCoordMapper(CoordMapper *cm)
{
    /* TODO */ NOT_IMPLEMENTED;
}

} 