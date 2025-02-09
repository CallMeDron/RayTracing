#include "point.h"

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

TPoint::TPoint() : X(0.0), Y(0.0), Z(0.0) {}
TPoint::TPoint(TSafeDouble x, TSafeDouble y, TSafeDouble z) : X(x), Y(y), Z(z) {}

bool TPoint::operator==(const TPoint& other) const { return isEqual<TPoint>(*this, other); }
bool TPoint::operator!=(const TPoint& other) const { return !isEqual<TPoint>(*this, other); }

TVector TPoint::operator-(const TPoint& other) const { return TVector{X - other.X, Y - other.Y, Z - other.Z}; }

std::ostream& operator<<(std::ostream& os, const TPoint& point) {
  std::cout << std::scientific;
  std::cout << std::setprecision(1);
  return os << "point = {" << point.X << ", " << point.Y << ", " << point.Z << "}\n";
}

void TPoint::print() { std::cout << *this; }

} // namespace NGeometry3D