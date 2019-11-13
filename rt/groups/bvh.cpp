#include <rt/groups/bvh.h>
#include <stack>
namespace rt {

BVH::BVH(){
    /* TODO */
    tree = new BVHNode();
}

BVH::~BVH() {
    /* TODO */
    delete tree;
}

void BVH::rebuildIndex() {
    tree->nodePrimitives = primitives;
    recursiveBuild(tree);
}

void BVH::recursiveBuild(BVHNode * node){
    //1. compute bounds of all primitives.
    BBox maxBound = BBox::empty();
    int start = 0; 
    int numPrim = node->nodePrimitives.size();
    int end = numPrim -1;

    for(int i = start; i <= end; i++){
        maxBound.extend(node->nodePrimitives[i]->getBounds());
        //node->nodePrimitives.push_back(primitives[i]);
    }
    if(numPrim <= 0)
        return;
    if(numPrim < 3){
        // create leave node and stop.
        node->initLeafNode(maxBound);
        return;
    }
    else if(numPrim >=3){
        node->initInternalNode(maxBound);
        int splitAxis = maxBound.maxExtent();
        //float dimScalar = (maxBound.max.at(splitAxis) + maxBound.min.at(splitAxis)) / 2.f;
        float dimScalar = maxBound.getCentroid().at(splitAxis);
        //Point splitAxisPoint = maxBound.axisPoint(splitAxis, dimScalar);
        //int mid = (start + end) / 2;
        for (int i = start; i <= end; i++){
                Primitive *currentPrim = node->nodePrimitives[i];
                if (currentPrim->getBounds().getCentroid().at(splitAxis) < dimScalar){
                    node->leftChild->nodePrimitives.push_back(currentPrim);

                    // Handling the case when BBox of primitive coincides with centroid
                     if(std::abs(currentPrim->getBounds().max.at(splitAxis) - currentPrim->getBounds().min.at(splitAxis)) 
                     == std::abs(node->bounds.max.at(splitAxis) - node->bounds.min.at(splitAxis)))
                        
                        std::swap(node->leftChild->nodePrimitives.front(), node->leftChild->nodePrimitives.back());
                }                                        
                else{
                    node->rightChild->nodePrimitives.push_back(currentPrim);
                     // Handling the case when BBox of primitive coincides with centroid
                    if(std::abs(currentPrim->getBounds().max.at(splitAxis) - currentPrim->getBounds().min.at(splitAxis)) 
                     == std::abs(node->bounds.max.at(splitAxis) - node->bounds.min.at(splitAxis)))
                        
                        std::swap(node->rightChild->nodePrimitives.front(), node->rightChild->nodePrimitives.back());
                }
            }
        /* Boundary case */
        if (node->leftChild->nodePrimitives.size() == 0){
            node->leftChild->nodePrimitives.push_back(node->rightChild->nodePrimitives[0]);
            node->rightChild->nodePrimitives.erase(node->rightChild->nodePrimitives.begin());
        }
        else if(node->rightChild->nodePrimitives.size() == 0){
            node->rightChild->nodePrimitives.push_back(node->leftChild->nodePrimitives[0]);
            node->leftChild->nodePrimitives.erase(node->leftChild->nodePrimitives.begin());
        }
        recursiveBuild(node->leftChild);
        recursiveBuild(node->rightChild);
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