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

    std::optional<std::pair<TPoint, TPointContainment>> intersection(const TLine& line) const override;

    friend std::ostream& operator<<(std::ostream& os, const TPolyhedron& polyhedron);

  private:
    std::unordered_set<TPolygon> Faces_;
};

TPolyhedron createRegularTetrahedron(const TPoint& center, TSafeDouble edgeLength);
TPolyhedron createRegularHexahedron(const TPoint& center, TSafeDouble edgeLength);
TPolyhedron createRegularOctahedron(const TPoint& center, TSafeDouble edgeLength);
TPolyhedron createRegularDodecahedron(const TPoint& center, TSafeDouble edgeLength);
TPolyhedron createRegularIcosahedron(const TPoint& center, TSafeDouble edgeLength);

} // namespace NRayTracingLib