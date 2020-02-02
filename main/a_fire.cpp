
#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>
#include <rt/solids/sphere.h>

#include <rt/cameras/perspective.h>
#include <rt/solids/quad.h>
#include <rt/groups/simplegroup.h>
#include <rt/materials/dummy.h>
#include <rt/materials/lambertian.h>
#include <rt/materials/flatmaterial.h>
#include <rt/materials/phong.h>
#include <rt/textures/constant.h>
#include <rt/lights/pointlight.h>
#include <rt/lights/spotlight.h>
#include <rt/lights/directional.h>
#include <rt/lights/projectivelight.h>

#include <rt/integrators/raytracefire.h>
#include <rt/cameras/dofperspective.h>
#include <rt/volumes/vcone.h>
#include <rt/primmod/vinstance.h>
#include <rt/groups/vsimplegroup.h>
#include <core/interpolate.h>
#include <core/random.h>
#include <rt/solids/cylinder.h>
#include <rt/primmod/instance.h>
#include <rt/solids/infiniteplane.h>
#include <rt/textures/perlin.h>
#include<random>

using namespace rt;

namespace {
std::default_random_engine g;
std::normal_distribution<> d(pi,2);
Vector g1Center = Vector(-1.6, 5.4, -2);
Vector g2Center = Vector(2.2, 4.6, 0);
Vector g3Center = Vector(-3.4, 2, 0);
Vector g4Center = Vector(3, 0, 1);

//Monochrome
RGBColor g1Color = RGBColor(0.886f, 0.345f, 0.133f); //Original flame color
RGBColor g2Color = RGBColor(0.886, 0.282f, 0.133f); 
RGBColor g3Color = RGBColor(0.886, 0.408, 0.133f); 
RGBColor g4Color = RGBColor(0.886f, 0.345f, 0.133f); //original

void makeSparkleFlameGroup(VGroup* vscene, Vector groupOrigin, int p1MaxCount, int p2MaxCount, int p3MaxCount, int q1MaxCount, RGBColor gColor){
    float p1MaxHeight = 3.2f;
    float p1MinHeight = 1.0f;
    float p1MaxRotate = pi/2;
    float p1MinRotate = -pi/2;

    float p2MaxHeight = 2.5f;
    float p2MinHeight = 1.0f;
    float p2MaxRotate = 2 * pi;
    float p2MinRotate = 0.f;

    float q1MaxHeight = 1.0f;
    float q1MinHeight = 0.2f;
    float q1MaxRotate = 2 * pi;
    float q1MinRotate = 0.f;
    
    //float stepSize = 0.005f;
    float minStepSize = 0.002f;
    float maxStepSize = 0.035f;
    float stepSize;
    
    for (int i = 0; i < p1MaxCount; ++i) {
        float p1Height = rt::random(p1MinHeight, p1MaxHeight);
        //float p1Angle = rt::random(p1MinRotate, p1MaxRotate);
        float p1Angle = d(g);
        stepSize = rt::random(minStepSize, maxStepSize);

        VCone *p1Cone = new VCone(0.03f, p1Height, stepSize, gColor);
        VInstance* p1Instance = new VInstance(p1Cone);

        p1Instance->rotate(Vector(0, 0, 1.0f), p1Angle);
        p1Instance->translate(Vector(p1Height * sin(p1Angle), -1 * p1Height * cos(p1Angle), 0.0f));
        p1Instance->translate(groupOrigin);
        vscene->add(p1Instance);

        //Secondary flames
        int q1Count = rt::random(4, q1MaxCount);
        for (int j = 0; j < q1Count; ++j) {        
            float q1Height = rt::random(q1MinHeight, q1MaxHeight);
            float q1Angle = d(g); 
            //float q1Angle = rt::random(q1MinRotate, q1MaxRotate); 
            stepSize = random(minStepSize, maxStepSize);

            VCone *q1Cone = new VCone(0.02f, q1Height, stepSize, gColor);
            VInstance* q1Instance = new VInstance(q1Cone);
            q1Instance->rotate(Vector(0, 0, 1.0f), q1Angle);
            q1Instance->translate(Vector(1 * p1Height * sin(p1Angle), -1 * p1Height * cos(p1Angle), 0.0f));
            q1Instance->translate(groupOrigin);
            vscene->add(q1Instance);
        }
    }
    
    //Primary flames
    for (int i = 0; i < p2MaxCount; ++i) {
        float height = rt::random(p2MinHeight, p2MaxHeight);
        float angle = rt::random(p2MinRotate, p2MaxRotate); 
        //float angle = d(g); 
        stepSize = rt::random(minStepSize, maxStepSize);
        
        VCone *cone = new VCone(0.03f, height, stepSize, gColor);
        VInstance* instance = new VInstance(cone);
        instance->rotate(Vector(0, 0, 1.0f), angle);
        instance->translate(groupOrigin);
        vscene->add(instance);
    } 
    //Primary flames inverted
    for (int i = 0; i < p3MaxCount; ++i) {
        float height = rt::random(p2MinHeight, p2MaxHeight);
        float angle = rt::random(p2MinRotate, p2MaxRotate); 
        //float angle = d(g); 
        stepSize = rt::random(minStepSize, maxStepSize);

        VCone *cone = new VCone(0.03f, height, stepSize, gColor);
        VInstance* instance = new VInstance(cone);
        instance->rotate(Vector(0, 0, 1.0f), angle);
        instance->translate(Vector(height * sin(angle), -1 * height * cos(angle), 0.0f));
        instance->translate(groupOrigin);
        vscene->add(instance);
    }    
    //Flying flames
    
    float transMin = -5, transMax = 5;
    for (int i = 0; i < p3MaxCount; ++i) {
        float height = rt::random(p2MinHeight, p2MaxHeight);
        //float angle = rt::random(p2MinRotate, p2MaxRotate); 
        float angle = d(g); 
        stepSize = rt::random(minStepSize, maxStepSize);

        VCone *cone = new VCone(0.03f, height, stepSize, gColor);
        VInstance* instance = new VInstance(cone);
        instance->rotate(Vector(0, 0, 1.0f), angle);
        instance->translate(Vector(rt::random(transMin, transMax), rt::random(transMin, transMax), rt::random(transMin, transMax)));
        vscene->add(instance);
    }  
}

VGroup* makeSparkleFlames(){

    
    /*HRES*/
   
    int g1p1MaxCount = 8, g1q1MaxCount = 8, g1p2MaxCount = 20, g1p3MaxCount = 3;
    int g2p1MaxCount = 7, g2q1MaxCount = 10, g2p2MaxCount = 15, g2p3MaxCount = 2;
    int g3p1MaxCount = 6, g3q1MaxCount = 9, g3p2MaxCount = 18, g3p3MaxCount = 2;
    int g4p1MaxCount = 6, g4q1MaxCount = 8, g4p2MaxCount = 20, g4p3MaxCount = 2;
   
    /*LRES*/
    /*
    int g1p1MaxCount = 1, g1q1MaxCount = 5, g1p2MaxCount = 5, g1p3MaxCount = 3;
    int g2p1MaxCount = 1, g2q1MaxCount = 4, g2p2MaxCount = 6, g2p3MaxCount = 2;
    int g3p1MaxCount = 1, g3q1MaxCount = 6, g3p2MaxCount = 5, g3p3MaxCount = 3;
    int g4p1MaxCount = 1, g4q1MaxCount = 6, g4p2MaxCount = 5, g4p3MaxCount = 3;
    */

    VGroup* vscene = new VSimpleGroup();
    makeSparkleFlameGroup(vscene, g1Center, g1p1MaxCount, g1p2MaxCount, g1p3MaxCount, g1q1MaxCount, g1Color);  
    makeSparkleFlameGroup(vscene, g2Center, g2p1MaxCount, g2p2MaxCount, g2p3MaxCount, g2q1MaxCount, g2Color);
    makeSparkleFlameGroup(vscene, g3Center, g3p1MaxCount, g3p2MaxCount, g3p3MaxCount, g3q1MaxCount, g3Color);    
    makeSparkleFlameGroup(vscene, g4Center, g4p1MaxCount, g4p2MaxCount, g4p3MaxCount, g4q1MaxCount, g4Color);    
    return vscene;
}

void addStick(Group * scene, Material *material, Vector groupOrigin, float angle, float yMin, float yMax){
    
    float radius = 0.1;//, yMin = -6, yMax = 0.5f;
    Point cOrigin(0, 0, 0);
    Cylinder *cylinderStick1 = new Cylinder(cOrigin, radius, yMin, yMax, nullptr, material);
    Instance *instanceStick1 = new Instance(cylinderStick1);

    instanceStick1->rotate(Vector(0, 0, 1), angle);
    instanceStick1->translate(groupOrigin);
    scene->add(instanceStick1);

    Cylinder *cylinderStick2 = new Cylinder(cOrigin, 0.02, yMin-2, yMin, nullptr, material);
    Instance *instanceStick2 = new Instance(cylinderStick2);
    instanceStick2->rotate(Vector(0, 0, 1), angle);
    instanceStick2->translate(groupOrigin);
    scene->add(instanceStick2);
}
 
World makeSparkleSticks(){
    
    float angleStick1 = pi/40; 
    float angleStick2 = -pi/18; 
    float angleStick3 = pi/10; 
    float angleStick4 = -pi/8;

    World world;
    
    Group* scene = new SimpleGroup();
    Texture *blacktex, *whitetex, *tealtex, *bluetex;
    blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    whitetex = new ConstantTexture(RGBColor::rep(1.0f));
    tealtex = new ConstantTexture(RGBColor(0, 0.04f, 0.04f));
    //bluetex = new ConstantTexture(RGBColor(0, 0.05f, 0.08f));
    Material *lambertianStick = new LambertianMaterial(blacktex, whitetex);
    Material *backwall = new FlatMaterial(tealtex);
   
    addStick(scene, lambertianStick, g1Center, angleStick1, -6, 0.5f);
    addStick(scene, lambertianStick, g2Center, angleStick2, -4, 0.7f);
    addStick(scene, lambertianStick, g3Center, angleStick3, -5, 0.8f);
    addStick(scene, lambertianStick, g4Center, angleStick4, -4, 0.3f);
    
    scene->add(new InfinitePlane(Point(0.0f,0.0f,-3.f), Vector(0.f, 0.1f, 1.0f), nullptr, backwall));
    world.scene = scene;

    RGBColor intensity = 10 * RGBColor(0.886f, 0.345f, 0.133f);
    //world.light.push_back(new PointLight(Point(0, 4, 1), 35 * intensity));
    world.light.push_back(new PointLight(Point(g1Center.x + 1, g1Center.y, g1Center.z + 1.6), 10 * g1Color));
    world.light.push_back(new PointLight(Point(g2Center.x - 1, g2Center.y, g2Center.z + 1.6), 10 * g2Color));
    world.light.push_back(new PointLight(Point(g3Center.x + 1, g3Center.y, g3Center.z + 1.6), 10 * g3Color));
    world.light.push_back(new PointLight(Point(g4Center.x - 1, g4Center.y, g4Center.z + 1.6), 10 * g4Color));
    return world;
}

void renderFireworks(const char* filename, int imgRes, int numSamples=1) {

    Image img(imgRes, imgRes);
    
    World world = makeSparkleSticks();

    VGroup *vscene = makeSparkleFlames();
    
    RayTraceFireIntegrator integrator(&world, vscene);

    PerspectiveCamera cam(Point(0, 1.7, 10), Vector(0, 0, -1), Vector(0, 1, 0), pi/3, pi/3);
    //PerspectiveCamera cam(Point(0, 2.5, 10), Vector(0, 0, -1), Vector(0, 1, 0), pi/3, pi/3);
    //PerspectiveCamera cam(Point(1, 1.7, 8), Vector(0, 0, -1), Vector(0, 1, 0), pi/3, pi/3);
    //DOFPerspectiveCamera cam(Point(0, 1.7, 10), Vector(0, 0, -1), Vector(0, 1, 0), pi/3, pi/3, 7.0f, 0.025f);
    
    Renderer engine(&cam, &integrator);
     if (numSamples>1)
        engine.setSamples(numSamples);
    engine.render(img);
    img.writePNG(filename);

}
}


void a_fire() {
    /*HRES*/
    /*LRES*/
    //renderFireworks("a9-1-hres-1920-20.png", 20);
    renderFireworks("a9-1-1080-20.png", 1080, 20);
    //renderFireworks("a9-1080-.png", 1080, 20);
}