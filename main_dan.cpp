#include <iostream>
#include "world/world.h"
#include "aux/colour.h"
#include "world/object.h"
#include "world/sphere.h"
#include "world/triangle.h"
#include "world/camera.h"

int main() {
 // Colour bgColour(0,0.7,0.7);
  Colour bgColour(1,1,1);
  World w(bgColour);
  
 // Object* o1 = new Sphere(1., Point(-4.5, 4.45, -3.05));
//Object* o1 = new Sphere(0.81, Point(17.89, 10.51, -5.65));
  Object* o1 = new Sphere(10, Point(0, 0, 150));
  o1->setColour(Colour(1.,0.,0.));

  Object* o2 = new Sphere(10, Point(25, 10, 250));
  o2->setColour(Colour(0.,1.,0.));

  Object* o3 = new Sphere(2, Point(0, 10, 0));
  o3->setColour(Colour(1.,0.,0.));


  //Point topLeft(-2, 2, -2000);//6., -2., 0.);
  //Point topRight(2,2,-2000);//6., 2., 0.);
  //Point botLeft(-2,-2,-2000);//,4., 2., 0.);
  //Point botRight(2,-2,-2000);//4., -2., 0.);
  
// TESTING
  Point topLeft(-16, 5, 200);//6., -2., 0.);
  Point topRight(16,5, 200);//6., 2., 0.);
  Point botLeft(-16,0, 200);//,4., 2., 0.);
  Point botRight(16,0, 200);//,4., 2., 0.);
  Object* t1 = new Triangle(topLeft, topRight, botLeft);

  //Object* t1 = new Triangle(topLeft, topRight, botLeft);
  Object* t2 = new Triangle(topRight, botRight, botLeft);
  
  t1->setColour(Colour(0.,0.,1.));
  t2->setColour(Colour(0.,0.,1.));

  w.add(t1);
  w.add(t2);
  w.add(o1);
  w.add(o2);
  w.add(o3);
  //w.add(o2);

  //Point camPos(-6.01, 13.44, -2.59);
  //Point camPos(-1.8, 2.33, -10.32);
  Point camPos(0, 0, 0);
  //Point look(-4.5,4.45,-3.05);
  Point look(0, 0, 5);
  //Point look(0.,0.,0.);
  Vector up(0,1,0);
  //Camera cam(camPos,look,up, 3.5);
  Camera cam(camPos,look,up, 5);
  cam.setPixDim(720,540);
  //cam.setPixDim(540,720);
  cam.setDim(4,3);
  
  w.printObjects();  

  Image im = cam.render(w);
  
  w.printObjects();
  
  im.toPPM("test.ppm");
  
/*  Colour c0(.8,.8,.8);
  Colour c1(.5,.5,.5);
  
  Colour c2 = c0*c1;
  
  std::cout << c2.getR() << ", " << c2.getG() << ", " << c2.getB() << std::endl;
*/
  return 0;
}
/*
 47   Sphere* s = dynamic_cast<Sphere*>(w.getFrontObject());
 48   Point center(s->getCenter());
 49   std::cout << center << std::endl;
*/
