#include "line.h"

namespace NRayTracingLib {

TLine::TLine() {}
TLine::TLine(const TPoint& point1, const TPoint& point2) : Point(point1), Vector(point2 - point1) {
    if (Vector.isZero()) {
        throw std::runtime_error("Error: creating line by equal points");
    }
}
TLine::TLine(const TPoint& point, const TVector& vector) : Point(point), Vector(vector) {
    if (Vector.isZero()) {
        throw std::runtime_error("Error: creating line by equal points");
    }
}

TSafeDouble TLine::cos(const TLine& other) const { return Vector.cos(other.Vector); }
bool TLine::isParallel(const TLine& other) const { return Vector.isParallel(other.Vector); }
bool TLine::isPerpendicular(const TLine& other) const { return Vector.isPerpendicular(other.Vector); }

TSafeDouble TLine::distToPoint(const TPoint& point) const {
    const TVector vectorToPoint{Point, point};
    if (vectorToPoint.isZero()) {
        return 0.0;
    }
    return (vectorToPoint - vectorToPoint.projectTo(Vector)).length();
}
bool TLine::containsPoint(const TPoint& point) const { return distToPoint(point) == 0.0; }

bool TLine::operator==(const TLine& other) const {
    return Vector.isParallel(other.Vector) && containsPoint(other.Point);
}
bool TLine::operator!=(const TLine& other) const { return !(*this == other); }

static TSafeDouble det2x2(TSafeDouble a11, TSafeDouble a12, TSafeDouble a21, TSafeDouble a22) {
    return a11 * a22 - a12 * a21;
}

std::optional<TPoint> TLine::intersection(const TLine& other) const {
    if (*this == other) {
        throw std::runtime_error("Error: itersection of equal lines");
    }

    const TSafeDouble a11 = Vector.X, a12 = -other.Vector.X, b1 = other.Point.X - Point.X;
    const TSafeDouble a21 = Vector.Y, a22 = -other.Vector.Y, b2 = other.Point.Y - Point.Y;
    const TSafeDouble a31 = Vector.Z, a32 = -other.Vector.Z, b3 = other.Point.Z - Point.Z;

    const TSafeDouble det = det2x2(a11, a12, a21, a22);
    if (det == 0.0) {
        return std::nullopt;
    }

    const TSafeDouble t = det2x2(b1, a12, b2, a22) / det;
    const TSafeDouble s = det2x2(a11, b1, a21, b2) / det;

    const TPoint result{Point.X + t * a11, Point.Y + t * a21, Point.Z + t * a31};

    if ((distToPoint(result) > (10.0 * ACCURACY)) || (other.distToPoint(result) > (10.0 * ACCURACY))) {
        return std::nullopt;
    }

    return result;
}
std::optional<TPoint> TLine::intersection(const TPlane& plane) const {
    if (plane.Normal.isPerpendicular(Vector)) {
        if (plane.containsLine(*this)) {
            throw std::runtime_error("Error: itersection of plane and line in it");
        } else {
            return std::nullopt;
        }
    }

    return Point + Vector * (((plane.Point - Point) * plane.Normal) / (Vector * plane.Normal));
}

std::ostream& operator<<(std::ostream& os, const TLine& line) { return os << "line:\n" << line.Point << line.Vector; }

TRay::TRay() {}
TRay::TRay(const TPoint& point1, const TPoint& point2) : TLine(point1, point2) {}
TRay::TRay(const TPoint& point, const TVector& vector) : TLine(point, vector) {}

TSafeDouble TRay::distToPoint(const TPoint& point) const {
    if (Point == point) {
        return 0.0;
    }
    if ((point - Point).cos(Vector) >= 0) {
        return TLine::distToPoint(point);
    }
    return Point.distToPoint(point);
}

std::optional<TPoint> TRay::intersection(const TPlane& plane) const {
    std::optional<TPoint> lineIntersection = TLine::intersection(plane);
    if (lineIntersection == std::nullopt || !containsPoint(lineIntersection.value())) {
        return std::nullopt;
    }
    return lineIntersection;
}

std::ostream& operator<<(std::ostream& os, const TRay& ray) { return os << "ray:\n" << ray.Point << ray.Vector; }

} // namespace NRayTracingLib