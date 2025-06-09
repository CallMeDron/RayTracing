#include "ray_tracing_lib\line\line.h"
#include "ray_tracing_lib\plane\plane.h"
#include "ray_tracing_lib\point\point.h"
#include "ray_tracing_lib\safe_double\safe_double.h"
#include "ray_tracing_lib\vector\vector.h"

using namespace NRayTracingLib;

int main() { std::cout << TPlane(TPoint{0, 1, 2}, TVector{3, 4, 5}); }