// Dan Goldberg and Vic McGowen
// Sphere class

#ifndef SPHERE_H_
#define SPHERE_H_

// Included Dependencies
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <Eigen/Dense>
#include "../aux/ray.h"
#include "../aux/point.h"
#include "../aux/colour.h"
#include "../world/object.h"

class Sphere: public Object{

public:

	Sphere(); // initial constructor
	Sphere(double r, Point c);
	virtual ~Sphere(); // deconstructor 

	void setCenter(const Point c ); // change center to move sphere
	Point getCenter() const { return c_; }; // returns center to get coordinates

  std::string toString() const;

	double intersect(const Ray& ray); // intersect method
	void transform(const Eigen::Matrix4d& mat);
	//void setColour(const Colour& c);

private:
	double r_; // radius
	Point c_; // center
};

#endif
