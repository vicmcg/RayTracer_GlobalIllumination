//Vic McGowen and Dan Goldberg Ray Tracer

#include "box.h"

Box::Box(){} // constructor
Box::Box(const Point& min,const Point& max){
  min_ = min;
  max_ = max;
}
Box::Box(const std::list<Point>& p){
  double smallx=std::numeric_limits<double>::max();
  double smally=std::numeric_limits<double>::max();
  double smallz=std::numeric_limits<double>::max();
  double largex=0;
  double largey=0;
  double largez=0;
  
  std::list<Point>::const_iterator it;
  for ( it=p.begin();it != p.end(); it++){
    if ((*it).getX() < smallx){
      smallx = (*it).getX();
    }
    if ((*it).getY() < smally){
      smally = (*it).getY();
    }
    if ((*it).getZ() < smallz){
      smallz = (*it).getZ();
    }
 
    if ((*it).getX() > largex){
      largex = (*it).getX();
    }
    if ((*it).getY() > largey){
      largey = (*it).getY();
    }
    if ((*it).getZ() > largez){
      largez = (*it).getZ();
    }
  }
  
  min_ = Point(smallx,smally,smallz);
  max_ = Point(largex,largey,largez);
}


Box::~Box(){} // deconstructor

std::string Box::toString() const {
  std::ostringstream ss;
  ss << "Box: " << min_.toString() << ", " << max_.toString();
  return ss.str();
}


void Box::transform(const Eigen::Matrix4d& mat){
/*
  std::list<Point> ps;
  std::list<Point>::iterator it;
  for ( it=points_.begin();it != points_.end(); it++){
    Point p(*it);
    p.transform(mat);
    ps.push_back(p);
  }
  Box b(ps);
  min_=b.getMin();
  max_=b.getMax();
*/
  min_.transform(mat);
  max_.transform(mat);
} // transform

/*
void Box::setColour(const Colour& c){
	col_ = c;
} // setColour
*/

double Box::intersect(const Ray& ray){ // intersect method
  // from http://www.siggraph.org/education/materials/HyperGraph/raytrace/rtinter3.htm
  double MAX=std::numeric_limits<double>::max();
  double tnear = -MAX;
  double tfar = MAX;
  Point A(ray.getOrigin());
  Vector B(ray.getDirection());
  double xd(B.getX()),yd(B.getY()),zd(B.getZ());
  double xo(A.getX()),yo(A.getY()),zo(A.getZ());
  
  double minx(min_.getX()),miny(min_.getY()),minz(min_.getZ());
  double maxx(max_.getX()),maxy(max_.getY()),maxz(max_.getZ());
  double t1,t2,temp;

  Vector xn(-1,0,0);
  Vector yn(0,-1,0);
  Vector zn(0,0,-1);
  Vector norm;
  
  bool switched(false);
  
  if (xd == 0){
    if ( (xo < minx) || (xo > maxx) ){
      // Parallel to X
      return MAX;
    }
  } else {
    t1 = (minx - xo)/xd;
    t2 = (maxx - xo)/xd;
    if (t1>t2){
      temp = t1;
      t1 = t2;
      t2 = temp;
      switched=true;
    }
    if (t1 > tnear){
      tnear = t1;
      if (switched){
        norm = xn*(-1);
      } else {
        norm = xn;
      }
    }
    if (t2 < tfar){
      tfar = t2;
    }
  }
  
  if (yd == 0){
    if ( (yo < miny) || (yo > maxy) ){
      // Parallel to Y
      return MAX;
    }
  } else {
    t1 = (miny - yo)/yd;
    t2 = (maxy - yo)/yd;
    if (t1>t2){
      temp = t1;
      t1 = t2;
      t2 = temp;
      switched=true;
    }

    if (t1 > tnear){
      tnear = t1;
      if (switched){
        norm = yn*(-1);
      } else {
        norm = yn;
      }
    }

    if (t2 < tfar){
      tfar = t2;
    }
  }

  
  if (zd == 0){
    if ( (zo < minz) || (zo > maxz) ){
      // Parallel to Z
      return MAX;
    }
  } else {
    t1 = (minz - zo)/zd;
    t2 = (maxz - zo)/zd;
    if (t1>t2){
      temp = t1;
      t1 = t2;
      t2 = temp;
      switched=true;
    }
    if (t1 > tnear){
      tnear = t1;
      if (switched){
        norm = zn*(-1);
      } else {
        norm = zn;
      }
    }

    if (t2 < tfar){
      tfar = t2;
    }
  }
  
  //std::cout<<norm.toString()<<" "<<tnear<<"\n";
  
  setNormal(norm);
  return tnear;
} // intersect
