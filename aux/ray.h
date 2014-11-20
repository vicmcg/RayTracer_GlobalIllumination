// Dan Goldberg and Vic McGowen
// Ray class header

#ifndef RAY_H_
#define RAY_H_

// Included Dependencies
#include <string>
#include "../aux/vector.h"
#include "../aux/point.h"

class Ray {
  public:
    Ray();
    Ray(const Point& p,const Vector& v);
    Ray(const Ray& other);

    virtual ~Ray();
    
    Point getOrigin() const {return origin_;};
    Vector getDirection() const {return direction_; };
    void setOrigin(const Point& p) {origin_=p;};
    void setDirection(const Vector& v) {direction_=v;};
    Ray reflect(const Ray& normal)const;

    std::string toString() const;

  private:
    Point origin_;
    Vector direction_;

};

#endif
