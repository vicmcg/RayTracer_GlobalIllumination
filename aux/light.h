// Dan Goldberg and Vic McGowen
// Light source class

#ifndef LIGHT_H_
#define LIGHT_H_

#include <string>
#include <Eigen/Dense>
#include "../aux/point.h"
#include "../aux/colour.h"

class Light{

public:
  Light();
  Light(const Point& p, const Colour& c);
  Light(const Light& l);
  virtual ~Light();

  void setColour(const Colour& c) {col_=c;};
  void setPosition(const Point& p) {pos_=p;};
  
  Colour getColour() const {return col_;};
  Point getPosition() const {return pos_;};

  std::string toString()const;

  void transform(const Eigen::Matrix4d& mat){pos_.transform(mat);};

private:
  Point pos_;
  Colour col_;
};

#endif
