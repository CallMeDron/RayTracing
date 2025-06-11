#pragma once

#include "safe_double.h"

namespace NRayTracingLib {

class TAngle {
  public:
    explicit TAngle(TSafeDouble angle, bool fromDegrees = true);

    TSafeDouble getDegrees() const;
    TSafeDouble getRadians() const;

    TSafeDouble cos() const;
    TSafeDouble sin() const;

  private:
    TSafeDouble Degrees_;
    TSafeDouble Radians_;
};

} // namespace NRayTracingLib
