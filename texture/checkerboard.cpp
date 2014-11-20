// Vic McGowen and Dan Goldberg Ray Tracer
// Checkerboard class

#include "checkerboard.h"

Checkerboard::Checkerboard()
	: colour1_(Colour(1,1,0)), colour2_(Colour(1,0,0)){}

Checkerboard::Checkerboard(Colour colour1, Colour colour2)
	: colour1_(colour1), colour2_(colour2){}

Checkerboard::~Checkerboard(){}

double* Checkerboard::getUV(const IntersectData& intersect,
                                const Eigen::Matrix4d& view)const{
  double* outUV = new double[2];
  // get point of intersection in camera space
	Point p = intersect.getPoint();

	// convert point in camera space to world space
//	Eigen::Matrix4d& inverse = view.inverse();
//	p.transform(inverse);
	p.transform(view.inverse());

  Vector f1 = p-v0_;
  Vector f2 = p-v1_;
  Vector f3 = p-v2_;
  
  Vector s1 = v1_-v0_;
  Vector s2 = v2_-v0_;
  
  double a = s1.cross(s2).getLength();
  double a1 = f2.cross(f3).getLength()/a;
  double a2 = f3.cross(f1).getLength()/a;
  double a3 = f1.cross(f2).getLength()/a;
//  std::cout<<v0_.toString()<<" "<<v1_.toString()<<" "<<v2_.toString()<<"\n";
  double u = uv0_.getX()*a1 + uv1_.getX()*a2 + uv2_.getX()*a3;
  double v = uv0_.getZ()*a1 + uv1_.getZ()*a2 + uv2_.getZ()*a3;

//  std::cout<<u<<" "<<v<<"\n";
  
	//notes say this ranges from [-1,1] for plane example
//	double x = p.getX(); // point x value in world space
//	double z = p.getZ(); // point z value in world space
	// convert to (u, v) based on floor specs -- projector function
	// used Planar mapping function
	//double u = (z+1)/2;
	//double v = (x+1)/2;

  outUV[0] = u;
  outUV[1] = v; 
  
  
	return outUV;
}

Colour Checkerboard::getTexture(const double* uv)const{
  Colour outcolour; // output colour
  
  double u = uv[0];
  double v = uv[1];
  
  int col = (int) (u*2);
  int row = (int) (v*2);
  bool oddRow = (row % 2 == 1);
  bool oddCol = (col % 2 == 1);
  
  double n(0);
  //n = Tools::noise(u-((int) u),v-((int)v),(1-u-v)-((int)(1-u-v)));
  
  if ((oddRow && oddCol) || (!oddRow && !oddCol)) {
    outcolour = colour1_+n;
  } else {
    outcolour = colour2_+n;
  }
  
/*  if (u>.5||v>.5){
    std::cout<<u<<", "<<v<<"\n";
    std::cout<<col<<" "<<row<<"; "<<oddRow<<" "<<oddCol<<"\n";
  }*/
  return outcolour;
}

Colour Checkerboard::getTexture(const IntersectData& intersect,
                                const Eigen::Matrix4d& view)const{
  Colour outcolour;
  
  double* uv = getUV(intersect,view);
  outcolour = getTexture(uv);
  delete[] uv;
  return outcolour;
}

