//Vic McGowen and Dan Goldberg Ray Tracer

#include "object.h"

Object::Object()
  :texture_(NULL),depth_(10){}
 // constructor

Object::~Object(){
//  if(texture_)std::cout<<texture_->toString()<<"\n";
  if (texture_) delete texture_;
} // destructor

// virtual, abstract methods
//double Object::intersect(const Ray& ray) {return 0.0;}
//void Object::transform(const Eigen::Matrix4d& mat){}

/*
// implementation
void Object::computeIllumination(const IntersectData& data){
  addIllumination(iModel_.illuminate(data));
}
*/
