#include "ray_tracing_lib/all.h"

#include <chrono>

using namespace NRayTracingLib;

int main() {
    try {
        const double radius = 10.0;
        const size_t total_iterations = 100;

        for (size_t i = 0; i < total_iterations; i++) {
            auto start = std::chrono::steady_clock::now();

            double angle = (2 * std::numbers::pi * i) / total_iterations;
            double camX = radius * cos(angle);
            double camY = radius * sin(angle);
            double camZ = radius;

            TCamera camera{
                TPoint{camX, camY, camZ},
                TVector{-camX, -camY, -camZ},
                {TAngle{15.0}, TAngle{15.0}},
                {1000, 1000},
            };

            const TPolyhedron figure = createRegularDodecahedron(TPoint{0.0, 0.0, 0.0}, 1.0);
            camera.makePicture(figure);

            char filename[256];
            snprintf(filename, sizeof(filename), "D:/Coding/C++/RayTracing/src/images/output_%d.png", i);
            camera.savePicture(filename);

            auto end = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            print("Program work time =", duration.count(), "ms");
        }

    } catch (const std::exception& e) {
        print(e.what());
    }
}