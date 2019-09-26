#pragma once
#include "Vector3D.h"
#include "IFF.h"




class Tube
{
public:
	
	Tube( Vector3D rA, Vector3D rB, double radius, int sides );
	~Tube();

	std::vector<Vector3D> points;
	std::vector<IFF::Face> faces;
	
	std::vector<Vector3D>  *point_data() { return &points; }
	std::vector<IFF::Face> * face_data() { return &faces;  }

private:

	int addPoint(Vector3D p);

};

