#include "Quaternion.h"
#include <cmath>


Quaternion::Quaternion(): X(0), Y(0), Z(0), W(0) {}
Quaternion::Quaternion(double x, double y, double z, double w): X(x), Y(y), Z(z), W(w) {}
Quaternion::Quaternion( double x, double y, double z, double w, AngleMeasureMode units ) {

	double angle     = w;
	double sinAngle  = 0,
	       magnitude = 0;

	switch( units ) {

		case DEGREES:  // Construct a quaternion from a rotation axis and a rotation angle (in degress)
			angle /= 57.2957795; // Convert angle from degrees to radians, prior to the normal AXIS_ANGLE_RADIAN treatment (below)
		case RADIANS:  // Construct quaternion from an axis and an angle (in radians)
			
			// Normalizes the axis vector
			magnitude = sqrt( x*x + y*y + z*z );

			// Edge case, if the axis to rotate around doesn't exist just return a quaternion with no rotation
			if( magnitude == 0.0 ) {
				this->X = 0;
				this->Y = 0;
				this->Z = 0;
				this->W = 1;
				return;
			}

			x = x/magnitude;
			y = y/magnitude;
			z = z/magnitude;

			sinAngle = sin(angle/2.0);
		
			this->X=  x*sinAngle;
			this->Y = y*sinAngle;
			this->Z = z*sinAngle;
			this->W = cos(angle/2.0);
			break;


		default:
			throw "Quaternion: Invalid units specified for the constructor angle.";
			break;
	}
}
Quaternion::Quaternion(Vector3D v, double w, AngleMeasureMode units ) {
	double angle = w;
	double sinAngle = 0;
	double magnitude = 0;
	double x = v.x();
	double y = v.y();
	double z = v.z();

	switch (units) {

	case DEGREES:  // Construct a quaternion from a rotation axis and a rotation angle (in degress)
		angle /= 57.2957795; // Convert angle from degrees to radians, prior to the normal AXIS_ANGLE_RADIAN treatment (below)
	case RADIANS:  // Construct quaternion from an axis and an angle (in radians)

		// Normalizes the axis vector
		magnitude = sqrt(x*x + y * y + z * z);

		// Edge case, if the axis to rotate around doesn't exist just return a quaternion with no rotation
		if (magnitude == 0.0) {
			this->X = 0;
			this->Y = 0;
			this->Z = 0;
			this->W = 1;
			return;
		}

		x = x / magnitude;
		y = y / magnitude;
		z = z / magnitude;

		sinAngle = sin(angle / 2.0);

		this->X = x * sinAngle;
		this->Y = y * sinAngle;
		this->Z = z * sinAngle;
		this->W = cos(angle / 2.0);
		break;

	default:
		throw "Quaternion: Invalid units specified for the constructor angle.";
		break;
	}
}
Quaternion::Quaternion(Vector3D v) {
	X = v.x();
	Y = v.y();
	Z = v.z();
	W = 0;
}

Quaternion::~Quaternion()
{}


// Normalize quaternion
void Quaternion::normalize()
{
	double magnitude = sqrt( X*X + Y*Y + Z*Z + W*W );
	X = X/magnitude;
	Y = Y/magnitude;
	Z = Z/magnitude;
	W = W/magnitude;
}

Quaternion& Quaternion::operator=(const Quaternion &rhs)
{
	if( &rhs != this ) {  // Avoids self assignment
		X = rhs.X;
		Y = rhs.Y;
		Z = rhs.Z;
		W = rhs.W;
	}
	return *this; // allows chaining, i.e. x = y = z;
}


// QuaternionStore = Q1 * Q2
// Order matters!
Quaternion Quaternion::operator*( const Quaternion &rhs )
{
  double result_w = W*rhs.W - X*rhs.X - Y*rhs.Y - Z*rhs.Z;
  double result_x = W*rhs.X + X*rhs.W + Y*rhs.Z - Z*rhs.Y;
  double result_y = W*rhs.Y - X*rhs.Z + Y*rhs.W + Z*rhs.X;
  double result_z = W*rhs.Z + X*rhs.Y - Y*rhs.X + Z*rhs.W;
  
  return Quaternion( result_x, result_y, result_z, result_w );
}


// A conjugate quaternion performs the opposite rotation
Quaternion Quaternion::conjugate() {
	return Quaternion( -X, -Y, -Z, W );
}


Vector3D Quaternion::rotate(const Vector3D &rotatee) {
	Quaternion r(rotatee);
	Quaternion newR = (*this) * r * this->conjugate();
	return Vector3D(newR.x(), newR.y(), newR.z());
}