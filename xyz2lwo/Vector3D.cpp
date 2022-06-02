#include "Vector3D.h"
#include <iomanip>
#include <sstream>
#ifdef INCLUDE_RANDOMIZER
#include "Rando.h"
#endif

Vector3D::~Vector3D() { }
Vector3D::Vector3D() { e[0] = e[1] = e[2] = 0.0; }
Vector3D::Vector3D(double x, double y, double z)
{
	e[0] = x;
	e[1] = y;
	e[2] = z;
}




void Vector3D::set(double x, double y, double z)
{
	e[0] = x;
	e[1] = y;
	e[2] = z;
}


void Vector3D::normalize() {

	double mag = norm();
	
	if (mag != 0) {
		e[0] = e[0] / mag;
		e[1] = e[1] / mag;
		e[2] = e[2] / mag;
	}
	else
		e[0] = e[1] = e[2] = 0.0;
}


Vector3D& Vector3D::operator=(const Vector3D& rhs) {
	if (this != &rhs) {
		this->e[0] = rhs.x();
		this->e[1] = rhs.y();
		this->e[2] = rhs.z();
	}

	return *this;
}


Vector3D& Vector3D::operator=(const double rhs) {
	this->e[0] = rhs;
	this->e[1] = rhs;
	this->e[2] = rhs;

	return *this;
}


bool Vector3D::equals(const Vector3D& rhs, double threshold) {

	if (distance2(*this, rhs) <= (threshold * threshold))
		return true;
	return false;
}


// Addition
Vector3D& Vector3D::operator+=(const Vector3D& rhs) {
	this->e[0] = this->e[0] + rhs.x();
	this->e[1] = this->e[1] + rhs.y();
	this->e[2] = this->e[2] + rhs.z();

	return *this;
}


// Subtraction
Vector3D& Vector3D::operator-=(const Vector3D& rhs) {
	this->e[0] = this->e[0] - rhs.x();
	this->e[1] = this->e[1] - rhs.y();
	this->e[2] = this->e[2] - rhs.z();

	return *this;
}


// vector * scalar
Vector3D& Vector3D::operator*=(const double scalar) {
	this->e[0] *= scalar;
	this->e[1] *= scalar;
	this->e[2] *= scalar;
	return (*this);
}
Vector3D& Vector3D::operator/=(const double scalar) {
	this->e[0] /= scalar;
	this->e[1] /= scalar;
	this->e[2] /= scalar;
	return (*this);
}
// scalar * vector  (non-member function)
Vector3D operator*(const double d, const Vector3D rhs) {
	return Vector3D(d * rhs.x(), d * rhs.y(), d * rhs.z());
}


// Squared Distance between i & j
double Vector3D::distance2(const Vector3D i, const Vector3D j) {
	
	double A = i.x() - j.x();
	A = A*A;

	double B = i.y() - j.y();
	B = B*B;

	double C = i.z() - j.z();
	C = C*C;

	return A + B + C;
}



std::string Vector3D::xyzOut(std::string symbol) {
	using namespace std;
	stringstream out;
	out << left << setw(5) << symbol << right;
	out << fixed << setprecision(5);
	out << setw(10) << e[0]
		<< setw(10) << e[1]
		<< setw(10) << e[2];

	return out.str();
}

#ifdef INCLUDE_RANDOMIZER
// Create a unit vector that points randomly to a point on the surface of a unit sphere
void Vector3D::randomize() {
	X = Rando::rand_normal();
	Y = Rando::rand_normal();
	Z = Rando::rand_normal();
	normalize();
}
#endif