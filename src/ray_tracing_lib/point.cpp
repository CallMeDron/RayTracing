#include "point.h"
#include "line.h"

namespace NRayTracingLib {

TPoint::TPoint() : X(0), Y(0), Z(0) {}
TPoint::TPoint(TSafeDouble x, TSafeDouble y, TSafeDouble z) : X(x), Y(y), Z(z) {}

bool TPoint::operator==(const TPoint& other) const noexcept {
    return (X == other.X) && (Y == other.Y) && (Z == other.Z);
}
bool TPoint::operator!=(const TPoint& other) const noexcept { return !(*this == other); }

TVector TPoint::operator-(const TPoint& other) const noexcept { return TVector{X - other.X, Y - other.Y, Z - other.Z}; }
TPoint TPoint::operator+(const TVector& vector) const noexcept {
    return TPoint{X + vector.X, Y + vector.Y, Z + vector.Z};
}

std::ostream& operator<<(std::ostream& os, const TPoint& point) {
    return os << "point = {" << point.X << ", " << point.Y << ", " << point.Z << "}\n";
}

void TPoint::print() const { std::cout << *this; }

TSafeDouble TPoint::distToPoint(const TPoint& point) const noexcept {
    return ((X - point.X).pow(2) + (Y - point.Y).pow(2) + (Z - point.Z).pow(2)).pow(0.5);
}
TSafeDouble TPoint::distToLine(const TLine& line) const noexcept { return line.distToPoint(*this); }

} // namespace NRayTracingLib