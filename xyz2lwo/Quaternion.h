/*  Quaternion C++ Class (Header)
 *  https://github.com/b-tudor/Quaternion
 * 
 *  CONSTRUCTORS
 *    Quaternion() - creates a 0'd out quaternion
 *    Quaternion(x,y,z,w) - creates a quaternion with literal values x, y, z & w
 *    Quaternion(x,y,z,w,units) - creates a quaternion that represents a rotation of w units about axis (x,y,z)
 *                                units are specified as Quaternion::RADIANS or Quaternion::DEGREES
 *    Quaternion( Vector3D v)   - creates a quaternion that can be used to respresent a normal 3D vector (w is set to 0)
 *    Quaternion( Vector3D v, w, units) - creates a quaternion that represents a rotation of w units about axis v
 *                                        units are specified as Quaternion::RADIANS or Quaternion::DEGREES
 *
 *
 *  GETTERS
 *    x(), y(), z(), w() - returns the x, y, z & w components of the quaternion
 *
 *
 *  SUPPORTED OPERATIONS
 *     multiplication (quaternion * quaternion)
 *     assignment quaternion = quaternion
 *
 *
 *  METHODS
 *    normalize() - scales quaternion so that it has length of 1
 *    conjugate() - returns the conjugate quaternion of THIS vector
 *    rotate( Vector3D r ) - rotates r according to the rotation specified by THIS quaternion
 */

#pragma once
#ifndef QUATERNION_H
#define QUATERNION_H

// Certain functions rely on the Vector3D class located at:
// https://github.com/b-tudor/Vector3D.git
#include "Vector3D.h"


class Quaternion
{
public:
	enum class AngleMode { RADIANS, DEGREES };

	Quaternion();
	Quaternion(double x, double y, double z, double w);
	Quaternion( double x, double y, double z, double w, AngleMode units );
	Quaternion(Vector3D v);
	Quaternion(Vector3D v, double angle, AngleMode units );
	~Quaternion();

	

	void normalize();
	Quaternion  operator*( const Quaternion &rhs );
	Quaternion& operator=( const Quaternion &rhs );
	Quaternion  conjugate();
	Vector3D rotate(const Vector3D &rotatee);

	inline double x() { return X; }
	inline double y() { return Y; }
	inline double z() { return Z; }
	inline double w() { return W; }

	

private:
	double X, Y, Z, W;
  
};


#endif  // QUATERNION_H