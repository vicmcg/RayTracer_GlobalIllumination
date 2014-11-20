// Dan Goldberg and Vic McGowen
// Vector class

#ifndef VECTOR_H_
#define VECTOR_H_

// Included Dependencies
#include <string>
#include <sstream>
#include <Eigen/Dense>

class Vector {
  public:
    Vector();
    Vector(double x, double y, double z);
    Vector(const Vector& other);
    Vector(const Eigen::Vector3d& vec);
    virtual ~Vector();

    double getX() const {return vector_(0);};
    double getY() const {return vector_(1);};
    double getZ() const {return vector_(2);};
    Eigen::Vector3d getVector() const {return vector_;};
    double getLength() const {return vector_.norm();};
    std::string toString() const;

    Vector reflect(const Vector& normal)const;
    Vector normalize()const {return Vector(vector_.normalized());};
    void transform(const Eigen::Matrix4d& mat);
    Vector cross(const Vector& other) const;

    Vector operator+(const Vector& v2) const;
    Vector operator-(const Vector& v2) const;
    double operator*(const Vector& v2) const;
    Vector operator*(const double& a) const;
    double& operator()(const int index) ;

    friend Vector operator*(const double& a, const Vector& v);
    friend std::ostream& operator<< (std::ostream &out, Vector &v);
    friend std::istream& operator>> (std::istream &in, Vector &v);
 
  private:
    Eigen::Vector3d vector_;
};

 

#endif
