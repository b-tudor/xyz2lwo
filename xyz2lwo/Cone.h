#pragma once
#include "Object3D.h"
#include "Vector3D.h"





class Cone : public Object3D
{
public:

	Cone( Vector3D r, double radius, int nSides );
	~Cone();

private:

	int addPoint(Vector3D p);
	void addFace( int idx_A, int idx_B, int idx_C, int idx_D );

};

