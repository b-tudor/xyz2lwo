#include "Cube.h"





Cube::Cube( Vector3D R, double radius ) {
	
	const double r = radius;
	
	// Start with a trigonal bipyramid where each point is 1 unit from the origin,
	// and recursively tesselate each face, depth times to create our sphere. If
	// we tesselate to depth 1, the result is the starting geometry below: a triangular
	// bipyramid (a little diamond shape with six faces). 
	Vector3D A( -r,  r,  r );
	Vector3D B(  r,  r,  r );
	Vector3D C( -r, -r,  r );
	Vector3D D(  r, -r,  r );
	Vector3D E( -r,  r, -r );
	Vector3D F(  r,  r, -r );
	Vector3D G( -r, -r, -r );
	Vector3D H(  r, -r, -r );
	
	int idx_A = addPoint(A);
	int idx_B = addPoint(B);
	int idx_C = addPoint(C);
	int idx_D = addPoint(D);
	int idx_E = addPoint(E);
	int idx_F = addPoint(F);
	int idx_G = addPoint(G);
	int idx_H = addPoint(H);

	for (auto& pos : points) {
		pos += R;
	}

	addFace( idx_C, idx_D, idx_B, idx_A );
	addFace( idx_E, idx_F, idx_H, idx_G );
	addFace( idx_A, idx_B, idx_F, idx_E );
	addFace( idx_G, idx_H, idx_D, idx_C );
	addFace( idx_A, idx_E, idx_G, idx_C );
	addFace( idx_D, idx_H, idx_F, idx_B );
}



Cube::~Cube() { }





int Cube::addPoint( Vector3D p )
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



void Cube::addFace(int idx_A, int idx_B, int idx_C, int idx_D)
{
	Object3D::Face f;
	f.vertex_count = 4;
	f.vertex[0] = idx_A;
	f.vertex[1] = idx_B;
	f.vertex[2] = idx_C;
	f.vertex[3] = idx_D;
	faces.push_back(f);
}