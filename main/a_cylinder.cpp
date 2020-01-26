<<<<<<< HEAD

=======
>>>>>>> navami
#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/groups/simplegroup.h>
#include <rt/solids/sphere.h>
#include <rt/solids/infiniteplane.h>
#include <rt/solids/triangle.h>
#include <rt/solids/quad.h>
#include <rt/solids/disc.h>
#include <rt/solids/aabox.h>
#include <rt/cameras/perspective.h>
#include <rt/integrators/casting.h>
#include <rt/integrators/castingdist.h>
#include <rt/renderer.h>
#include <rt/solids/cylinder.h>
#include <rt/lights/pointlight.h>
#include <rt/integrators/recraytrace.h>

#include <rt/materials/lambertian.h>
#include <rt/textures/constant.h>
#include <rt/integrators/raytrace.h>
#include <rt/materials/phong.h>
#include <rt/materials/mirror.h>
#include <rt/lights/arealight.h>

using namespace rt;

void a_cylinder() {
    Image img(640, 480);

    World world;

    SimpleGroup* scene = new SimpleGroup();
    float scale = 0.001f;
    //ceiling
    //scene->add(new Quad(Point(550.f, 550.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, Vector(-550.f, 000.f, 000.f)*scale, nullptr, nullptr));


    ///////////////////////////////textures..
    Texture *redtex, *greentex, *bluetex, *blacktex, *whitetex;
    //redtex = new ConstantTexture(RGBColor(.7f,0.f,0.f));
    greentex = new ConstantTexture(RGBColor(0.f,.7f,0.f));
    //bluetex = new ConstantTexture(RGBColor(0.f,0.f,0.7f));
    blacktex = new ConstantTexture(RGBColor::rep(0.0f));
    whitetex = new ConstantTexture(RGBColor::rep(1.0f));

    Material *phong, *mirror, *lambertian;

    //phong = new PhongMaterial(whitetex, 10.0f);
    //mirror = new MirrorMaterial(0.0f, 0.0f);
    //lambertian = new LambertianMaterial(blacktex, greentex);
    lambertian = new LambertianMaterial(blacktex, whitetex);
    ////////////////////////////////textures...
    float radius = 0.1, yMin = -3, yMax = 0.f;
    Point cOrigin(0, 0, 0);
    scene->add(new Cylinder(cOrigin, radius, yMin, yMax, nullptr, lambertian));
    //scene->add(new Cylinder(cOrigin + Point(1.f, 0, 0), radius, yMin, yMax, nullptr, lambertian));
    Point center(-.5f, 1.f, 5);
//    scene->add(new Sphere(center, radius, nullptr, lambertian));
//    world.light.push_back(new AreaLight(new Quad(center, Vector(1.f, 0, 0), Vector(0, 0, 1.f), nullptr, nullptr)));
    //////////////////////////////

    world.scene = scene;
    PerspectiveCamera cam(Point(0, 0, 10), Vector(0, 0, -1), Vector(0, 1, 0), pi/4, pi/3);

    ///////////////////////////////////light source
    //add another light source.
    //RGBColor intensity = RGBColor(15.0f, 10, 10);
    RGBColor intensity = RGBColor(0.886f, 0.345f, 0.133f);
    world.light.push_back(new PointLight(Point(2, 0, 1),4 * intensity));
    //world.light.push_back(new PointLight(Point(-1, 0, 1), intensity));
    
    scale = 1;
    //world.light.push_back(new PointLight(Point(288*scale,529.99f*scale,279.5f*scale),RGBColor::rep(40000.0f*scale*scale)));
    //world.light.push_back(new PointLight(Point(490*scale,329.99f*scale,279.5f*scale),RGBColor(60000.0f*scale*scale,0,0)));
    //world.light.push_back(new PointLight(Point(40*scale,329.99f*scale,279.5f*scale),RGBColor(0,60000.0f*scale*scale,0)));

    ConstantTexture* lightsrctex = new ConstantTexture(RGBColor::rep(35.0f));
    Material* lightsource = new LambertianMaterial(lightsrctex, blacktex);

    //Point lightCenter(1, 0, -2);
    Quad* light = new Quad(center, Vector(1,0,0), Vector(0,0,1), nullptr, lightsource);
    //Quad* light2 = new Quad(lightCenter, Vector(0,2,0), Vector(0,0,2), nullptr, lightsource);

    //AreaLight areaLight(light2);
    AreaLight als(light);

    //world.light.push_back(&als);
    //world.light.push_back(&areaLight);
    scene->add(light);
    //scene->add(light2);
    /////////////////////////////////////////////////////////////////

    //RecursiveRayTracingIntegrator integratorc(&world);
    RayTracingIntegrator integratorc(&world);
    Renderer enginec(&cam, &integratorc);
    enginec.render(img);
    img.writePNG("a_cylinder_light.png");
}
