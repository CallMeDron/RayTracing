#include "polygon.h"
#include "line.h"

#include <algorithm>
#include <cmath>
#include <unordered_set>

namespace NRayTracingLib {

void TPolygon::PrimalInit(const std::unordered_set<TPoint>& points) {
    if (points.size() < 3) {
        throw std::runtime_error("Error: creating polygon by < 3 unique points");
    }
    Points_ = std::vector<TPoint>(points.begin(), points.end());
    std::sort(Points_.begin(), Points_.end(), [](const TPoint& lhs, const TPoint& rhs) {
        if (lhs.X != rhs.X) {
            return lhs.X < rhs.X;
        }
        if (lhs.Y != rhs.Y) {
            return lhs.Y < rhs.Y;
        }
        return lhs.Z < rhs.Z;
    });
}

TPlane TPolygon::FindAnyPlane() const {
    const TLine line{Points_[0], Points_[1]};
    TPoint thirdPoint;
    bool thirdPointFound = false;
    for (size_t i = 2; i < Points_.size(); i++) {
        if (!line.containsPoint(Points_[i])) {
            thirdPoint = Points_[i];
            thirdPointFound = true;
            break;
        }
    }
    if (!thirdPointFound) {
        throw std::runtime_error("Error: creating polygon by points that all lie on the same line");
    }

    return TPlane{Points_[0], Points_[1], thirdPoint};
}

void TPolygon::CheckComplanarity(const TPlane& plane) const {
    for (size_t i = 3; i < Points_.size(); i++) {
        if (!plane.containsPoint(Points_[i])) {
            throw std::runtime_error("Error: creating polygon by points that do not lie in the same plane");
        }
    }
}

void TPolygon::SortByPolarAngle(const TPlane& plane) {
    TVector centerVector;
    for (const auto& point : Points_) {
        centerVector += TVector{point};
    }
    centerVector /= static_cast<double>(Points_.size());
    const TPoint center{centerVector};

    TVector xAxis = Points_[0] - center; // here used fact what Points_[0] is not a center
    xAxis.normalize();
    TVector yAxis = xAxis ^ plane.Normal;
    yAxis.normalize();

    std::vector<std::pair<TPoint, double>> pointsWithAngles;
    pointsWithAngles.reserve(Points_.size());

    for (const auto& point : Points_) {
        TVector centerToPoint = point - center;
        if (centerToPoint.isZero()) {
            throw std::runtime_error("Error: creating polygon with point in center");
        }
        double x = (centerToPoint * xAxis).Value;
        double y = (centerToPoint * yAxis).Value;
        double angle = std::atan2(y, x);
        pointsWithAngles.emplace_back(point, angle);
    }

    std::sort(pointsWithAngles.begin(), pointsWithAngles.end(),
              [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });

    for (size_t i = 0; i < Points_.size(); i++) {
        Points_[i] = pointsWithAngles[i].first;
    }
}

void TPolygon::RemoveExtraPoints() {
    std::unordered_set<size_t> extraPoints;

    for (size_t i = 0; i < Points_.size(); i++) { // here we use what all points are sorted by polar angle from center
        size_t prevIdx = (i == 0) ? (Points_.size() - 1) : (i - 1);
        size_t nextIdx = (i + 1) % Points_.size();

        const TVector lhs = Points_[i] - Points_[prevIdx];
        const TVector rhs = Points_[nextIdx] - Points_[i];

        if (lhs.isParallel(rhs)) {
            extraPoints.insert(i);
        }
    }

    std::vector<TPoint> cleanPoints;
    for (size_t i = 0; i < Points_.size(); i++) {
        if (!extraPoints.contains(i)) {
            cleanPoints.push_back(Points_[i]);
        }
    }

    if (cleanPoints.size() < 3) {
        throw std::runtime_error("Error: creating polygon by < 3 effective points");
    }

    Points_ = cleanPoints;
}

void TPolygon::ConvexityCheck() const {
    std::unordered_set<bool> anglesSigns;

    for (size_t i = 0; i < Points_.size(); i++) { // here we use what all points are sorted by polar angle from center
        size_t prevIdx = (i == 0) ? (Points_.size() - 1) : (i - 1);
        size_t nextIdx = (i + 1) % Points_.size();

        const TVector lhs = Points_[i] - Points_[prevIdx];
        const TVector rhs = Points_[nextIdx] - Points_[i];

        anglesSigns.insert(lhs.sin(rhs) > TSafeDouble{0});
        if (anglesSigns.size() > 1) {
            throw std::runtime_error("Error: creating not convex polygon");
        }
    }
}

TPolygon::TPolygon(const std::unordered_set<TPoint>& points) {
    PrimalInit(points);
    // now we have >= 3 unique points, independency from order and Points_[0] is not a center

    const TPlane plane = FindAnyPlane();
    // now we know what not all points lie on the same line

    CheckComplanarity(plane);
    // now we know what all points lie on the same plane

    SortByPolarAngle(plane);
    // now all points are sorted by polar angle from center

    RemoveExtraPoints();
    // now all points are edges

    ConvexityCheck();
    // now all points make up a сonvexity polygon
}

std::vector<TPoint> TPolygon::GetPoints() const { return Points_; }

TRectangle::TRectangle(const std::unordered_set<TPoint>& points) : TPolygon(points) {
    if (Points_.size() != 4) {
        throw std::runtime_error("Rectangle must have exactly 4 points");
    }
}

} // namespace NRayTracingLib