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

    const TVector xAxis = (Points_[0] - center).getNormalized(); // here used fact what Points_[0] is not a center
    const TVector yAxis = (xAxis ^ Plane_.Normal).getNormalized();

    std::vector<std::pair<TPoint, double>> pointsWithAngles;
    pointsWithAngles.reserve(Points_.size());

    for (const auto& point : Points_) {
        const TVector centerToPoint = point - center;
        if (centerToPoint.isZero()) {
            throw std::runtime_error("Error: creating polygon with point in center");
        }
        const double x = (centerToPoint * xAxis).Value;
        const double y = (centerToPoint * yAxis).Value;
        const double angle = std::atan2(y, x);
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
        const size_t prevIdx = (i == 0) ? (Points_.size() - 1) : (i - 1);
        const size_t nextIdx = (i + 1) % Points_.size();

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
    const TSafeDouble regularLength = (Points_[1] - Points_[0]).length();
    const TSafeDouble regularCos = TAngle{360.0 / Points_.size()}.cos();

    for (size_t i = 0; i < Points_.size(); i++) { // here we use what all points are sorted by polar angle from center
        const size_t prevIdx = (i == 0) ? (Points_.size() - 1) : (i - 1);
        const size_t nextIdx = (i + 1) % Points_.size();

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

TPointContainment TPolygon::containsPoint(const TPoint& point) const {
    const TSafeDouble ON_BORDER_CHECK = 1e-2;

    if (!Plane_.containsPoint(point)) {
        return TPointContainment::Outside;
    }

    bool hasPositive = false;
    bool hasNegative = false;

    for (size_t i = 0; i < Points_.size(); i++) {
        const size_t nextIdx = (i + 1) % Points_.size();
        const TVector edge = Points_[nextIdx] - Points_[i];
        const TVector toPoint = point - Points_[i];

        if (toPoint.length() < ON_BORDER_CHECK) {
            return TPointContainment::OnBoundary;
        }

        const TSafeDouble sign = (edge ^ toPoint) * Plane_.Normal;

        if (sign.abs() < ON_BORDER_CHECK) {
            const TSafeDouble scalar = toPoint * edge;
            if ((scalar >= 0.0) && (scalar <= edge * edge)) {
                return TPointContainment::OnBoundary;
            } else {
                return TPointContainment::Outside;
            }
        } else if (sign > ON_BORDER_CHECK) {
            hasPositive = true;
        } else {
            hasNegative = true;
        }

        if (hasPositive && hasNegative) {
            return TPointContainment::Outside;
        }
    }

    return TPointContainment::Inside;
}

std::optional<std::pair<TPoint, TPointContainment>> TPolygon::intersection(const TLine& line) const {
    const std::optional<std::pair<TPoint, TPointContainment>> planeIntersection = Plane_.intersection(line);
    if (planeIntersection == std::nullopt) {
        return std::nullopt;
    }
    const TPointContainment pointContainment = containsPoint(planeIntersection.value().first);
    if (pointContainment == TPointContainment::Outside) {
        return std::nullopt;
    } else {
        return std::make_pair(planeIntersection.value().first, pointContainment);
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
    const auto hashFunction = hash<TPoint>();
    for (const auto& point : pointsStableSorted) {
        seed ^= hashFunction(point) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

} // namespace std