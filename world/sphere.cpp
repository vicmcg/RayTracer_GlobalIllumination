//Vic McGowen and Dan Goldberg Ray Tracer

#include "sphere.h"

Sphere::Sphere() // constructor
	: r_(0), c_() {}

Sphere::Sphere(double r, Point c)
	: r_(r), c_(c){}

Sphere::~Sphere(){} // deconstructor

void Sphere::setCenter(const Point c ){
	c_ = c; 
} // setCenter


std::string Sphere::toString() const {
  std::ostringstream ss;
  ss << "Sphere: " << c_.toString() << ", " << r_;
  return ss.str();
}


void Sphere::transform(const Eigen::Matrix4d& mat){
	c_.transform(mat);
} // transform

/*
void Sphere::setColour(const Colour& c){
	col_ = c;
} // setColour
*/

double Sphere::intersect(const Ray& ray){ // intersect method
	// Get the origin point of Ray b
	Point o = ray.getOrigin(); 
	double xo = o.getX();
	double yo = o.getY();
	double zo = o.getZ();

	// Get the direction point of Ray b
	Vector dir = (ray.getDirection()).normalize(); 
	double dx = dir.getX();
	double dy = dir.getY();
	double dz = dir.getZ();

	// Get the centre point of sphere
	double xc = c_.getX();
	double yc = c_.getY();
	double zc = c_.getZ();

  double xdiff = xo-xc;
  double ydiff = yo-yc;
  double zdiff = zo-zc;

	// Intersection equations
	//double a_ = pow( dx_, 2) + pow( dy_, 2) + pow( dz_, 2);
	//double b = 2*( dx*(xo - xc) + (dy*(yo - yc)) + (dz*(zo - zc)) );
	//double c = pow((xo - xc), 2) + pow((yo - yc), 2) + pow((zo - zc), 2) - pow(r_, 2); 
  double b = 2 * ( dx*xdiff + dy*ydiff + dz*zdiff);
  double c = xdiff*xdiff + ydiff*ydiff + zdiff*zdiff - r_*r_;

	//double test = pow(b, 2) - (4*c);
	double det = b*b - (4*c);
  double sqDet = sqrt(det);

	double w = std::numeric_limits<double>::max();
	if( det < 0 ){ // imaginary roots
		return w;
	}

	// Master equation to find omega
//	double posw = (-1.*b_ + sqrt( pow(b_, 2) - (4*a_*c_) ) ) / (2*a_) ;
//	double negw = (-1.*b_ - sqrt( pow(b_, 2) - (4*a_*c_) ) ) / (2*a_) ;
//  double posw = (-1.*b_ + sqrt( pow(b_, 2) - (4*c_) ) ) *.5 ;
//  double negw = (-1.*b_ - sqrt( pow(b_, 2) - (4*c_) ) ) *.5 ;
  double posw = (-b + sqDet) *.5;
  double negw = (-b - sqDet) *.5;

  bool hit = false;
   
  // If one is neg
	if ( posw < 0.0 ) { 
		// If the other is also neg
		if( negw <0){
			return w;
		}
    // if the other is pos - Hit
		else{
      hit = true;
      //std::cout << "1 Hit\n";
			w = negw;
		}
	}
  // If first is pos
	else if(posw>0.000001){
    hit = true;
    // If second is also pos
		if( negw > 0.000001){
//      std::cout<< negw <<"\n";
//      std::cout<< posw <<"\n";
      // If second is greater
			if(negw > posw){
        if (posw > 0.000001){
				  w = posw;
        }else{
          w = negw;
        }
			}else{
        if (negw > 0.000001){
  				w = negw;
        }else{
          w = posw;
        }
			}
//      std::cout<<"Chose: "<<w<<"\n";
		}
    // Second is neg
		else if(posw>0.000001){
      //std::cout<<"1 hit\n";
			w = posw;
		}
	}
  
  if (hit) {
    Point p(xo+dx*w, yo+dy*w, zo+dz*w);
    Vector n = c_ - p;
    setNormal(n.normalize());
  }
  
	return w;
} // intersect




