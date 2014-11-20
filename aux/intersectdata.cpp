//Vic McGowen and Dan Goldberg Ray Tracer

#include "intersectdata.h"

IntersectData::IntersectData()
	: point_(Point()), normal_(Vector()), incoming_(Vector()), reflective_(Vector()),viewing_(Vector()), light_(Light()){}//, lights_(std::list<Light*>()){}

IntersectData::IntersectData(const Point& point,const Vector& normal,const Vector& incoming, const Vector& reflective,const Vector& viewing, const Light& light)//,const std::list<Light*>& lights)
	: point_(point), normal_(normal), incoming_(incoming), reflective_(reflective),viewing_(viewing), light_(light){}//, lights_(lights){}

IntersectData::IntersectData(const IntersectData& o){
  point_=o.getPoint();
  normal_=o.getNormal();
  incoming_=o.getIncoming();
  reflective_=o.getReflective();
  viewing_=o.getViewing();
  light_=o.getLight();
//  lights_=o.getLightList();
}

IntersectData::~IntersectData(){} // deconstructor
/*
void IntersectData::setPoint(const Point& point){
	point_ = point;
}
void IntersectData::setNormal(const Vector& normal){
	normal_ = normal;
}
void IntersectData::setIncoming(const Vector& incoming){
	incoming_ = incoming;
}
void IntersectData::setReflective(const Vector& reflective){
	reflective_ = reflective;
}
void IntersectData::setLightList(const std::list<Light*>& lights){
	lights_ = lights;
}
*/
