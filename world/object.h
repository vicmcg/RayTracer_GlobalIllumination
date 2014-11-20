// Dan Goldberg and Vic McGowen
// Object class

#ifndef OBJECT_H_
#define OBJECT_H_

// Included Dependencies
#include <iostream>
#include <string>
#include <Eigen/Dense>
#include "../aux/ray.h"
#include "../aux/vector.h"
#include "../aux/colour.h"
#include "../texture/texture.h"
//#include "../world/illuminationmodel.h"
//#include "../world/intersectdata.h"


class Object{

public:

	Object(); // initial constructor
  virtual ~Object();

  virtual void setNormal(const Vector& v){normal_=v;};
	virtual void setColour(const Colour& c){colour_=c;};
  virtual void setSpecular(const Colour& c){specular_=c;};
  // Takes ownership of t
  virtual void setTexture(Texture* t){texture_=t;};
  virtual void setView(const Eigen::Matrix4d& view){viewMatrix_=view;};
  virtual void setkr(const double& kr){kr_=kr;};
  virtual void setkt(const double& kt){kt_=kt;};
  virtual void setn(const double& n){n_=n;};
  virtual void setDepth(const int& d){depth_=d;};

  virtual Vector getNormal()const{return normal_;};
  virtual Colour getColour()const{return colour_;};
  virtual Colour getSpecular()const{return specular_;};
  virtual const Texture* getTexture()const{return texture_;};
  virtual Eigen::Matrix4d getView()const{return viewMatrix_;};
  virtual double getkr(){return kr_;};
  virtual double getkt(){return kt_;};
  virtual double getn(){return n_;};
  virtual int getDepth(){return depth_;};

 
  virtual bool hasTexture()const{return getTexture();};
	virtual double intersect(const Ray& ray) = 0; // initial intersect method
	virtual void transform(const Eigen::Matrix4d& mat) = 0; // transform method

  virtual std::string toString() const = 0;


private:
//  IlluminationModel iModel_;
  Vector normal_;
  Colour colour_;
  Colour specular_;
  const Texture* texture_;
  Eigen::Matrix4d viewMatrix_;
  double kr_;
  double kt_;
  double n_;
  int depth_;
};

#endif
