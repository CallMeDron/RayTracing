#include "vector.h"

#include <iomanip>
#include <stdexcept>

namespace NGeometry3D {

template <typename T>
void initializeFrom(const T& other, TSafeDouble& x, TSafeDouble& y, TSafeDouble& z) {
  x = other.X;
  y = other.Y;
  z = other.Z;
}

template <typename T>
bool isEqual(const T& a, const T& b) {
  return (a.X == b.X) && (a.Y == b.Y) && (a.Z == b.Z);
}

TVector::TVector() : X(0.0), Y(0.0), Z(0.0) {}
TVector::TVector(TSafeDouble x, TSafeDouble y, TSafeDouble z) : X(x), Y(y), Z(z) {}

TVector::TVector(const TPoint& point) { initializeFrom(point, X, Y, Z); }

TVector::TVector(const TPoint& start, const TPoint& end) : TVector{end - start} {}

bool TVector::operator==(const TVector& other) const { return isEqual<TVector>(*this, other); }
bool TVector::operator!=(const TVector& other) const { return !isEqual<TVector>(*this, other); }

TVector TVector::operator+(const TVector& other) const { return TVector{X + other.X, Y + other.Y, Z + other.Z}; }
TVector TVector::operator-(const TVector& other) const { return TVector{X - other.X, Y - other.Y, Z - other.Z}; }

TVector TVector::operator*(TSafeDouble n) const { return TVector{X * n, Y * n, Z * n}; }
TVector TVector::operator/(TSafeDouble n) const { return TVector{X / n, Y / n, Z / n}; }

TVector& TVector::operator+=(const TVector& other) {
  *this = *this + other;
  return *this;
}
TVector& TVector::operator-=(const TVector& other) {
  *this = *this - other;
  return *this;
}
TVector& TVector::operator*=(TSafeDouble n) {
  *this = *this * n;
  return *this;
}
TVector& TVector::operator/=(TSafeDouble n) {
  *this = *this / n;
  return *this;
}

TSafeDouble TVector::operator*(const TVector& other) const { return X * other.X + Y * other.Y + Z * other.Z; }

TVector TVector::operator^(const TVector& other) const {
  return TVector{Y * other.Z - Z * other.Y, Z * other.X - X * other.Z, X * other.Y - Y * other.X};
}

TSafeDouble TVector::length() const { return std::sqrt(((X ^ 2) + (Y ^ 2) + (Z ^ 2)).Value); }

void TVector::normalize() { *this /= this->length(); }

TVector TVector::getNormalized() const {
  TVector normalized{*this};
  normalized.normalize();
  return normalized;
}

TSafeDouble TVector::cos(const TVector& other) const { return (*this * other) / length() / other.length(); }

bool TVector::isParallel(const TVector& other) const { return cos(other) == TSafeDouble{1.0}; }
bool TVector::isPerpendicular(const TVector& other) const { return cos(other) == TSafeDouble{0.0}; }

bool TVector::isZero() const { return X == TSafeDouble{0.0} && Y == TSafeDouble{0.0} && Z == TSafeDouble{0.0}; }

std::ostream& operator<<(std::ostream& os, const TVector& vector) {
  std::cout << std::scientific;
  std::cout << std::setprecision(1);
  return os << "vector = {" << vector.X << ", " << vector.Y << ", " << vector.Z << "}\n";
}

void TVector::print() { std::cout << *this; }

} // namespace NGeometry3D