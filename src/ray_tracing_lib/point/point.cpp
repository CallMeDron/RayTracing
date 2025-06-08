#include "point.h"

#include <iomanip>

namespace NRayTracingLib {

TPoint::TPoint(TSafeDouble x, TSafeDouble y, TSafeDouble z) : X(x), Y(y), Z(z) {}

bool TPoint::operator==(const TPoint& other) const { return (X == other.X) && (Y == other.Y) && (Z == other.Z); }
bool TPoint::operator!=(const TPoint& other) const { return !(*this == other); }

TVector TPoint::operator-(const TPoint& other) const { return TVector{X - other.X, Y - other.Y, Z - other.Z}; }
TPoint TPoint::operator+(const TVector& vector) const { return TPoint{X + vector.X, Y + vector.Y, Z + vector.Z}; }

std::ostream& operator<<(std::ostream& os, const TPoint& point) {
    return os << "point = {" << point.X << ", " << point.Y << ", " << point.Z << "}\n";
}

void TPoint::print() const { std::cout << *this; }

} // namespace NRayTracingLib