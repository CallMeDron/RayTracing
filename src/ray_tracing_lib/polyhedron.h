#pragma once

#include "common.h"
#include "edge.h"
#include "figure.h"
#include "line.h"
#include "polygon.h"

namespace NRayTracingLib {

class TPolyhedron : public TFigure {
  public:
    TPolyhedron(const std::unordered_set<TPolygon>& polygons);

    const std::unordered_set<TPolygon>& getFaces() const;

    std::optional<TPoint> intersection(const TLine& line) const override;

  private:
    std::unordered_set<TPolygon> Faces_;
};

} // namespace NRayTracingLib