#include "polyhedron.h"

namespace NRayTracingLib {

TPolyhedron::TPolyhedron(const std::unordered_set<TPolygon>& polygons) : Faces_(polygons) {
    std::unordered_map<TEdge, uint8_t> edgesCount;

    for (const auto& face : Faces_) {
        for (size_t i = 0; i < face.getPoints().size(); i++) {
            size_t nextIdx = (i + 1) % face.getPoints().size();
            TEdge edge{face.getPoints()[i], face.getPoints()[nextIdx]};
            edgesCount[edge] += 1;
        }
    }

    for (const auto& [edge, count] : edgesCount) {
        if (count != 2) {
            throw std::runtime_error("Error: creating not closed polyhedron");
        }
    }
}

const std::unordered_set<TPolygon>& TPolyhedron::getFaces() const { return Faces_; }

std::optional<TPoint> TPolyhedron::intersection(const TLine& line) const {
    // closest to line.Point intersection point

    std::vector<std::pair<TPoint, double>> intersectionsWithDistances;

    for (const auto& face : Faces_) {
        std::optional<TPoint> intersection = face.intersection(line);
        if (intersection != std::nullopt) {
            intersectionsWithDistances.push_back(
                {intersection.value(), line.Point.distToPoint(intersection.value()).Value});
        }
    }

    sort(intersectionsWithDistances.begin(), intersectionsWithDistances.end(),
         [&line](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });

    if (intersectionsWithDistances.empty()) {
        return std::nullopt;
    }
    return intersectionsWithDistances[0].first;
}

} // namespace NRayTracingLib