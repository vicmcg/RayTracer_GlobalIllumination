// Dan Goldberg and Vic McGowen
// Phong Illumination Model

#ifndef PHONG_H_
#define PHONG_H_

#include <iostream>
#include <cmath>
#include "../lighting/illuminationmodel.h"
#include "../texture/texture.h"
#include "../aux/intersectdata.h"
#include "../aux/colour.h"

class Phong: public IlluminationModel{

public:
  Phong();
  virtual ~Phong();

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
