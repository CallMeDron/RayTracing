#include "polygon.h"
#include "plane.h"

#include <unordered_set>

namespace NRayTracingLib {

TPolygon::TPolygon(std::vector<TPoint> points) {
    std::unordered_set<TPoint> uniquePoints;
    for (const auto& point : points) {
        if (!uniquePoints.contains(point)) {
            Points.push_back(point);
            uniquePoints.insert(point);
        }
    }

    if (uniquePoints.size() < 3) {
        throw std::runtime_error("Error: creating polygon by < 3 unique points");
    }

    const TPlane plane{Points[0], Points[1], Points[2]};
    for (size_t i = 3; i < Points.size(); i++) {
        if (!plane.containsPoint(Points[i])) {
            throw std::runtime_error("Error: creating polygon by points that do not lie in the same plane");
        }
    }
}

} // namespace NRayTracingLib