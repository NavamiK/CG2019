#include <rt/groups/bvh.h>
#include <stack>
namespace rt {

BVH::BVH()
{
    tree = new BVHNode();
}

BVH::~BVH() {
    delete tree;
}

void BVH::rebuildIndex() {
    this->tree = recursiveBuild(0, primitives.size());
}

BVH::BVHNode* BVH::recursiveBuild(int start, int end){
    BVHNode *node = new BVHNode();
    //1. compute bounds of all primitives.
    BBox maxBound;
    //Primitives nodePrimitives;
    for(int i = start; i < end; i++){
        maxBound.extend(primitives[i]->getBounds());
        node->nodePrimitives.push_back(primitives[i]);
    }

    if(node->nodePrimitives.size() < 3){
        // create leave node and stop.
        node->initLeafNode(maxBound);
        return node;
    }
    else{
        int splitAxis = maxBound.maxExtent();
        //float dimScalar = (maxBound.max.at(splitAxis) + maxBound.min.at(splitAxis)) / 2.f;
        Point splitAxisPoint = maxBound.axisPoint(splitAxis);
        int mid = (start + end) / 2;
        // build child nodes and increase the node bounds to include the point.
        BVHNode *left = recursiveBuild(start, mid);
        left->bounds.extend(splitAxisPoint);
        BVHNode *right = recursiveBuild(mid, end);
        right->bounds.extend(splitAxisPoint);

        node->initInternalNode(left, right);
        return node;
    }
}

BBox BVH::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection BVH::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */ 
  
    Intersection currentIntersection;
    Intersection nearestIntersection = Intersection::failure();

    BVHNode* currentNode = new BVHNode();
    std::stack<BVHNode*> pendingNodesStack;

    //Need to traverse entire tree for intersection
    pendingNodesStack.push(tree);

    while(!pendingNodesStack.empty()){
        currentNode = pendingNodesStack.top(); //Fetch the topmost/next node
        pendingNodesStack.pop(); //Remove the topmost/next node from the list
        if(currentNode->isLeaf){ 
            for(auto primitive: currentNode->nodePrimitives){
                currentIntersection = primitive->intersect(ray, previousBestDistance);
                if(currentIntersection.distance < previousBestDistance){
                    previousBestDistance = currentIntersection.distance;
                    nearestIntersection = currentIntersection;
                }
            }
        }else{
            BBox leftBbox = currentNode->leftChild->bounds;
            auto[entryLeft, exitLeft] = leftBbox.intersect(ray);
            if(entryLeft < exitLeft)
                pendingNodesStack.push(currentNode->leftChild);

            
            BBox rightBbox = currentNode->rightChild->bounds;
            auto[entryRight, exitRight] = rightBbox.intersect(ray);
            if(entryRight < exitRight)
                pendingNodesStack.push(currentNode->rightChild);            
        }
    }
    return nearestIntersection;
}

void BVH::add(Primitive* p) {
    primitives.push_back(p);
}

void BVH::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void BVH::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

}