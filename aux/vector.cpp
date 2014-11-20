// Dan Goldberg
// Vector Class

#include "vector.h"

// Constructors
Vector::Vector()
  : vector_(Eigen::Vector3d())  {}

Vector::Vector(double x, double y, double z)
  : vector_(Eigen::Vector3d(x,y,z)) {}

Vector::Vector(const Vector& other)
  : vector_(other.getVector()){}

Vector::Vector(const Eigen::Vector3d& vec)
  : vector_(vec){}

Vector::~Vector(){}


std::string Vector::toString() const{
  double v0 = vector_(0);
  double v1 = vector_(1);
  double v2 = vector_(2);
  std::ostringstream strOut;
  strOut << std::string("(") << v0 << ", " << v1 << ", " << v2 << ")";
  return strOut.str();
}

Vector Vector::reflect(const Vector& n)const{
  Vector S((*this));
  double magNinv = 1/(n.getLength()*n.getLength());
  return S-2*(S*n)*magNinv*n;
}

/**
  Transforms vector by 4x4 matrix mat:
    1) Puts 3D Vector in 4D Eigen Vector
    2) does multiplication using Eigen's but in *
    3) puts result back into the same 3D Vector

*/
void Vector::transform(const Eigen::Matrix4d& mat){
  Eigen::Vector4d v(vector_(0),vector_(1),vector_(2),1.0);
  Eigen::Vector4d newV = mat*v;
  vector_(0) = newV(0);
  vector_(1) = newV(1);
  vector_(2) = newV(2);
}

/**
  Wrapped around Eigen's cross
*/
Vector Vector::cross(const Vector& other) const {
  return Vector(getVector().cross(other.getVector()));
}

/**
  add two vector's components
*/
Vector Vector::operator+(const Vector& v2) const {
  return Vector(getX()+v2.getX(),getY()+v2.getY(),getZ()+v2.getZ());
}

/**
  subtract two vectors components
*/
Vector Vector::operator-(const Vector& v2) const {
  return Vector(getX()-v2.getX(),getY()-v2.getY(),getZ()-v2.getZ());
}

/**
  do Eigen's dot product
*/  
double Vector::operator*(const Vector& v2) const {
  return getVector().dot(v2.getVector());
}

/**
  Multiply the scaler by each component
*/
Vector Vector::operator*(const double& a) const {
  return Vector(getX()*a,getY()*a,getZ()*a);
}

/**
  try to do indexing
*/
double& Vector::operator()(const int index) {
  assert(index >= 0 && index<3);

  return vector_(index);
}

/**
  Non-member class (no Vector::) means it takes 2 inputs (left and right)
  these were adapted from examples from 

http://stackoverflow.com/questions/19369975/c-overriding-and-operators

*/

Vector operator*(const double& a, const Vector& v) {
  double x(v.getX()*a);
  double y(v.getY()*a);
  double z(v.getZ()*a);
  return Vector(x,y,z);
}


std::ostream& operator<< (std::ostream &out, Vector &v)
{
    // Since operator<< is a friend of the Point class, we can access
    // Point's members directly.
    out << "(" << v.vector_(0) << ", " <<
        v.vector_(1) << ", " <<
        v.vector_(2) << ")";
    return out;
}
 
std::istream& operator>> (std::istream &in, Vector& v)
{
    in >> v.vector_(0);
    in >> v.vector_(1);
    in >> v.vector_(2);
    return in;
}
