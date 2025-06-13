#pragma once

#include "common.h"
#include "figure.h"
#include "plane.h"
#include "point.h"

namespace NRayTracingLib {

class TPolygon : public TFigure {
  public:
    explicit TPolygon(const std::unordered_set<TPoint>& points);

    bool operator==(const TPolygon& other) const;

    const std::vector<TPoint>& getPoints() const;
    const TPlane& getPlane() const;
    bool getEdgesIsEqual() const;
    bool getAnglesIsEqual() const;

    bool containsPoint(const TPoint& point) const;

    std::optional<TPoint> intersection(const TLine& line) const override;

    friend std::ostream& operator<<(std::ostream& os, const TPolygon& polygon);
    void print() const;

  protected:
    std::vector<TPoint> Points_;
    TPlane Plane_;
    bool EdgesIsEqual_ = true;
    bool AnglesIsEqual_ = true;

    void primalInit(const std::unordered_set<TPoint>& points);
    void findAnyPlane();
    void checkComplanarity() const;
    void sortByPolarAngle();
    void removeExtraPoints();
    void checkConvexityAndType();
};

} // namespace NRayTracingLib

namespace std {

using namespace NRayTracingLib;

template <>
struct hash<TPolygon> {
    size_t operator()(const TPolygon& polygon) const;
};

} // namespace std