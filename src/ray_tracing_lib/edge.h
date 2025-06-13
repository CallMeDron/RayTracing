#pragma once

#include "point.h"

#include <vector>

namespace NRayTracingLib {

class TEdge {
  public:
    explicit TEdge(const TPoint& point1, const TPoint& point2);

    bool operator==(const TEdge& other) const;

    const std::vector<TPoint>& getPoints() const;

  private:
    std::vector<TPoint> Points_;
};

} // namespace NRayTracingLib

namespace std {

using namespace NRayTracingLib;

template <>
struct hash<TEdge> {
    size_t operator()(const TEdge& edge) const;
};

} // namespace std