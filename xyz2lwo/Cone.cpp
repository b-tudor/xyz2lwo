#include "Cone.h"

#include <math.h>



Cone::~Cone() { }
Cone:: Cone( Vector3D R, double radius, int nSides ) 
{
	
	const double r = radius;
	const double PI = 3.141592653589793238462643383279;
	const double increment = 2.0 * PI / nSides;

	Vector3D    O( 0, 0, 0 );
	Vector3D Apex( 0, 0, r );
	int idx_O = addPoint(O);
	int idx_A = addPoint(Apex);

	std::vector<int> circumPts;
	nSides = (nSides<3) ? 3 : nSides;
	 
	for( int i=0; i<nSides; i++ ) {
		double angle = increment * i;
		double x = cos(angle) * r;
		double y = sin(angle) * r;
		Vector3D p(x,y,0);
		// Add the point and log its index 
		circumPts.push_back( addPoint(p) );
	}
	

	for( int i=1; i<nSides; i++) {
		addFace( idx_A, circumPts[i], circumPts[i-1]);
		addFace()
	}
	
	
	for (auto& pos : points) {
		pos += R;
	}

	//addFace( idx_C, idx_D, idx_B, idx_A );
	//addFace( idx_E, idx_F, idx_H, idx_G );
	//addFace( idx_A, idx_B, idx_F, idx_E );
	//addFace( idx_G, idx_H, idx_D, idx_C );
	//addFace( idx_A, idx_E, idx_G, idx_C );
	//addFace( idx_D, idx_H, idx_F, idx_B );
}



int Cone::addPoint( Vector3D p )
// addPoint() returns the index where 'point' was found in the point list--or if it had to 
// be added--it returns the index at which it was.
{

	const double threshold = 0.0000000001;

	for (unsigned int i = 0; i < points.size(); i++) {
		if (p.equals(points[i], threshold))
			return i;
	}
	
	points.push_back(p);
	int idx = (int) points.size()-1;
	int idx2 = 0;

	for (unsigned int i = 0; i < points.size(); i++) {
		if (p==points[i])
			idx2 = i;
	}

	if (idx != idx2)
		throw - 1;
	else
		return idx;
}



void Cone::addFace(int idx_A, int idx_B, int idx_C)
{
	Object3D::Face f;
	f.vertex_count = 3;
	f.vertex[0] = idx_A;
	f.vertex[1] = idx_B;
	f.vertex[2] = idx_C;
	faces.push_back(f);
}