//Vic McGowen and Dan Goldberg Ray Tracer
// Camera class

#ifndef CAMERA_H_
#define CAMERA_H_

// Included Dependencies
#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include "../aux/vector.h"
#include "../aux/ray.h"
#include "../aux/point.h"
#include "../world/image.h"
#include "../world/world.h"

class Camera{

public:

	Camera();
	Camera(Point pos, Point look, Vector up, double f);
  Camera(Point pos, Point look, Vector up, double f,
              unsigned int pixW, unsigned int pixH, double height, double width);
	virtual ~Camera();
  
  void roll(const double& theta);
  void pitch(const double& theta);
  void yaw(const double& theta);
  void setPos(const Point& p){pos_=p;};
  void setLook(const Point& p){look_=p;};
  void setUp(const Vector& v){up_=v;};
  void setPixDim(unsigned int pixW, unsigned int pixH);
  void setDim(double wid, double hei);
 
  Eigen::Matrix4d getViewMatrix()const; 
  Image render(World& world, const Eigen::Matrix4d& viewMat);
	Image render(World& world);
  

private:
	Point pos_;
	Point look_;
  Vector up_;
	double focal_;
	unsigned int pixH_; // pixels
	unsigned int pixW_; // pixels
	double height_; // world coordinates
	double width_; // world coordinates

};

#endif
