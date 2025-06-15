#include "point.h"
#include "line.h"

namespace NRayTracingLib {

TPoint::TPoint() {}
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

TSafeDouble TPoint::distToPoint(const TPoint& point) const {
    return ((X - point.X).pow(2.0) + (Y - point.Y).pow(2.0) + (Z - point.Z).pow(2.0)).pow(0.5);
}
TSafeDouble TPoint::distToLine(const TLine& line) const { return line.distToPoint(*this); }

} // namespace NRayTracingLib

namespace std {

using namespace NRayTracingLib;

size_t hash<TPoint>::operator()(const TPoint& point) const {
    size_t seed = 0;
    const auto hashFunction = hash<int64_t>();
    for (const auto& arg : {point.X, point.Y, point.Z}) {
        int64_t rounded = static_cast<int64_t>(llround(arg.Value / (ACCURACY * 2)));
        seed ^= hashFunction(rounded) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

} // namespace std