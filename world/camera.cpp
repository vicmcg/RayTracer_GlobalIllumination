//Vic McGowen and Dan Goldberg Ray Tracer

#include "camera.h"

Camera::Camera() {
  pos_ = Point(0.,0.,0.);
  look_ = Point(0.,0.,0.);
  up_ = Vector(0,1,0);
  focal_ = 0.;
  pixH_ = 0;
  pixW_ = 0;
  height_ = 0;
  width_ = 0;
}

Camera::~Camera(){} // deconstructor

Camera::Camera(Point pos, Point look, Vector up, double f) {
  pos_ = pos;
  look_ = look;
  up_ = up.normalize();
  focal_ = f;
  pixH_ = 0;
  pixW_ = 0;
  height_ = 0;
  width_ = 0;
}

Camera::Camera(Point pos, Point look, Vector up, double f,
              unsigned int pixW, unsigned int pixH, double height, double width) {
  pos_ = pos;
  look_ = look;
  up_ = up.normalize();
  focal_ = f;
  pixH_ = pixH;
  pixW_ = pixW;
  height_ = height;
  width_ = width;
}

void Camera::roll(const double& theta){
  /*Eigen::Matrix4d mat;
  pos_.transform(mat);
  look_.transform(mat);
  up_.transform(mat);*/
}
  
void Camera::pitch(const double& theta){
}
  
void Camera::yaw(const double& theta){
}



void Camera::setPixDim(const unsigned int pixW, const unsigned int pixH){
  pixH_ = pixH;
  pixW_ = pixW;
}

void Camera::setDim(const double wid, const double hei){
  height_ = hei;
  width_ = wid;
}

Eigen::Matrix4d Camera::getViewMatrix()const{
  Vector n = (pos_-look_).normalize();
  //std::cout<<n<<"\n";
  Vector u = (up_.cross(n)).normalize();
  //std::cout<<u<<"\n";
  Vector v = (n.cross(u)).normalize();
  //std::cout<<v<<"\n";

  Vector eyepoint = pos_.getVec();
  Vector neyepoint = eyepoint*(-1); // multiplication
  Eigen::Matrix4d viewMat;
/*
  viewMat(0,0) = u.getX();
  viewMat(1,0) = u.getY();
  viewMat(2,0) = u.getZ();
  viewMat(3,0) = neyepoint*(u); // dot product
 
  viewMat(0,1) = v.getX();
  viewMat(1,1) = v.getY();
  viewMat(2,1) = v.getZ();
  viewMat(3,1) = neyepoint*(v); // dot product
  
  viewMat(0,2) = n.getX();
  viewMat(1,2) = n.getY();
  viewMat(2,2) = n.getZ();
  viewMat(3,2) = neyepoint*(n); // dot product

  viewMat(0,3) = 0;
  viewMat(1,3) = 0;
  viewMat(2,3) = 0;
  viewMat(3,3) = 1.;
*/

  viewMat(0,0) = u.getX();
  viewMat(0,1) = u.getY();
  viewMat(0,2) = u.getZ();
  viewMat(0,3) = neyepoint*(u); // dot product
 
  viewMat(1,0) = v.getX();
  viewMat(1,1) = v.getY();
  viewMat(1,2) = v.getZ();
  viewMat(1,3) = neyepoint*(v); // dot product
  
  viewMat(2,0) = n.getX();
  viewMat(2,1) = n.getY();
  viewMat(2,2) = n.getZ();
  viewMat(2,3) = neyepoint*(n); // dot product

  viewMat(3,0) = 0;
  viewMat(3,1) = 0;
  viewMat(3,2) = 0;
  viewMat(3,3) = 1.;
  return viewMat;
}

Image Camera::render(World& world,const Eigen::Matrix4d& viewMat){
  
  world.transformAll(viewMat);

  double pixHeight = height_/(double)pixH_;
  double pixWidth = width_/(double)pixW_;
  
  double x = -width_/2. + 0.5*pixWidth;
  double y = height_/2. - .5*pixHeight;
  double topY = y;
  double z = focal_;
  
  Ray r;
  Colour c;
  Point origin;
  Point p;
  Vector dir;
  Image im(pixW_,pixH_);
  for (unsigned int i=0;i<pixW_;++i){
    for (unsigned int j=0;j<pixH_;++j){
      p = Point(x,y,z);
      dir = (origin-p).normalize();
      r.setOrigin(p);
      r.setDirection(dir);
      c = world.spawn(r);
      im.setPixel(i,j,c);
      y-=pixHeight;
      //x+=pixWidth;
    }
    y=topY;
    x+=pixWidth;
  }

  return im;
  
}

Image Camera::render(World& world){
  Eigen::Matrix4d viewMat=getViewMatrix();
  return render(world,viewMat);
}


