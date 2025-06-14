#pragma once

#include "point.h"

namespace NRayTracingLib {

class TFigure {
  public:
    virtual std::optional<TPoint> intersection(const TLine& line) const = 0;

    virtual ~TFigure() = default;
};

} // namespace NRayTracingLib
