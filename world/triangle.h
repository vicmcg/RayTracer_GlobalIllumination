// Dan Goldberg and Vic McGowen
// Triangle class

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

// Included Dependencies
#include <iostream>
#include <string>
#include <cmath>
#include <Eigen/Dense>
#include "../aux/ray.h"
#include "../aux/point.h"
#include "../aux/colour.h"
#include "../aux/vector.h"
#include "../world/object.h"

class Triangle: public Object{

public:

	Triangle(); // initial constructor
	Triangle(Point v0, Point v1, Point v2); // clockwise
	virtual ~Triangle(); // deconstructor 

  Point getv0()const{return v0_;};
  Point getv1()const{return v1_;};
  Point getv2()const{return v2_;};

  std::string toString() const;
	double intersect(const Ray& b) ; // intersect method
	void transform(const Eigen::Matrix4d& mat);
//	void setColour(const Colour& c);

private:
	Point v0_;
	Point v1_;
	Point v2_;
};

#endif
