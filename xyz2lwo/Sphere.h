#pragma once
#include "Object3D.h"
#include "Vector3D.h"





class Sphere : public Object3D
{
public:

	const int maxDepth = 10;


	Sphere( Vector3D r, double radius, int depth );
	~Sphere();

private:

	void tessellate( int depth, int index_A, int index_B, int index_C );

	int addPoint(Vector3D p);

};

