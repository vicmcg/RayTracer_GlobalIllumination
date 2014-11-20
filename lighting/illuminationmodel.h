// Vic McGowen and Dan Goldberg
// Illumination class

#ifndef ILLUMINATIONMODEL_H_
#define ILLUMINATIONMODEL_H_

// Included Dependencies
#include <iostream>
#include "../aux/colour.h"
#include "../aux/intersectdata.h"
#include "../world/object.h"
#include "../texture/texture.h"

//Abstract IlluminationModel Class
class IlluminationModel{
public:
	IlluminationModel();// empty constructor
//	IlluminationModel(const IntersectData& intersect);
	virtual ~IlluminationModel();

//	virtual Colour illuminate() const;
  virtual Colour illuminate(const Object* o,const IntersectData& intersect);
/*
  virtual void setIntersectData(const IntersectData& intersect){intersect_=intersect;};
  virtual void setObject(const Object& object){object_=object;};
  virtual IntersectData getIntersectData() const {return intersect_;};
  virtual Object getObject() const {return object_;};


private:
	IntersectData intersect_;
  Object object_;
*/
};

#endif
