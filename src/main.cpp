#include "ray_tracing_lib/all.h"

#include <chrono>

using namespace NRayTracingLib;

// void makePicture(const TCamera& camera, const std::vector<TFigure>& figures) {}

int main() {
    try {
        auto start = std::chrono::steady_clock::now();

        const TCamera camera{
            TPoint{10.0, 10.0, 10.0},
            TVector{-10.0, -10.0, -10.0},
            {TAngle{120.0}, TAngle{90.0}},
            {1200, 900},
        };

        auto end = std::chrono::steady_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        print(duration.count());

        // const std::vector<TFigure> figures{createRegularDodecahedron(TPoint(), 1.0)};

        // makePicture(camera, figures);

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}