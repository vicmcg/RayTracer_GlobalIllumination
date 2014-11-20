// Dan Goldberg and Vic McGowen
// Box class

#ifndef BOX_H_
#define BOX_H_

// Included Dependencies
#include <iostream>
#include <string>
#include <list>
#include <cmath>
#include <Eigen/Dense>
#include "../aux/ray.h"
#include "../aux/point.h"
#include "../aux/colour.h"
#include "../world/object.h"
#include "../world/triangle.h"
#include "../world/sphere.h"

class Box: public Object{

public:

	Box(); // initial constructor
  //Box(Point a,Point b,Point c, Point d,Point e,Point f,Point g,Point h);
  Box(const Point& min,const Point& max);
	Box(const std::list<Point>& p);
  Box(const Sphere& s);
  Box(const Triangle& t);
	virtual ~Box(); // deconstructor 

  Point getMin()const{return min_;};
  Point getMax()const{return max_;};
  void setMin(const Point& p){min_=p;};
  void setMax(const Point& p){max_=p;};

  std::string toString() const;

	double intersect(const Ray& ray); // intersect method
	void transform(const Eigen::Matrix4d& mat);

private:
	Point min_;
  Point max_;
  std::list<Point> points_;
};

#endif
