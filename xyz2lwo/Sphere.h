#pragma once
#include "Vector3D.h"
#include "IFF.h"




class Sphere
{
public:

	const int maxDepth = 10;


	Sphere( Vector3D r, double radius, int depth );
	~Sphere();

	std::vector<Vector3D> points;
	std::vector<IFF::Face> faces;
	
	std::vector<Vector3D>  *point_data() { return &points; }
	std::vector<IFF::Face> * face_data() { return &faces;  }

private:

	void tessellate( int depth, int index_A, int index_B, int index_C );

	int addPoint(Vector3D p);

};

