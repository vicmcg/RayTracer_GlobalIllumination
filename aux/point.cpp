//Vic McGowen and Dan Goldberg Ray Tracer

#include "point.h"

// Constructors
Point::Point()
	: point_(Vector(0.0, 0.0, 0.0)){}

Point::Point(double x, double y, double z)
	: point_(Vector(x, y, z)){}

Point::Point(Vector v)
  : point_(Vector(v)){}

Point::~Point(){} // deconstructor

double Point::distance(const Point& other){
	double xx = pow( (other.getX()-getX()), 2);
	double yy = pow( (other.getY()-getY()), 2);
	double zz = pow( (other.getZ()-getZ()), 2);

	double distance = sqrt(xx + yy + zz );
	return distance; 
}

Vector Point::operator-(const Point& b) const{
	double x = b.getX()-getX();
	double y = b.getY()-getY();
	double z = b.getZ()-getZ();
	return Vector(x,y,z);
}

double& Point::operator()(const int index) {
  assert(index>=0 && index<3);

  return point_(index);
}


std::ostream& operator<< (std::ostream &out, Point& p)
{
    // Since operator<< is a friend of the Point class, we can access
    // Point's members directly.
    out << p.point_;
    return out;
}
 
std::istream& operator>> (std::istream &in, Point& p)
{
    in >> p.point_;
    return in;
}
