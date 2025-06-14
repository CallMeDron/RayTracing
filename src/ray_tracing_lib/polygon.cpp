#include "polygon.h"
#include "angle.h"
#include "line.h"

namespace NRayTracingLib {

void TPolygon::primalInit(const std::unordered_set<TPoint>& points) {
    if (points.size() < 3) {
        throw std::runtime_error("Error: creating polygon by < 3 unique points");
    }
    Points_ = std::vector<TPoint>(points.begin(), points.end());
    std::sort(Points_.begin(), Points_.end());
}

void TPolygon::findAnyPlane() {
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

    Plane_ = TPlane{Points_[0], Points_[1], thirdPoint};
}

void TPolygon::checkComplanarity() const {
    for (size_t i = 3; i < Points_.size(); i++) {
        if (!Plane_.containsPoint(Points_[i])) {
            throw std::runtime_error("Error: creating polygon by points that do not lie in the same plane");
        }
    }
}

void TPolygon::sortByPolarAngle() {
    TVector centerVector{0.0, 0.0, 0.0};
    for (const auto& point : Points_) {
        centerVector += TVector{point};
    }
    centerVector /= static_cast<double>(Points_.size());
    const TPoint center{centerVector};

    TVector xAxis = Points_[0] - center; // here used fact what Points_[0] is not a center
    xAxis.normalize();
    TVector yAxis = xAxis ^ Plane_.Normal;
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

void TPolygon::removeExtraPoints() {
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

void TPolygon::checkConvexityAndType() {
    std::unordered_set<bool> anglesSigns;
    TSafeDouble regularLength = (Points_[1] - Points_[0]).length();
    TSafeDouble regularCos = TAngle{360.0 / Points_.size()}.cos();

    for (size_t i = 0; i < Points_.size(); i++) { // here we use what all points are sorted by polar angle from center
        size_t prevIdx = (i == 0) ? (Points_.size() - 1) : (i - 1);
        size_t nextIdx = (i + 1) % Points_.size();

        const TVector lhs = Points_[i] - Points_[prevIdx];
        const TVector rhs = Points_[nextIdx] - Points_[i];

        anglesSigns.insert(lhs.sin(rhs) > 0.0);
        if (anglesSigns.size() > 1) {
            throw std::runtime_error("Error: creating not convex polygon");
        }

        if (lhs.length() != regularLength) {
            EdgesIsEqual_ = false;
        }

        if (lhs.cos(rhs) != regularCos) {
            AnglesIsEqual_ = false;
        }
    }
}

TPolygon::TPolygon(const std::unordered_set<TPoint>& points) {
    primalInit(points);
    // now we have >= 3 unique points, independency from order and Points_[0] is not a center

    findAnyPlane();
    // now we know what not all points lie on the same line

    checkComplanarity();
    // now we know what all points lie on the same plane

    sortByPolarAngle();
    // now all points are sorted by polar angle from center

    removeExtraPoints();
    // now all points are edges

    checkConvexityAndType();
    // now all points make up a сonvexity polygon
}

bool TPolygon::operator==(const TPolygon& other) const {
    auto sortedCopy = Points_;
    std::sort(sortedCopy.begin(), sortedCopy.end());

    auto otherSortedCopy = other.Points_;
    std::sort(otherSortedCopy.begin(), otherSortedCopy.end());

    return sortedCopy == otherSortedCopy;
}

const std::vector<TPoint>& TPolygon::getPoints() const { return Points_; }
const TPlane& TPolygon::getPlane() const { return Plane_; }
bool TPolygon::getEdgesIsEqual() const { return EdgesIsEqual_; }
bool TPolygon::getAnglesIsEqual() const { return AnglesIsEqual_; }

bool TPolygon::containsPoint(const TPoint& point) const {
    if (!Plane_.containsPoint(point)) {
        return false;
    }

    std::unordered_set<bool> anglesSigns;

    for (size_t i = 0; i < Points_.size(); i++) {
        size_t nextIdx = (i + 1) % Points_.size();

        TSafeDouble sign = ((Points_[nextIdx] - Points_[i]) ^ (point - Points_[i])) * Plane_.Normal;

        anglesSigns.insert(sign > 0.0);
        if (anglesSigns.size() > 1) {
            return false;
        }
    }

    return true;
}

std::optional<TPoint> TPolygon::intersection(const TLine& line) const {
    std::optional<TPoint> planeIntersectionPoint = Plane_.intersection(line);
    if ((planeIntersectionPoint == std::nullopt) || !containsPoint(planeIntersectionPoint.value())) {
        return std::nullopt;
    } else {
        return planeIntersectionPoint.value();
    }
}

std::ostream& operator<<(std::ostream& os, const TPolygon& polygon) {
    os << "polygon:\n";
    for (const auto& point : polygon.getPoints()) {
        os << point;
    }
    return os;
}

} // namespace NRayTracingLib

namespace std {

using namespace NRayTracingLib;

size_t hash<TPolygon>::operator()(const TPolygon& polygon) const {
    vector<TPoint> pointsStableSorted = polygon.getPoints();
    sort(pointsStableSorted.begin(), pointsStableSorted.end());

    size_t seed = 0;
    auto hashFunction = hash<TPoint>();
    for (const auto& point : pointsStableSorted) {
        seed ^= hashFunction(point) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

} // namespace std