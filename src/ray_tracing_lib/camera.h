#pragma once

#include "angle.h"
#include "point.h"

namespace NRayTracingLib {

class TCamera {
  public:
    TCamera();
    TCamera(const TPoint& position, const TVector& direction, const std::pair<TAngle, TAngle>& viewAngles,
            const std::pair<uint16_t, uint16_t>& resolution);

  private:
    TPoint Position_;
    TVector Direction_;
    std::pair<TAngle, TAngle> ViewAngles_;
    std::pair<uint16_t, uint16_t> Resolution_;
};

} // namespace NRayTracingLib
