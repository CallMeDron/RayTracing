#pragma once

#include "point.h"

#include <optional>

namespace NRayTracingLib {

class TObject {
  public:
    virtual std::optional<TPoint> intersection(const TLine& line) const = 0;

    virtual ~TObject() = default;
};

} // namespace NRayTracingLib
