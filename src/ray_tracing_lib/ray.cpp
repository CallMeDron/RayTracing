#include "ray.h"

namespace NRayTracingLib {

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