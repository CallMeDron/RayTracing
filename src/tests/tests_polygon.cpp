#include "..\ray_tracing_lib\line.h"
#include "..\ray_tracing_lib\plane.h"
#include "..\ray_tracing_lib\point.h"
#include "..\ray_tracing_lib\polygon.h"
#include "..\ray_tracing_lib\safe_double.h"
#include "..\ray_tracing_lib\vector.h"

#include <gtest/gtest.h>
#include <unordered_set>

using namespace NRayTracingLib;

//=== TPolygon tests ===

TEST(TPolygon, CreatesPolygonWithUniquePointsSuccessfully) {
    std::vector<TPoint> points = {
        TPoint(0.0, 0.0, 0.0), TPoint(1.0, 0.0, 0.0), TPoint(0.0, 1.0, 0.0),
        TPoint(1.0, 1.0, 0.0), TPoint(0.0, 0.0, 0.0),
    };

    EXPECT_NO_THROW({ TPolygon polygon(points); });
}

TEST(TPolygon, ThrowsWhenLessThanThreeUniquePoints) {
    std::vector<TPoint> points = {
        TPoint(0.0, 0.0, 0.0),
        TPoint(0.0, 0.0, 0.0),
        TPoint(0.0, 0.0, 0.0),
    };

    EXPECT_THROW({ TPolygon polygon(points); }, std::runtime_error);
}

TEST(TPolygon, ThrowsWhenPointsNotOnSamePlane) {
    std::vector<TPoint> points = {
        TPoint(0.0, 0.0, 0.0),
        TPoint(1.0, 0.0, 0.0),
        TPoint(0.0, 1.0, 0.0),
        TPoint(0.0, 0.0, 1.0),
    };

    EXPECT_THROW({ TPolygon polygon(points); }, std::runtime_error);
}