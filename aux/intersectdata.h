//Vic McGowen and Dan Goldberg Ray Tracer
// IntersectData class

#ifndef INTERSECTDATA_H_
#define INTERSECTDATA_H_

// Included Dependencies
#include <iostream>
#include <Eigen/Dense>
#include <list>
#include "../aux/light.h"
#include "../aux/vector.h"
#include "../aux/point.h"

class IntersectData{
public:

	IntersectData(); // empty constructor
	IntersectData(const Point& point,const Vector& normal,const Vector& incoming,const Vector& reflective,const Vector& viewing, const Light& light);//,const std::list<Light*>& lights);
 	IntersectData(const IntersectData& o);
	virtual ~IntersectData(); // deconstructor

	// getters
	Point getPoint()const {return point_;};
	Vector getNormal()const {return normal_;};
	Vector getIncoming()const {return incoming_;};
	Vector getReflective()const {return reflective_;};
	Vector getViewing()const{return viewing_;};
	Light getLight()const {return light_;};
//	std::list<Light*> getLightList() const {return lights_;};

	// setters
	void setPoint(const Point& point){point_=point;};
	void setNormal(const Vector& normal){normal_=normal;};
	void setIncoming(const Vector& incoming){incoming_=incoming;};
	void setReflective(const Vector& reflective){reflective_=reflective;};
  void setViewing(const Vector& viewing){viewing_=viewing;};
  void setLight(const Light& light){light_=light;};
//	void setLightList(const std::list<Light*>& lights){lights_=lights;};

private:
	Point point_;
	Vector normal_;
	Vector incoming_;
	Vector reflective_;
  Vector viewing_;
  Light light_;
//	std::list<Light*> lights_;
};

#endif
