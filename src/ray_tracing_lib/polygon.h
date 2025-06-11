#pragma once

#include "object.h"
#include "plane.h"
#include "point.h"

#include <iostream>
#include <unordered_set>
#include <vector>

namespace NRayTracingLib {

class TPolygon : TObject {
  public:
    explicit TPolygon(const std::unordered_set<TPoint>& points);

    std::vector<TPoint> getPoints() const;
    TPlane getPlane() const;

    bool containsPoint(const TPoint& point) const;

    std::optional<TPoint> intersection(const TLine& line) const override;

    friend std::ostream& operator<<(std::ostream& os, const TPolygon& polygon);
    void print() const;

  protected:
    std::vector<TPoint> Points_;
    TPlane Plane_;

    void primalInit(const std::unordered_set<TPoint>& points);
    void findAnyPlane();
    void checkComplanarity() const;
    void sortByPolarAngle();
    void removeExtraPoints();
    void convexityCheck() const;
};

class TRectangle : public TPolygon {
  public:
    explicit TRectangle(const std::unordered_set<TPoint>& points);
};

} // namespace NRayTracingLib