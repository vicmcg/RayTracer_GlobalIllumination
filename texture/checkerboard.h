// Vic McGowen and Dan Goldberg Ray Tracer
// Checkerboard class

#ifndef CHECKERBOARD_H_
#define CHECKERBOARD_H_

#include <iostream>
#include <cmath>
#include <string>
#include <Eigen/LU> 
#include <Eigen/Dense> 
#include "../texture/texture.h"
#include "../aux/point.h"
#include "../aux/intersectdata.h"
#include "../aux/colour.h"
#include "../world/camera.h"
#include "../world/world.h"
#include "../aux/tools.h"

class Checkerboard: public Texture{

public:

	Checkerboard(); // constructor
	Checkerboard(Colour colour1, Colour colour2); // constructor defining class's colours
	virtual ~Checkerboard(); // destructor

  void setV0(const Point& uv,const Point& xyz){uv0_=uv;v0_=xyz;};
  void setV1(const Point& uv,const Point& xyz){uv1_=uv;v1_=xyz;};
  void setV2(const Point& uv,const Point& xyz){uv2_=uv;v2_=xyz;};

	// @override Texture functions
	double* getUV(const IntersectData& intersect,const Eigen::Matrix4d& view)const;
  Colour getTexture(const double* uv)const;
  Colour getTexture(const IntersectData& intersect,
                    const Eigen::Matrix4d& view)const;

  std::string toString() const{return "Checkerboard";};

private:
	Colour colour1_;
	Colour colour2_;
  // UV point then XYZ point
  Point uv0_;
  Point v0_;
  Point uv1_;
  Point v1_;
  Point uv2_;
  Point v2_;
};


#endif
