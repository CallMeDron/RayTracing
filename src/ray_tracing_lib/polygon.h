#pragma once

#include "plane.h"
#include "point.h"

#include <iostream>
#include <unordered_set>
#include <vector>

namespace NRayTracingLib {

class TPolygon {
  public:
    explicit TPolygon(const std::unordered_set<TPoint>& points);

    std::vector<TPoint> GetPoints() const;

    friend std::ostream& operator<<(std::ostream& os, const TPolygon& polygon);
    void print() const;

  protected:
    std::vector<TPoint> Points_;

    void PrimalInit(const std::unordered_set<TPoint>& points);
    TPlane FindAnyPlane() const;
    void CheckComplanarity(const TPlane& plane) const;
    void SortByPolarAngle(const TPlane& plane);
    void RemoveExtraPoints();
    void ConvexityCheck() const;
};

class TRectangle : public TPolygon {
  public:
    explicit TRectangle(const std::unordered_set<TPoint>& points);
};

} // namespace NRayTracingLib