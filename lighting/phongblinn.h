// Vic McGowen and Dan Goldberg Ray Tracer 
// PhongBlinn Illumination Model

#ifndef PHONGBLINN_H_
#define PHONGBLINN_H_

#include <iostream>
#include <cmath>
#include "../lighting/illuminationmodel.h"
#include "../aux/intersectdata.h"
#include "../aux/colour.h"

class PhongBlinn: public IlluminationModel{

public:
  PhongBlinn();
  virtual ~PhongBlinn();

  void setKd(const double& kd){kd_=kd;};
  void setKs(const double& ks){ks_=ks;};
  void setKe(const double& ke){ke_=ke;};

  Colour illuminate(const Object* o,const IntersectData& intersect);

private:
  double kd_;
  double ks_;
  double ke_;
};


#endif
