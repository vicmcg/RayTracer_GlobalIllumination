//Dan Goldberg
// Tools for ray tracer

#ifndef TOOLS_H_
#define TOOLS_H_

#include <cmath>

class Tools {
  private:
    static double fade(const double& t){
          return t * t * t * (t * (t * 6 - 15) + 10);};
    static double lerp(const double& t, const double& a, const double& b){
          return a + t * (b - a);};
    static double grad(const int& hash,const double& x,const double& y, const double& z){
          int h = hash & 15;                      // CONVERT LO 4 BITS OF HASH CODE
          double u = h<8 ? x : y,                 // INTO 12 GRADIENT DIRECTIONS.
                 v = h<4 ? y : h==12||h==14 ? x : z;
          return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
    };

  public:
    static double noise(double x, double y, double z);
};

#endif
