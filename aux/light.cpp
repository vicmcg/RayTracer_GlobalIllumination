// Dan Goldberg and Vic McGowen
// Light Class

#include "light.h"

Light::Light()
  : pos_(Point()), col_(Colour()){}

Light::Light(const Point& p, const Colour& c)
  : pos_(p), col_(c){}

Light::Light(const Light& l)
  : pos_(l.getPosition()), col_(l.getColour()){}

Light::~Light(){}

std::string Light::toString()const{
  std::string out("Light: ");
  out = out + pos_.toString() + ", " + col_.toString();
  return out;
}
