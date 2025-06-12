#include "point.h"
#include "line.h"

namespace NRayTracingLib {

TPoint::TPoint() : X(0.0), Y(0.0), Z(0.0) {}
TPoint::TPoint(TSafeDouble x, TSafeDouble y, TSafeDouble z) : X(x), Y(y), Z(z) {}
TPoint::TPoint(const TVector& vector) : X(vector.X), Y(vector.Y), Z(vector.Z) {}

bool TPoint::operator==(const TPoint& other) const { return (X == other.X) && (Y == other.Y) && (Z == other.Z); }
bool TPoint::operator!=(const TPoint& other) const { return !(*this == other); }

TVector TPoint::operator-(const TPoint& other) const { return TVector{X - other.X, Y - other.Y, Z - other.Z}; }
TPoint TPoint::operator+(const TVector& vector) const { return TPoint{X + vector.X, Y + vector.Y, Z + vector.Z}; }

bool TPoint::operator<(const TPoint& other) const {
    if (X != other.X) {
        return X < other.X;
    }
    if (Y != other.Y) {
        return Y < other.Y;
    }
    return Z < other.Z;
}

std::ostream& operator<<(std::ostream& os, const TPoint& point) {
    return os << "point = {" << point.X << ", " << point.Y << ", " << point.Z << "}\n";
}
void TPoint::print() const { std::cout << *this; }

TSafeDouble TPoint::distToPoint(const TPoint& point) const {
    return ((X - point.X).pow(2.0) + (Y - point.Y).pow(2.0) + (Z - point.Z).pow(2.0)).pow(0.5);
}
TSafeDouble TPoint::distToLine(const TLine& line) const { return line.distToPoint(*this); }

} // namespace NRayTracingLib