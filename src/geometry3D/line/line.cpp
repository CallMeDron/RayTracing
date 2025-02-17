#include "line.h"

#include <iomanip>
#include <optional>

namespace NGeometry3D {

TLine::TLine(const TPoint& point1, const TPoint& point2) : Point1(point1), Point2(point2), Vector(point2 - point1) {
    if (Vector.isZero()) {
        throw std::runtime_error("Error: creating line by equal points");
    }
}
TLine::TLine(const TPoint& point, const TVector& vector) : Point1(point), Point2(point + vector), Vector(vector) {
    if (Vector.isZero()) {
        throw std::runtime_error("Error: creating line by equal points");
    }
}

TSafeDouble TLine::cos(const TLine& other) const { return Vector.cos(other.Vector); }
bool TLine::isParallel(const TLine& other) const { return Vector.isParallel(other.Vector); }
bool TLine::isPerpendicular(const TLine& other) const { return Vector.isPerpendicular(other.Vector); }

TSafeDouble TLine::distToPoint(const TPoint& point) const {
    const TVector P1P{Point1, point};
    if (P1P.isZero()) {
        return 0.0;
    }
    return (P1P - P1P.projectTo(Vector)).length();
}
bool TLine::containsPoint(const TPoint& point) const { return distToPoint(point) == 0.0; }

bool TLine::operator==(const TLine& other) const {
    return Vector.isParallel(other.Vector) && containsPoint(other.Point1);
}
bool TLine::operator!=(const TLine& other) const { return !(*this == other); }

TSafeDouble det2x2(TSafeDouble a11, TSafeDouble a12, TSafeDouble a21, TSafeDouble a22) { return a11 * a22 - a12 * a21; }

std::optional<TPoint> TLine::intersection(const TLine& other) const {
    if (*this == other) {
        throw std::runtime_error("Error: itersection of equal lines");
    }

    TSafeDouble a11 = Vector.X, a12 = -other.Vector.X, b1 = other.Point1.X - Point1.X;
    TSafeDouble a21 = Vector.Y, a22 = -other.Vector.Y, b2 = other.Point1.Y - Point1.Y;
    TSafeDouble a31 = Vector.Z, a32 = -other.Vector.Z, b3 = other.Point1.Z - Point1.Z;

    TSafeDouble det = det2x2(a11, a12, a21, a22);
    if (det == TSafeDouble{0}) {
        return std::nullopt;
    }

    TSafeDouble t = det2x2(b1, a12, b2, a22) / det;
    TSafeDouble s = det2x2(a11, b1, a21, b2) / det;

    if (t * a31 + s * a32 != b3) {
        return std::nullopt;
    }

    return TPoint{Point1.X + t * a11, Point1.Y + t * a21, Point1.Z + t * a31};
}

std::ostream& operator<<(std::ostream& os, const TLine& line) {
    std::cout << std::scientific;
    std::cout << std::setprecision(1);
    return os << "line:\n" << line.Point1 << line.Point2 << line.Vector;
}
void TLine::print() const { std::cout << *this; }

} // namespace NGeometry3D