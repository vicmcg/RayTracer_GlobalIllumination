//Vic McGowen and Dan Goldberg Ray Tracer

#include "triangle.h"

Triangle::Triangle() // initial constructor
	: v0_(Point()), v1_(Point()), v2_(Point()){
  setNormal(Vector());
} 

Triangle::Triangle(Point v0, Point v1, Point v2) // constructor w vertices
	: v0_(v0), v1_(v1), v2_(v2){
  setNormal(((v1-v0).cross(v2-v0)).normalize());
}

Triangle::~Triangle(){} // deconstructor


std::string Triangle::toString() const {
  return "Triangle: ("+v0_.toString()+", "+v1_.toString()+", "+v2_.toString()+")";
}

void Triangle::transform(const Eigen::Matrix4d& mat){
	v0_.transform(mat);
	v1_.transform(mat);
	v2_.transform(mat);
  setNormal(((v1_-v0_).cross(v2_-v0_)).normalize());
} // transform

double Triangle::intersect(const Ray& b) { // intersection between triangle and ray b
	double distance; // distance to return

	// Define Ray properties
	Vector d = b.getDirection();
	Point o = b.getOrigin();

	// define triangle vectors
	Vector e1 = v0_ - v1_;
	Vector e2 = v0_ - v2_;
	Vector T = v0_ - o;
	Vector p = d.cross(e2);
	Vector q = T.cross(e1);

	// define dot products for matrix
	double pe1 = p *(e1); // denominator 
	double fraction = 1.0/pe1;

	// Vector
	Eigen::Vector3d m;
	m(0) = q * e2;
	m(1) = p* T;
	m(2) = q * d;

	// t u v Vector
	Eigen::Vector3d tuv = fraction * m;

	// defining t u and v
	double t = tuv(0);
	double u = tuv(1);
	double v = tuv(2);

	// no hit cases
	if (pe1 == 0.0) { //parallel ray
		distance = 0;
	}
	
	else if (t < 0.000001) { //intersect behind origin
		distance = 0;
	}
	
	else if (u< 0.0 || v < 0.0 || u+v >1.0) { // intersect outside of triangle
		distance = 0;
	}

	else{// intersect
		distance = t;
	}


	return distance;
} // intersect
