#pragma once

#include "angle.h"
#include "line.h"

namespace NRayTracingLib {

class TCamera {
  public:
    TCamera(const TPoint& position, const TVector& direction, const std::pair<TAngle, TAngle>& viewAngles,
            const std::pair<uint16_t, uint16_t>& resolution);

    void makePicture(const TFigure& figure);
    void savePicture(const char* filename) const;

  private:
    TPoint Position_;
    TVector Direction_;
    TAngle WidthViewAngle_;
    TAngle HeightViewAngle_;
    size_t WidthResolution_;
    size_t HeightResolution_;

    TVector HalfUpVector_;
    TVector HalfLeftVector_;

    std::vector<uint8_t> ImageData_;

    void initHalfUpVector();
    void initHalfLeftVector();
};

} // namespace NRayTracingLib
