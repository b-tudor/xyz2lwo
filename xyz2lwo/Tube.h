#pragma once
#include "Object3D.h"
#include "Vector3D.h"





class Tube : public Object3D
{
public:
	
	Tube( Vector3D rA, Vector3D rB, double radius, int sides );
	~Tube();

private:

	int addPoint(Vector3D p);

};

