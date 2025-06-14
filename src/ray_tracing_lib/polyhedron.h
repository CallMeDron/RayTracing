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

    friend std::ostream& operator<<(std::ostream& os, const TPolyhedron& polyhedron);

  private:
    std::unordered_set<TPolygon> Faces_;
};

TPolyhedron CreateRegularTetrahedron(const TPoint& center, TSafeDouble edgeLength);
TPolyhedron CreateRegularHexahedron(const TPoint& center, TSafeDouble edgeLength);
TPolyhedron CreateRegularOctahedron(const TPoint& center, TSafeDouble edgeLength);
TPolyhedron CreateRegularDodecahedron(const TPoint& center, TSafeDouble edgeLength);
// TPolyhedron CreateRegularIcosahedron(const TPoint& center, TSafeDouble edgeLength);

} // namespace NRayTracingLib