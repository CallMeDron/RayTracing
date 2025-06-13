#include "edge.h"

#include <algorithm>

namespace NRayTracingLib {

TEdge::TEdge(const TPoint& point1, const TPoint& point2) : Points_{{point1, point2}} {
    if (point1 == point2) {
        throw std::runtime_error("Error: creating edge by 2 equal points");
    }
    std::sort(Points_.begin(), Points_.end());
}

bool TEdge::operator==(const TEdge& other) const { return Points_ == other.Points_; }

const std::vector<TPoint>& TEdge::getPoints() const { return Points_; }

} // namespace NRayTracingLib

namespace std {

using namespace NRayTracingLib;

size_t hash<TEdge>::operator()(const TEdge& edge) const {
    size_t seed = 0;
    auto hashFunction = hash<TPoint>();
    for (const auto& point : edge.getPoints()) {
        seed ^= hashFunction(point) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

} // namespace std