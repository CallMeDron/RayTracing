#pragma once

#include "point.h"

namespace NRayTracingLib {

enum class TPointContainment { Outside, Inside, OnBoundary };

class TFigure {
  public:
    virtual std::optional<std::pair<TPoint, TPointContainment>> intersection(const TLine& line) const = 0;

    virtual ~TFigure() = default;
};

} // namespace NRayTracingLib
