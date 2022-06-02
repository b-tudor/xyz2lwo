/*  Brant Tudor
 *  (c) 2019
 *  Vector Class to represent a three dimensional Cartesian coordinate vector
 *  along with common operations associated with these objects. 
 */

#pragma once
#ifndef VECTOR_3D_H
#define	VECTOR_3D_H
#include <string>
#include <cmath>
// The randomizer function will create a vector whose point lies on the surface of
// a unit sphere. To use this function, uncomment the following line and include 
// the Rando class found at: https://github.com/b-tudor/Rando
// #define INCLUDE_RANDOMIZER
/*

	CONSTRUCTORS/DESTRUCTORS

	Vector3D();
	Vector3D(double x, double y, double z);
	~Vector3D(void);



	GETTERS/SETTERS

	void set(double x, double y, double z);
	void setX(double x) { X = x; }
	void setY(double y) { Y = y; }
	void setZ(double z) { Z = z; }
	inline double x() const { return X; }
	inline double y() const { return Y; }
	inline double z() const { return Z; }



	OPERATORS SUPPORTED

	Vector3D & operator=(const Vector3D &rhs);              vector vector assignment
	Vector3D & operator=(const double rhs);                 assign all components of a vector the same scalar
	bool operator==(const Vector3D &rhs);                   exact equality comparator
	bool equals(const Vector3D &rhs, double threshold);     equality comparator with an accuracy threshold
	Vector3D & operator+=(const Vector3D &rhs);             Addition
	inline const Vector3D operator+(const Vector3D &rhs);
	Vector3D & operator-=(const Vector3D &rhs) const;       Subtraction
	const Vector3D operator-(const Vector3D &rhs) const
	inline double operator*(const Vector3D &rhs) const      Dot product
	inline Vector3D cross(const Vector3D &rhs) const        Cross product
	inline Vector3D operator*(const double  rhs) const      Scalar x vector
	inline Vector3D operator/(const double  rhs) const      Division by scalar


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
	Vector3D();
	Vector3D(double x, double y, double z);
	~Vector3D(void);

	void set(double x, double y, double z);
	void setX(double x) { e[0] = x; }
	void setY(double y) { e[1] = y; }
	void setZ(double z) { e[2] = z; }
	// fast element access w/o bounds checking
	inline double operator[](int i) { return e[i]; }
	// safer element access, w bounds checking 
	inline double access(int i) { return ((i >= 0) && (i<3)) ? e[i] : NAN;}
	inline double x() const { return e[0]; }
	inline double y() const { return e[1]; }
	inline double z() const { return e[2]; }

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
	Vector3D operator-() const { return Vector3D(-e[0], -e[1], -e[2]); }
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
	

	// generate a string suitable for inclusion in a .xyz formatted file, with given Chemical symbol 'symbol' (e.g. C, H, O, Ag, Fe, Cu)
	std::string xyzOut(std::string symbol);


	#ifdef INCLUDE_RANDOMIZER
		// convert to randomly oriented unit vector
		void randomize();
	#endif


private:
	double e[3];
};

#endif	// VECTOR3D_H
