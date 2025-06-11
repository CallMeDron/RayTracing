#include "..\ray_tracing_lib\all.h"

#include <cmath>
#include <gtest/gtest.h>
#include <unordered_set>

using namespace NRayTracingLib;

const double TINY = ACCURACY / 2.0;
const double NOT_TINY = ACCURACY * 2.0;

//=== TPolygon Tests ===

TEST(TPolygonTest, InitializationFailsWithLessThanThreePoints) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 0, 0)};
    EXPECT_THROW(TPolygon p(points), std::runtime_error);
}

TEST(TPolygonTest, ValidTriangle) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 0, 0), TPoint(0, 1, 0)};
    TPolygon p(points);
    EXPECT_EQ(p.getPoints().size(), 3u);
}

TEST(TPolygonTest, ValidRectangle) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 0, 0), TPoint(0, 1, 0), TPoint(1, 1, 0)};
    TPolygon p(points);
    EXPECT_EQ(p.getPoints().size(), 4u);
}

TEST(TPolygonTest, CheckPlanarityFail) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 0, 0), TPoint(0, 1, 0), TPoint(0, 0, 1)};
    EXPECT_THROW(TPolygon p(points), std::runtime_error);
}

TEST(TPolygonTest, SortByPolarAngleWorksCorrectly) {
    std::unordered_set<TPoint> points = {TPoint(1, 0, 0), TPoint(0, 1, 0), TPoint(-1, 0, 0), TPoint(0, -1, 0)};
    TPolygon p(points);

    std::vector<std::vector<TPoint>> expectedVariants;
    expectedVariants.push_back({TPoint(-1, 0, 0), TPoint(0, 1, 0), TPoint(1, 0, 0), TPoint(0, -1, 0)});
    expectedVariants.push_back({TPoint(0, -1, 0), TPoint(-1, 0, 0), TPoint(0, 1, 0), TPoint(1, 0, 0)});
    expectedVariants.push_back({TPoint(1, 0, 0), TPoint(0, -1, 0), TPoint(-1, 0, 0), TPoint(0, 1, 0)});
    expectedVariants.push_back({TPoint(0, 1, 0), TPoint(1, 0, 0), TPoint(0, -1, 0), TPoint(-1, 0, 0)});
    expectedVariants.push_back({TPoint(-1, 0, 0), TPoint(0, -1, 0), TPoint(1, 0, 0), TPoint(0, 1, 0)});
    expectedVariants.push_back({TPoint(0, -1, 0), TPoint(1, 0, 0), TPoint(0, 1, 0), TPoint(-1, 0, 0)});
    expectedVariants.push_back({TPoint(1, 0, 0), TPoint(0, 1, 0), TPoint(-1, 0, 0), TPoint(0, -1, 0)});
    expectedVariants.push_back({TPoint(0, 1, 0), TPoint(-1, 0, 0), TPoint(0, -1, 0), TPoint(1, 0, 0)});

    bool condition = false;
    for (const auto& expected : expectedVariants) {
        condition |= (p.getPoints() == expected);
    }

    EXPECT_TRUE(condition);
}

TEST(TPolygonTest, RemoveExtraPointsRemovesCollinearPoints) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 1, 0), TPoint(2, 2, 0), TPoint(0, 1, 0)};
    TPolygon p(points);
    EXPECT_EQ(p.getPoints().size(), 3u);
    for (const auto& point : p.getPoints()) {
        EXPECT_NE(point, TPoint(1, 1, 0));
    }
}

TEST(TPolygonTest, NonConvexPolygonThrows) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(2, 0, 0), TPoint(1, 1, 0), TPoint(2, 2, 0),
                                         TPoint(0, 2, 0)};
    EXPECT_THROW(TPolygon p(points), std::runtime_error);
}

TEST(TPolygonTest, PointsOnLineThrows) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 1, 0), TPoint(2, 2, 0)};
    EXPECT_THROW(TPolygon p(points), std::runtime_error);
}

TEST(TPolygonTest, FullCreationProcess) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 0, 0), TPoint(1, 1, 0), TPoint(0, 1, 0),
                                         TPoint(0.5, 0.5, 0)};
    EXPECT_THROW(TPolygon p(points), std::runtime_error);
}
