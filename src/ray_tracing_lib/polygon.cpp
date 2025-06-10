#include "polygon.h"
#include "plane.h"

#include <algorithm>
#include <cmath>
#include <unordered_set>

namespace NRayTracingLib {

// void TPolygon::SortByPolarAngle(const TPlane& plane) {
//     TVector centerVector;
//     for (const auto& point : Points) {
//         centerVector += TVector{point};
//     }
//     centerVector /= TSafeDouble{Points.size()};
//     const TPoint center{centerVector};

//     TVector xAxis = Points[0] - center;
//     xAxis.normalize();
//     TVector yAxis = xAxis ^ plane.Normal;
//     yAxis.normalize();

//     std::sort(Points.begin(), Points.end(), [&center, &xAxis, &yAxis](const TPoint& a, const TPoint& b) {
//         double aX = (a - center).projectTo(xAxis).length().Value;
//         double aY = (a - center).projectTo(yAxis).length().Value;

//         double bX = (b - center).projectTo(xAxis).length().Value;
//         double bY = (b - center).projectTo(yAxis).length().Value;

//         return std::atan2(aY, aX) < std::atan2(bY, bX);
//     });
// }

// void TPolygon::RemoveExtraPoints() {}

TPolygon::TPolygon(const TPoints& points) {
    // unique points only
    std::unordered_set<TPoint> uniquePoints;
    for (const auto& point : points) {
        if (!uniquePoints.contains(point)) {
            Points.push_back(point);
            uniquePoints.insert(point);
        }
    }

    // count of unique points >= 3
    if (Points.size() < 3) {
        throw std::runtime_error("Error: creating polygon by < 3 unique points");
    }

    // all points on one plane
    const TPlane plane{Points[0], Points[1], Points[2]};
    for (size_t i = 3; i < Points.size(); i++) {
        if (!plane.containsPoint(Points[i])) {
            throw std::runtime_error("Error: creating polygon by points that do not lie in the same plane");
        }
    }

    // SortByPolarAngle(plane);

    // RemoveExtraPoints();

    // effective count of points >= 3
    if (Points.size() < 3) {
        throw std::runtime_error("Error: creating polygon by < 3 unique points");
    }
}

TRectangle::TRectangle(const TPoints& points) : TPolygon(std::move(points)) {
    if (Points.size() != 4) {
        throw std::runtime_error("Rectangle must have exactly 4 points");
    }
}

} // namespace NRayTracingLib