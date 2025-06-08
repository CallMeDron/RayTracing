#include "plane.h"

#include "../line/line.h"

#include <optional>

namespace NRayTracingLib {

TPlane::TPlane(const TPoint& point, const TVector& normal) : Point(point), Normal(normal) {
    if (Normal.isZero()) {
        throw std::runtime_error("Error: creating plane by point and normal vector");
    }
    Normal.normalize();
}
TPlane::TPlane(const TPoint& point, const TVector& vector1, const TVector& vector2)
    : Point(point), Normal((vector1 ^ vector2)) {
    if (Normal.isZero()) {
        throw std::runtime_error("Error: creating plane by point and 2 vectors");
    }
    Normal.normalize();
}
TPlane::TPlane(const TPoint& point1, const TPoint& point2, const TPoint& point3)
    : Point(point1), Normal(((point2 - point1) ^ (point3 - point1))) {
    if (Normal.isZero()) {
        throw std::runtime_error("Error: creating plane by 3 points");
    }
    Normal.normalize();
}
TPlane::TPlane(const TPoint& point, const TLine& line)
    : Point(point), Normal(((line.Point - point) ^ (line.Point + line.Vector - point))) {
    if (Normal.isZero()) {
        throw std::runtime_error("Error: creating plane by point and line");
    }
    Normal.normalize();
}
TPlane::TPlane(const TLine& line1, const TLine& line2) : Point(line1.Point), Normal(0, 0, 0) {
    std::optional<TPoint> intersection = line1.intersection(line2);

    if (intersection.has_value()) {
        Point = *intersection;
        Normal = line1.Vector ^ line2.Vector;
    } else if (line1.isParallel(line2)) {
        Normal = line1.Vector ^ (line2.Point - line1.Point);
    }

    if (Normal.isZero()) {
        throw std::runtime_error("Error: creating plane by 2 lines");
    }

    Normal.normalize();
}

TSafeDouble TPlane::distToPoint(const TPoint& point) const noexcept { return ((point - Point) * Normal).abs(); }
bool TPlane::containsPoint(const TPoint& point) const noexcept { return distToPoint(point) == TSafeDouble{0}; }

bool TPlane::operator==(const TPlane& other) const {
    return Normal.isParallel(other.Normal) && containsPoint(other.Point);
}
bool TPlane::operator!=(const TPlane& other) const { return !(*this == other); }

TSafeDouble TPlane::cos(const TPlane& other) const { return Normal.cos(other.Normal); }
bool TPlane::isParallel(const TPlane& other) const { return Normal.isParallel(other.Normal); }
bool TPlane::isPerpendicular(const TPlane& other) const { return Normal.isPerpendicular(other.Normal); }

// std::optional<TPoint> intersection(const TLine& line) const {}
// std::optional<TLine> intersection(const TPlane& plane) const {}

} // namespace NRayTracingLib