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

    std::vector<TPoint> getPoints() const;

    friend std::ostream& operator<<(std::ostream& os, const TPolygon& polygon);
    void print() const;

  protected:
    std::vector<TPoint> Points_;

    void primalInit(const std::unordered_set<TPoint>& points);
    TPlane findAnyPlane() const;
    void checkComplanarity(const TPlane& plane) const;
    void sortByPolarAngle(const TPlane& plane);
    void removeExtraPoints();
    void convexityCheck() const;
};

class TRectangle : public TPolygon {
  public:
    explicit TRectangle(const std::unordered_set<TPoint>& points);
};

} // namespace NRayTracingLib