#pragma once

#include "angle.h"
#include "line.h"

namespace NRayTracingLib {

class TCamera {
  public:
    TCamera(const TPoint& position, const TVector& direction, const std::pair<TAngle, TAngle>& viewAngles,
            const std::pair<uint16_t, uint16_t>& resolution);

  private:
    TPoint Position_;
    TVector Direction_;
    std::pair<TAngle, TAngle> ViewAngles_;
    std::pair<size_t, size_t> Resolution_;
    std::vector<TRay> Rays_;

    TRay& getRay(size_t i, size_t j);
    TVector getHalfUpVector() const;
    TVector getHalfLeftVector() const;
    void initRays();
};

} // namespace NRayTracingLib
