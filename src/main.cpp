#include "ray_tracing_lib\line.h"
#include "ray_tracing_lib\plane.h"
#include "ray_tracing_lib\point.h"
#include "ray_tracing_lib\polygon.h"
#include "ray_tracing_lib\safe_double.h"
#include "ray_tracing_lib\vector.h"

using namespace NRayTracingLib;

// struct TConfig {
//     TPoint CameraPosition = TPoint{0, 0, 0};
// };

int main() { std::cout << TPolygon({TPoint{0, 1, 0}, TPoint{1, 0, 0}, TPoint{1, 2, 2}, TPoint{2, 1, 2}}); }