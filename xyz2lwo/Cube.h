#pragma once
#include "Object3D.h"
#include "Vector3D.h"





class Cube : public Object3D
{
public:

	const int maxDepth = 10;


	Cube( Vector3D r, double radius );
	~Cube();

private:

	//void tessellate( int depth, int index_A, int index_B, int index_C );

	int addPoint(Vector3D p);
	void addFace( int idx_A, int idx_B, int idx_C, int idx_D );

};

