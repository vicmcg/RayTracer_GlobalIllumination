//Vic McGowen and Dan Goldberg Ray Tracer

#include "colour.h"

Colour::Colour() 
	: r_(0), g_(0), b_(0){}

Colour::Colour(double a)
  : r_(a), g_(a), b_(a){}

Colour::Colour(double r, double g, double b)
	: r_(r), g_(g), b_(b){}

Colour::Colour(const Colour& c)
  : r_(c.getR()), g_(c.getG()), b_(c.getB()){}

Colour::~Colour(){} // deconstructor

void Colour::setR(double r){ r_ = r; } // setR

void Colour::setG(double g){ g_ = g; } // setG

void Colour::setB(double b){ b_ = b;} // setB

void Colour::setRGB(double a){
  r_ = a;
  g_ = a;
  b_ = a;
}

void Colour::setRGB(double r, double g, double b){
	r_ = r; 
	g_ = g;
	b_ = b;
}// setRGB

//const Colour::Colour black(0,0,0);
//const Colour::Colour red(1,0,0);
//const Colour::Colour green(0,1,0);
//const Colour::Colour blue(0,0,1);
//const Colour::Colour white(1,1,1);

Colour Colour::operator*( const Colour& other ) const{
	Colour result;
	result.r_ = other.r_ * r_;
	result.g_ = other.g_ * g_;
	result.b_ = other.b_ * b_;
	return result;
}// operator*

Colour Colour::operator/( const Colour& other ) const{
	Colour result;
	result.r_ = r_ / other.r_;
	result.g_ = g_ / other.g_;
	result.b_ = b_ / other.b_;
	return result;
}// operator*

Colour Colour::operator*( const double& a ) const{
	Colour result;
	result.r_ = a * r_;
	result.g_ = a * g_;
	result.b_ = a * b_;
	return result;
}// operator*

Colour Colour::operator/( const double& a ) const{
	Colour result;
	result.r_ = r_/a;
	result.g_ = g_/a;
	result.b_ = b_/a;
	return result;
}// operator*

Colour Colour::operator+( const Colour& o ) const{
  return Colour(o.r_+r_,o.g_+g_,o.b_+b_);
}
