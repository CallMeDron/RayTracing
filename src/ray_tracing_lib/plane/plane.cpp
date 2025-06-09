#include "plane.h"

#include "../line/line.h"

#include <optional>

namespace NRayTracingLib {

TPlane::TPlane() : Point(TPoint{0, 0, 0}), Normal(TVector{1, 0, 0}) {}
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
TPlane::TPlane(const TLine& line1, const TLine& line2) : Point(line1.Point), Normal(TVector{0, 0, 0}) {
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
bool TPlane::containsLine(const TLine& line) const {
    return containsPoint(line.Point) && Normal.isPerpendicular(line.Vector);
}

bool TPlane::operator==(const TPlane& other) const {
    return Normal.isParallel(other.Normal) && containsPoint(other.Point);
}
bool TPlane::operator!=(const TPlane& other) const { return !(*this == other); }

TSafeDouble TPlane::cos(const TPlane& other) const { return Normal.cos(other.Normal); }
bool TPlane::isParallel(const TPlane& other) const { return Normal.isParallel(other.Normal); }
bool TPlane::isPerpendicular(const TPlane& other) const { return Normal.isPerpendicular(other.Normal); }

std::optional<TPoint> TPlane::intersection(const TLine& line) const {
    if (Normal.isPerpendicular(line.Vector)) {
        if (containsLine(line)) {
            throw std::runtime_error("Error: itersection of plane and line in it");
        } else {
            return std::nullopt;
        }
    }

    return line.Point + line.Vector * (((Point - line.Point) * Normal) / (line.Vector * Normal));
}
std::optional<TLine> TPlane::intersection(const TPlane& plane) const {
    if (Normal.isParallel(plane.Normal)) {
        if (*this == plane) {
            throw std::runtime_error("Error: intersection of equal planes");
        } else {
            return std::nullopt;
        }
    }

    TVector direction = Normal ^ plane.Normal;

    const TSafeDouble A1 = Normal.X;
    const TSafeDouble B1 = Normal.Y;
    const TSafeDouble C1 = Normal.Z;
    const TSafeDouble D1 = -(A1 * Point.X + B1 * Point.Y + C1 * Point.Z);

    const TSafeDouble A2 = plane.Normal.X;
    const TSafeDouble B2 = plane.Normal.Y;
    const TSafeDouble C2 = plane.Normal.Z;
    const TSafeDouble D2 = -(A2 * plane.Point.X + B2 * plane.Point.Y + C2 * plane.Point.Z);

    TSafeDouble x, y, z;

    if (direction.Z != TSafeDouble{0}) {
        TSafeDouble det = A1 * B2 - A2 * B1;
        if (det == TSafeDouble{0}) {
            throw std::runtime_error("Degenerate system while computing plane intersection (z = 0)");
        }
        x = (B1 * D2 - B2 * D1) / det;
        y = (A2 * D1 - A1 * D2) / det;
    } else if (direction.Y != TSafeDouble{0}) {
        TSafeDouble det = A1 * C2 - A2 * C1;
        if (det == TSafeDouble{0}) {
            throw std::runtime_error("Degenerate system while computing plane intersection (y = 0)");
        }
        x = (C1 * D2 - C2 * D1) / det;
        z = (A2 * D1 - A1 * D2) / det;
    } else {
        TSafeDouble det = B1 * C2 - B2 * C1;
        if (det == TSafeDouble{0}) {
            throw std::runtime_error("Degenerate system while computing plane intersection (x = 0)");
        }
        y = (C1 * D2 - C2 * D1) / det;
        z = (B2 * D1 - B1 * D2) / det;
    }

    return TLine{TPoint{x, y, z}, direction};
}

std::ostream& operator<<(std::ostream& os, const TPlane& plane) {
    return os << "plane:\n" << plane.Point << plane.Normal;
}
void TPlane::print() const { std::cout << *this; }

} // namespace NRayTracingLib