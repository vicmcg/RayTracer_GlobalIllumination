// Dan Goldberg and Vic McGowen
// Texture class

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>
#include <Eigen/Dense>
#include "../aux/colour.h"
#include "../aux/intersectdata.h"

class Texture{
  public:
    Texture();
    virtual ~Texture();
    
    virtual double* getUV(const IntersectData& intersect,
                              const Eigen::Matrix4d& view) const=0;

    virtual Colour getTexture(const double* uv)const=0;
    virtual Colour getTexture(const IntersectData& intersect,
                              const Eigen::Matrix4d& view)const=0;

    virtual std::string toString()const=0;
};

#endif

