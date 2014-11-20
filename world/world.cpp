// Dan Goldberg and Vic McGowen
// World class

#include "world.h"

World::World()
  : objects_(std::list<Object*>()),lights_(std::list<Light*>()), bgcolour_(Colour()), model_(new IlluminationModel()) {}
/*
World::World(Colour& c)
  : objects_(std::list<Object*>()), bgcolour_(c) {}

World::World(Colour& c, std::list<Object*>& olist)
  : objects_(olist), bgcolour_(c) {}
*/
World::~World(){
  std::list<Object*>::iterator it; 
  for(it = objects_.begin(); it != objects_.end(); it++)
    delete *it;
  std::list<Light*>::iterator it2;
  for(it2 = lights_.begin(); it2 != lights_.end();it2++)
    delete *it2;
  
  delete model_;
}

void World::printObjects()const{
  std::list<Object*>::const_iterator it;
  for(it = objects_.begin(); it != objects_.end(); it++)
    std::cout<<(*it)->toString()<<"\n";
}

void World::printLights()const{
  std::list<Light*>::const_iterator it;
  for(it = lights_.begin(); it != lights_.end(); it++)
    std::cout<<(*it)->toString()<<"\n";
}

void World::transformAll(const Eigen::Matrix4d& mat){
  std::list<Object*>::iterator it;
  for(it = objects_.begin(); it != objects_.end(); it++){
    // Same thing as below different notation
    //(*it).transform(mat);
    // need extra * in addition to -> since its a list of pointers
    (*it)->transform(mat);
    (*it)->setView(mat);
  }
  std::list<Light*>::iterator it2;
  for(it2 = lights_.begin(); it2 != lights_.end(); it2++){
    (*it2)->transform(mat);
  }
}
Ray World::calcTrans(const Ray& r,const Vector& inNorm,double n)const{
  Ray outR;
  double n1=worldn_, n2=n;
  outR.setOrigin(r.getOrigin());
  Vector d(r.getDirection());
  Vector t(d);
  
  Vector norm(inNorm);
  if ((inNorm*d) < 0){
    // Inside object
    norm = norm * (-1);
    n1 = n;
    n2 = worldn_;
  }
  
  double TT(n1);
  n1 = n2;
  n2 = TT;
  
  double small = 0.000000001;
  //if n1~n2 then just return r
  if ((n1>(n2-small))&&(n1<(n2+small))){
    // No change in n
    return r;
  } else {
    // Change in n
    double under = 1 - (n1*n1/(n2*n2) * (1 - (d*norm)*(d*norm)));
    if ((under < 0)){
      // Total Internal ref
      outR.setDirection(d.reflect(norm));
    } else {
      t = (d-norm*(d*norm))*(n1/n2) + norm * std::sqrt(under);
      outR.setDirection(t);
    }
  }
  return outR;
}

Object* World::intersectWithObjects(const Ray& r, double& least_w){
  return intersectWithObjects(r,least_w,NULL);
}

Object* World::intersectWithObjects(const Ray& r, double& least_w, const Object* ignoreO){
  double w;
  //double least_w = std::numeric_limits<double>::max();
  Object *close_o = NULL;
  std::list<Object*>::iterator it;
  
  for(it = objects_.begin(); it != objects_.end(); it++){
    if (*it!=ignoreO){
        w = (*it)->intersect(r);
      //std::cout<<w<<"\n";
      if (std::isfinite(w) && (w < least_w) && (w>0)){
        //std::cout<<w;
        least_w = w;
        close_o = (*it);
      }
    }
  }
  return close_o;
} 

Colour World::spawn(const Ray& r) {
  return spawnrec(r,0);
}

Colour World::spawnrec(const Ray& r,const int& depth) {
  Point p;
  Vector normal;
  Vector incoming;
  Vector reflective;
  std::list<Light*> lights(getLightList());
  IntersectData data;
  double lightW;
//  bool useBG = true;

  Colour illumination = getBgColour();
  double max_w = std::numeric_limits<double>::max();
  double least_w = max_w;
  Object* close_o = intersectWithObjects(r,least_w);

  // If intersection 
  if (close_o){
//    useBG = false;
    // Initialize things
    illumination = Colour();
    Vector origin = (r.getOrigin()).getVec();
    Vector dir = r.getDirection();
    p = Point(origin+(dir*least_w));
    normal = close_o->getNormal();
    data.setPoint(p);
    data.setNormal(normal.normalize());
    data.setViewing((p-Point()).normalize());
 
    Ray lightRay;
    Ray shadowRay;
    Ray outShadowRay;
    Object* blockingObject;
    least_w = std::numeric_limits<double>::max();
    std::list<Light*>::iterator it;
    Vector lightDir;
    for(it = lights.begin(); it != lights.end(); it++){
      lightDir = (p-((*it)->getPosition())).normalize();
      lightRay = Ray(p,lightDir);
      blockingObject = intersectWithObjects(lightRay,least_w,close_o);
      incoming = p-((*it)->getPosition());
      reflective = ((*it)->getPosition()-p).reflect(normal).normalize();
      data.setLight(*(*it));
      data.setIncoming(incoming.normalize());
      data.setReflective(reflective.normalize());
        
      if (blockingObject){
        // In shadow
        if (blockingObject->getkt()>0){
          //shadowRay.setOrigin(Point(origin+(lightDir*least_w)));
          //shadowRay.setDirection(lightRay.getDirection());
          //outShadowRay = calcTrans(shadowRay,(blockingObject->getNormal()).normalize(),blockingObject->getn());
          illumination = illumination +
                          model_->illuminate(close_o,data) * blockingObject->getkt();
        }
 
      } else {
        // Not in shadow
        //std::cout<<(blockingObject->toString())<<"\n";
        lightW = close_o->intersect(lightRay);
        if (std::isfinite(lightW) || (lightW>0)){
         illumination = illumination + model_->illuminate(close_o,data);
        }
      }
      
    }
    if (depth < close_o->getDepth()){
      // Reflected Ray
      if (close_o->getkr()>0){
        Ray refRay(p,(Point()-p).reflect(normal).normalize());
        illumination = illumination +
                        (spawnrec(refRay,depth+1)
                        * close_o->getkr());
      }
      // Transmission ray
      if (close_o->getkt()>0){
        Ray inRay(p,r.getDirection());
//        std::cout<<"In: "<<inRay.toString()<<"\n";
        Ray transRay = calcTrans(inRay,normal,close_o->getn());
//        std::cout<<"Out: "<<transRay.toString()<<"\n";
        illumination = illumination +
                        (spawnrec(transRay,depth+1)
                        * close_o->getkt());
      }
    }

/*    if (useBG){
      illumination = getBgColour();
    }*/
  }
  return illumination;
}
