/*  Brant Tudor
 *  (c) 2019
 *  Vector Class to represent a three dimensional Cartesian coordinate vector
 *  along with common operations associated with these objects.
 */

#pragma once
#ifndef VECTOR_3D_H
#define	VECTOR_3D_H
#include <iostream>
#include <string>
#include <cmath>
 // The randomizer function will create a vector whose point lies on the surface of a unit
 // sphere. To use this function, uncomment the following line and include the Rando RNG
 // wrapper found at (or substitute your own, but to get an even distribution of points 
 // across the surface of the unit sphere make sure the random numbers are selected from
 // a normal distribution): https://github.com/b-tudor/Rando
 // #define INCLUDE_RANDOMIZER
 /*
	 CONSTRUCTORS/DESTRUCTORS
	 Vector3D();
	 Vector3D(double x, double y, double z);
	 ~Vector3D(void);
	 GETTERS/SETTERS
	 void set(double x, double y, double z);
	 void setX(double x)
	 void setY(double y)
	 void setZ(double z)
	 inline double x() const
	 inline double y() const
	 inline double z() const
	 double & operator[]                                     fast, loop-friendly access to the vector components
	 inline double R(const size_t i) const                   slower, bounds-checked read-only access
	 OPERATORS SUPPORTED

	 ostream& operator<< (ostream& os, const Vector3D& v)    stream output
	 Vector3D & operator=(const Vector3D &rhs);              vector vector assignment
	 Vector3D & operator=(const double rhs);                 assign all components of a vector the same scalar
	 bool operator==(const Vector3D &rhs);                   EXACT (floating point rep) equality comparator
	 bool equals(const Vector3D &rhs, double threshold);     equality comparator that uses an accuracy threshold
	 Vector3D & operator+=(const Vector3D &rhs);             Addition
	 inline const Vector3D operator+(const Vector3D &rhs);
	 Vector3D & operator-=(const Vector3D &rhs) const;       Subtraction
	 const Vector3D operator-(const Vector3D &rhs) const
	 inline double operator*(const Vector3D &rhs) const      Dot product
	 inline Vector3D cross(const Vector3D &rhs) const        Cross product
	 inline Vector3D operator*(const double rhs) const       Scalar * vector     (vector scaling)
	 inline Vector3D operator/(const double rhs) const       Division by scalar  (vector scaling)
	 OTHER OPERATIONS
	 inline double norm ()                     length of vector
	 inline double norm2()                     norm() squared
	 double distance()                         distance between to (position) vectors
	 double distance2()                        distance() squared
	 void randomize()                          changes Vector into  a random unit vector, selected from a uniform
												 distribution across the surface of a unit sphere
	 OUTPUT
	 std::string xyzOut(std::string symbol)    returns a string suitable for inclusion in an xyz file
 */



class Vector3D
{
public:

	// Data
	double r[3];

	// Methods

	Vector3D();
	Vector3D(double x, double y, double z);
	~Vector3D(void);

	void set(double x, double y, double z);
	void setX(double x) { r[0] = x; }
	void setY(double y) { r[1] = y; }
	void setZ(double z) { r[2] = z; }
	inline double x() const { return r[0]; }
	inline double y() const { return r[1]; }
	inline double z() const { return r[2]; }
	// Faster read/write access w no bounds-checking:
	inline double& operator[](const size_t i) { return r[i]; }
	// Safer, slower, bounds-checked READ-ONLY access (fouled numerical results MAY indicate out-of-bounds
	// index condition, but out-of-bounds array access attempts will not seg fault [at least not here]):
	inline double R(const size_t i) const { return (i >= 0 && i < 3) ? r[i] : NAN; }

	friend std::ostream& operator<<(std::ostream& os, Vector3D& v);

	void normalize();


	Vector3D& operator=(const Vector3D& rhs);
	Vector3D& operator=(const double rhs);

	bool operator==(const Vector3D& rhs) {
		return  (this->x() == rhs.x()) && (this->y() == rhs.y()) && (this->z() == rhs.z());
	}
	bool equals(const Vector3D& rhs, double threshold);

	// Addition
	Vector3D& operator+=(const Vector3D& rhs);
	inline const Vector3D operator+(const Vector3D& rhs) const {
		return Vector3D(*this) += rhs;
	}
	// Subtraction
	Vector3D& operator-=(const Vector3D& rhs);
	const Vector3D operator-(const Vector3D& rhs) const {
		return Vector3D(*this) -= rhs;
	}


	// vector * scalar
	Vector3D& operator*=(const double scalar);
	Vector3D& operator/=(const double scalar);
	inline Vector3D operator*(const double  rhs) const {
		return Vector3D(this->x() * rhs, this->y() * rhs, this->z() * rhs);
	}
	inline Vector3D operator/(const double  rhs) const {
		return Vector3D(this->x() / rhs, this->y() / rhs, this->z() / rhs);
	}
	// -1 * vector
	Vector3D operator-() const { return Vector3D(-x(), -y(), -z()); }
	// scalar * vector
	friend Vector3D operator*(const double lhs, Vector3D rhs);

	// Dot (scalar) Product
	inline double operator*(const Vector3D& rhs) const {
		return this->x() * rhs.x() + this->y() * rhs.y() + this->z() * rhs.z();
	}

	// Cross (vector) product
	inline Vector3D cross(const Vector3D& rhs) const {
		return Vector3D(
			this->y() * rhs.z() - this->z() * rhs.y(),
			this->z() * rhs.x() - this->x() * rhs.z(),
			this->x() * rhs.y() - this->y() * rhs.x()
		);
	}


	// vector length
	inline double norm() { return sqrt(norm2()); }
	inline double norm2() { return ((*this) * (*this)); }


	// distance between vectors (or the positions they represent
	static double distance2(const Vector3D r1, const Vector3D r2);
	inline static double distance(const Vector3D r1, const Vector3D r2) { return sqrt(distance2(r1, r2)); }


	// generate a string suitable for inclusion in an .xyz formatted file, with given Chemical symbol 'symbol' (e.g. C, H, O, Ag, Fe, Cu)
	std::string xyzOut(std::string symbol);


#ifdef INCLUDE_RANDOMIZER
	// convert to randomly oriented unit vector
	void randomize();
#endif




};

#endif	// VECTOR3D_H