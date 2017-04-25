#pragma once
#include "optimizer/geometry.h"
//!  Class providing basic 2D airfoil geometry representation
/*!
  A more elaborate class description. [TODO]
*/
class Genome
{
public:
	Genome(Geometry &geometry) :
		_geom(geometry)
	{}
private:
	Geometry _geom;
};
