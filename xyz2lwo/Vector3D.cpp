#include "Vector3D.h"
#include <iomanip>
#include <sstream>
#ifdef INCLUDE_RANDOMIZER
#include "Rando.h"
#endif

// DESTRUCTOR + CONSTRUCTORS
Vector3D::~Vector3D() { }
Vector3D::Vector3D() { r[0] = r[1] = r[2] = 0.0; }
Vector3D::Vector3D(double x, double y, double z)
{
	r[0] = x;
	r[1] = y;
	r[2] = z;
}


// PUBLIC METHODS

void Vector3D::set(double x, double y, double z)
{
	r[0] = x;
	r[1] = y;
	r[2] = z;
}


void Vector3D::normalize() {

	double mag = norm();

	if (mag) {
		r[0] = r[0] / mag;
		r[1] = r[1] / mag;
		r[2] = r[2] / mag;
	}
	else
		r[0] = r[1] = r[2] = 0;
}


Vector3D& Vector3D::operator=(const Vector3D& rhs) {
	if (this != &rhs) {
		this->r[0] = rhs.x();
		this->r[1] = rhs.y();
		this->r[2] = rhs.z();
	}

	return *this;
}


Vector3D& Vector3D::operator=(const double rhs) {
	this->r[0] = rhs;
	this->r[1] = rhs;
	this->r[2] = rhs;

	return (*this);
}


bool Vector3D::equals(const Vector3D& rhs, double threshold) {

	if (distance2(*this, rhs) <= (threshold * threshold))
		return true;
	return false;
}


// Addition
Vector3D& Vector3D::operator+=(const Vector3D& rhs) {
	this->r[0] = this->r[0] + rhs.x();
	this->r[1] = this->r[1] + rhs.y();
	this->r[2] = this->r[2] + rhs.z();

	return (*this);
}


// Subtraction
Vector3D& Vector3D::operator-=(const Vector3D& rhs) {
	this->r[0] = this->r[0] - rhs.x();
	this->r[1] = this->r[1] - rhs.y();
	this->r[2] = this->r[2] - rhs.z();
	return (*this);
}


// vector * scalar
Vector3D& Vector3D::operator*=(const double scalar) {
	this->r[0] *= scalar;
	this->r[1] *= scalar;
	this->r[2] *= scalar;
	return (*this);
}
Vector3D& Vector3D::operator/=(const double scalar) {
	this->r[0] /= scalar;
	this->r[1] /= scalar;
	this->r[2] /= scalar;
	return (*this);
}
// scalar * vector  (non-member function)
Vector3D operator*(const double d, const Vector3D rhs) {
	return Vector3D(d * rhs.x(), d * rhs.y(), d * rhs.z());
}


// Squared Distance between i & j
double Vector3D::distance2(const Vector3D i, const Vector3D j) {
	double A2 = i.x() - j.x();
	A2 = A2 * A2;
	double B2 = i.y() - j.y();
	B2 = B2 * B2;
	double C2 = i.z() - j.z();
	C2 = C2 * C2;

	return A2 + B2 + C2;
}





// OUTPUT METHODS

std::string Vector3D::xyzOut(std::string symbol) {
	using namespace std;
	stringstream out;
	out << left << setw(5) << symbol << right;
	out << fixed << setprecision(6);
	out << setw(10) << x()
		<< setw(10) << y()
		<< setw(10) << z();

	return out.str();
}


std::ostream& operator<<(std::ostream& os, const Vector3D& rhs)
{
	os << "(" << rhs.x() << ", " << rhs.y() << ", " << rhs.z() << ")";
	return os;
}





#ifdef INCLUDE_RANDOMIZER
// Create a unit vector that points randomly to a point on the surface of a unit sphere
void Vector3D::randomize() {
	r[0] = Rando::rand_normal();
	r[1] = Rando::rand_normal();
	r[2] = Rando::rand_normal();
	normalize();
}
#endif