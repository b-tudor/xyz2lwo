#include "Tube.h"
#include "Quaternion.h"

#define _USE_MATH_DEFINES
#include <math.h>



Tube::Tube( Vector3D rA, Vector3D rB, double radius, int sides ) {
	
	Vector3D bond_vector = rB - rA;

	// Create some random vector so we can take a cross product with the bond vector and
	// construct a vector perpindicular to the bond vector (to act as the 12:00 point as
	// we rotate it about the bond axis in order to form the sides of the tube). 
	double perturb_X =  1.5 * bond_vector.x() - 2.0;
	double perturb_Y = -1.0 * bond_vector.y() + 1.0;
	double perturb_Z = -1.5 * bond_vector.z() + 2.0;
	Vector3D different_vector( perturb_X, perturb_Y, perturb_Z ); 
	Vector3D ortho_vector = bond_vector.cross(different_vector);
	
	// Scale said vector to the length of the tube radius
	ortho_vector.normalize();
	ortho_vector = radius * ortho_vector; 
	
	// create a quaternion that will rotate a point about the bond axis by the angle dictated by the side count
	double angle = (2.0 * M_PI) / (double) sides;
	Quaternion rotor(bond_vector, angle, Quaternion::AngleMode::RADIANS);
	
	int idx_limit = 2 * sides;

	for (int i = 0; i < sides; i++) {
		
		int two_i = 2 * i;
		Object3D::Face f;
		f.vertex_count = 4;
		f.vertex[0] = two_i;
		f.vertex[1] = (two_i + 2) % idx_limit;
		f.vertex[2] = (two_i + 3) % idx_limit;
		f.vertex[3] = two_i + 1;
		faces.push_back(f);

		points.push_back( rA + ortho_vector );
		points.push_back( rB + ortho_vector );
		ortho_vector = rotor.rotate(ortho_vector);
	}
}



Tube::~Tube() { }







int Tube::addPoint( Vector3D p )
// addPoint() returns the index where 'point' was found in the point list--or if it had to 
// be added--it returns the index at which it was.
{

	const double threshold = 0.000001;

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
		throw -1;
	else
		return idx;
}