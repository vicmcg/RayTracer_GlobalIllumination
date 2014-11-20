// Dan Goldberg and Vic McGowen
// Phong class

#include "phong.h"

Phong::Phong()
  :kd_(.8),ks_(.2),ke_(2){}

Phong::~Phong(){}

Colour Phong::illuminate(const Object* o, const IntersectData& data){
  Colour outColour;
  Point p = data.getPoint();
  Vector N = data.getNormal();
  Vector S = data.getIncoming();
  Vector R = data.getReflective();
  Vector V = data.getViewing();
  Light l = data.getLight();

  double d = p.distance(l.getPosition());

  Colour L = l.getColour();
  Colour Co;
  if (o->hasTexture()){
    Co = (o->getTexture())->getTexture(data,o->getView());
  } else {
    Co = o->getColour();
  }
  double diff = S*N;
  if (diff<0)
    diff = 0;

  Colour Cs = o->getSpecular();
  double spec = R*V;

  if (spec<0)
    spec = 0;
  if (spec>1)
    spec = 0;

  outColour = L*Co*diff*kd_ + L*Cs*std::pow(spec, ke_)*ks_;
  outColour = outColour*(1/(d*d));
  
/*  if (outColour.getR()<0||outColour.getG()<0||outColour.getB()<0){
    std::cout<<diff<<"\n"<<spec<<"\n";
    outColour = Colour();
  }*/

  return outColour;
}
