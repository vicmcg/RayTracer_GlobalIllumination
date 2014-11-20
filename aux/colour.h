//Vic McGowen and Dan Goldberg Ray Tracer

#ifndef COLOUR_H_
#define COLOUR_H_

// Included Dependencies
#include <string>
#include "../aux/vector.h"

class Colour{

public:
	Colour();
  Colour(double a);
	Colour(double r, double g, double b); 
  Colour(const Colour& c);
	virtual ~Colour();

	static const Colour black;
	static const Colour red;
	static const Colour green;
	static const Colour blue;
	static const Colour white;
	
	double getR() const { return r_; };
	double getG() const { return g_; };
	double getB() const { return b_; };

	void setR(double r);
	void setG(double g);
	void setB(double b);
  void setRGB(double a);
	void setRGB(double r, double g, double b);

  Vector getVec()const{return Vector(r_,g_,b_);};
  std::string toString()const{return getVec().toString();};

	Colour operator* (const Colour& b) const;
	Colour operator/ (const Colour& b) const;
	Colour operator* (const double& a) const;
	Colour operator/ (const double& a) const;
  Colour operator+ (const Colour& b) const;

private:
	double r_;
	double g_;
	double b_;

};

#endif
