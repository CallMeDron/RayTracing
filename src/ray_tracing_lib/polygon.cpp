#include "polygon.h"
#include "line.h"

#include <algorithm>
#include <cmath>
#include <unordered_set>

namespace NRayTracingLib {

bool TPolygon::IsLine() const {
    const TLine line{Points[0], Points[1]};
    for (size_t i = 2; i < Points.size(); i++) {
        if (!line.containsPoint(Points[i])) {
            return false;
        }
    }
    return true;
}

void TPolygon::SortByPolarAngle(const TPlane& plane) {
    TVector centerVector;
    for (const auto& point : Points) {
        centerVector += TVector{point};
    }
    centerVector /= static_cast<double>(Points.size());
    const TPoint center{centerVector};

    TVector xAxis;
    for (const auto& point : Points) {
        if (!(point - center).isZero()) {
            xAxis = point - center;
            break;
        }
    }
    if (xAxis.isZero()) {
        throw std::runtime_error("Error: zero xAxis in SortByPolarAngle");
    }
    xAxis.normalize();
    TVector yAxis = xAxis ^ plane.Normal;
    yAxis.normalize();

    std::vector<std::pair<TPoint, double>> pointsWithAngles;
    pointsWithAngles.reserve(Points.size());

    for (const auto& point : Points) {
        TVector vec = point - center;
        double x = (vec * xAxis).Value;
        double y = (vec * yAxis).Value;
        double angle = std::atan2(y, x);
        pointsWithAngles.emplace_back(point, angle);
    }

    std::sort(pointsWithAngles.begin(), pointsWithAngles.end(),
              [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });

    for (size_t i = 0; i < Points.size(); ++i) {
        Points[i] = pointsWithAngles[i].first;
    }
}

void TPolygon::RemoveExtraPoints() {}

bool TPolygon::IsConvex() const { return true; }

TPolygon::TPolygon(const TPoints& points) {
    std::unordered_set<TPoint> uniquePoints;
    for (const auto& point : points) {
        if (!uniquePoints.contains(point)) {
            Points.push_back(point);
            uniquePoints.insert(point);
        }
    }

    if (Points.size() < 3) {
        throw std::runtime_error("Error: creating polygon by < 3 unique points");
    }

    const TPlane plane{Points[0], Points[1], Points[2]};
    for (size_t i = 3; i < Points.size(); i++) {
        if (!plane.containsPoint(Points[i])) {
            throw std::runtime_error("Error: creating polygon by points that do not lie in the same plane");
        }
    }

    if (IsLine()) {
        throw std::runtime_error("Error: creating polygon by points that lie on the same line");
    }

    SortByPolarAngle(plane);

    RemoveExtraPoints();

    if (Points.size() < 3) {
        throw std::runtime_error("Error: creating polygon by < 3 effective points");
    }

    if (!IsConvex()) {
        throw std::runtime_error("Error: polygon is not convex");
    }
}

TRectangle::TRectangle(const TPoints& points) : TPolygon(points) {
    if (Points.size() != 4) {
        throw std::runtime_error("Rectangle must have exactly 4 points");
    }
}

} // namespace NRayTracingLib