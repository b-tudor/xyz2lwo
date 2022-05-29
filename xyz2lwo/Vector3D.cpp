#include "Vector3D.h"
#include <iomanip>
#include <sstream>
#ifdef INCLUDE_RANDOMIZER
#include "Rando.h"
#endif

Vector3D::~Vector3D() { }
Vector3D::Vector3D() :X(0), Y(0), Z(0) {}
Vector3D::Vector3D(double x, double y, double z)
{
	X = x;
	Y = y;
	Z = z;
}




void Vector3D::set(double x, double y, double z)
{
	X = x;
	Y = y;
	Z = z;
}


void Vector3D::normalize() {
	double mag = norm();
	if (mag != 0) {
		X = X / mag;
		Y = Y / mag;
		Z = Z / mag;
	}
	else
		X = Y = Z = 0;
}


Vector3D& Vector3D::operator=(const Vector3D& rhs) {
	if (this != &rhs) {
		this->X = rhs.x();
		this->Y = rhs.y();
		this->Z = rhs.z();
	}

	return *this;
}


Vector3D& Vector3D::operator=(const double rhs) {
	this->X = rhs;
	this->Y = rhs;
	this->Z = rhs;

	return *this;
}


bool Vector3D::equals(const Vector3D& rhs, double threshold) {

	if (distance2(*this, rhs) <= (threshold * threshold))
		return true;
	return false;
}


// Addition
Vector3D& Vector3D::operator+=(const Vector3D& rhs) {
	this->X = this->X + rhs.x();
	this->Y = this->Y + rhs.y();
	this->Z = this->Z + rhs.z();

	return *this;
}


// Subtraction
Vector3D& Vector3D::operator-=(const Vector3D& rhs) {
	this->X = this->X - rhs.x();
	this->Y = this->Y - rhs.y();
	this->Z = this->Z - rhs.z();

	return *this;
}


// vector * scalar
Vector3D& Vector3D::operator*=(const double scalar) {
	this->X *= scalar;
	this->Y *= scalar;
	this->Z *= scalar;
	return (*this);
}
Vector3D& Vector3D::operator/=(const double scalar) {
	this->X /= scalar;
	this->Y /= scalar;
	this->Z /= scalar;
	return (*this);
}
// scalar * vector  (non-member function)
Vector3D operator*(const double d, const Vector3D rhs) {
	return Vector3D(d * rhs.x(), d * rhs.y(), d * rhs.z());
}


// Squared Distance between i & j
double Vector3D::distance2(const Vector3D i, const Vector3D j) {
	double A = i.x() - j.x();
	double B = i.y() - j.y();
	double C = i.z() - j.z();
	return A * A + B * B + C * C;
}



std::string Vector3D::xyzOut(std::string symbol) {
	using namespace std;
	stringstream out;
	out << left << setw(5) << symbol << right;
	out << fixed << setprecision(5);
	out << setw(10) << X
		<< setw(10) << Y
		<< setw(10) << Z;

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