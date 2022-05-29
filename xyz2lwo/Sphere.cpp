#include "Sphere.h"
#include <algorithm>




Sphere::Sphere( Vector3D r, double radius, int depth ) {
	
	depth = (depth >= maxDepth) ? maxDepth : depth;

	// Start with a trigonal bipyramid where each point is 1 unit from the origin,
	// and recursively tesselate each face, depth times to create our sphere. If
	// we tesselate to depth 1, the result is the starting geometry below: a triangular
	// bipyramid (a little diamond shape with six faces). 
	Vector3D A( 0,   1,  0           );
	Vector3D B( 1,   0,  0           );
	Vector3D C(-0.5, 0, -0.866025404 );
	Vector3D D(-0.5, 0,  0.866025404 );
	Vector3D E( 0,  -1,  0           );
	
	int idx_A = addPoint(A);
	int idx_B = addPoint(B);
	int idx_C = addPoint(C);
	int idx_D = addPoint(D);
	int idx_E = addPoint(E);

	// Tessellate the top pyramid
	tessellate( depth, idx_A, idx_B, idx_C );
	tessellate( depth, idx_A, idx_C, idx_D );
	tessellate( depth, idx_A, idx_D, idx_B );

	// Tessellate the bottom pyramid
	tessellate( depth, idx_C, idx_B, idx_E );
	tessellate( depth, idx_D, idx_C, idx_E );
	tessellate( depth, idx_B, idx_D, idx_E );


	for (auto& pos : points) {
		pos *= radius;
		pos += r;
	}
}



Sphere::~Sphere() { }



void Sphere::tessellate(int depth, int idx_A, int idx_B, int idx_C) {
	
	if (depth <= 0) {
		IFF::Face f;
		f.vertex_count = 3;
		f.vertex[0] = idx_A;
		f.vertex[1] = idx_B;
		f.vertex[2] = idx_C;
		faces.push_back(f);
		return;
	}
		

	Vector3D A = points[idx_A];
	Vector3D B = points[idx_B];
	Vector3D C = points[idx_C];

	Vector3D D = 0.5 * (A + B);
	Vector3D E = 0.5 * (B + C);
	Vector3D F = 0.5 * (C + A);

	D.normalize();
	E.normalize();
	F.normalize();

	int idx_D = addPoint(D);
	int idx_E = addPoint(E);
	int idx_F = addPoint(F);


	tessellate( depth-1, idx_A, idx_D, idx_F );
	tessellate( depth-1, idx_F, idx_D, idx_E );
	tessellate( depth-1, idx_F, idx_E, idx_C );
	tessellate( depth-1, idx_D, idx_B, idx_E );
}



int Sphere::addPoint( Vector3D p )
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