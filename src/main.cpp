#include "ray_tracing_lib\line\line.h"
#include "ray_tracing_lib\plane\plane.h"
#include "ray_tracing_lib\point\point.h"
#include "ray_tracing_lib\safe_double\safe_double.h"
#include "ray_tracing_lib\vector\vector.h"

using namespace NRayTracingLib;

int main() {
    TPoint x{1, 2, 3};
    TPoint y{4, 5, -9};
    TLine line(x, y);
    std::cout << line;
}