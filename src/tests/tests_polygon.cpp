#include "../ray_tracing_lib/all.h"

#include <cmath>
#include <gtest/gtest.h>
#include <unordered_set>

using namespace NRayTracingLib;

const double TINY = ACCURACY / 2.0;
const double NOT_TINY = ACCURACY * 2.0;

//=== TPolygon Tests ===

TEST(TPolygon, InitializationFailsWithLessThanThreePoints) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 0, 0)};
    EXPECT_THROW(TPolygon p(points), std::runtime_error);
}

TEST(TPolygon, ValidTriangle) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 0, 0), TPoint(0, 1, 0)};
    TPolygon p(points);
    EXPECT_EQ(p.getPoints().size(), 3u);
}

TEST(TPolygon, ValidRectangle) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 0, 0), TPoint(0, 1, 0), TPoint(1, 1, 0)};
    TPolygon p(points);
    EXPECT_EQ(p.getPoints().size(), 4u);
}

TEST(TPolygon, CheckPlanarityFail) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 0, 0), TPoint(0, 1, 0), TPoint(0, 0, 1)};
    EXPECT_THROW(TPolygon p(points), std::runtime_error);
}

TEST(TPolygon, SortByPolarAngleWorksCorrectly) {
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

TEST(TPolygon, RemoveExtraPointsRemovesCollinearPoints) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 1, 0), TPoint(2, 2, 0), TPoint(0, 1, 0)};
    TPolygon p(points);
    EXPECT_EQ(p.getPoints().size(), 3u);
    for (const auto& point : p.getPoints()) {
        EXPECT_NE(point, TPoint(1, 1, 0));
    }
}

TEST(TPolygon, NonConvexPolygonThrows) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(2, 0, 0), TPoint(1, 1, 0), TPoint(2, 2, 0),
                                         TPoint(0, 2, 0)};
    EXPECT_THROW(TPolygon p(points), std::runtime_error);
}

TEST(TPolygon, PointsOnLineThrows) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 1, 0), TPoint(2, 2, 0)};
    EXPECT_THROW(TPolygon p(points), std::runtime_error);
}

TEST(TPolygon, FullCreationProcess) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 0, 0), TPoint(1, 1, 0), TPoint(0, 1, 0),
                                         TPoint(0.5, 0.5, 0)};
    EXPECT_THROW(TPolygon p(points), std::runtime_error);
}

void ExpectOptionalPointsEqual(const std::optional<TPoint>& expected, const std::optional<TPoint>& actual) {
    if (!expected.has_value() && !actual.has_value()) {
        SUCCEED();
    } else if (expected.has_value() && actual.has_value()) {
        EXPECT_EQ(expected.value(), actual.value());
    } else {
        FAIL() << "One of the optionals is null, the other is not.";
    }
}

TPolygon CreateSquare() {
    std::unordered_set<TPoint> pts = {TPoint(0, 0, 0), TPoint(1, 0, 0), TPoint(1, 1, 0), TPoint(0, 1, 0)};
    return TPolygon(pts);
}

TEST(TPolygon, ContainsPointInside) {
    TPolygon square = CreateSquare();
    TPoint insidePoint(0.5, 0.5, 0);
    EXPECT_TRUE(square.containsPoint(insidePoint));
}

TEST(TPolygon, ContainsPointOnEdge) {
    TPolygon square = CreateSquare();
    TPoint onEdge(1, 0.5, 0);
    EXPECT_TRUE(square.containsPoint(onEdge));
}

TEST(TPolygon, ContainsPointOnVertex) {
    TPolygon square = CreateSquare();
    TPoint vertex(0, 0, 0);
    EXPECT_TRUE(square.containsPoint(vertex));
}

TEST(TPolygon, ContainsPointOutside) {
    TPolygon square = CreateSquare();
    TPoint outsidePoint(2, 2, 0);
    EXPECT_FALSE(square.containsPoint(outsidePoint));
}

TEST(TPolygon, ContainsPointOnPlaneButOutsidePolygon) {
    TPolygon square = CreateSquare();
    TPoint outsideOnPlane(1.5, 0.5, 0);
    EXPECT_FALSE(square.containsPoint(outsideOnPlane));
}

TEST(TPolygon, IntersectionInsidePolygon) {
    TPolygon square = CreateSquare();
    TLine line(TPoint(0.5, 0.5, -1), TPoint(0.5, 0.5, 1));
    auto result = square.intersection(line);
    ExpectOptionalPointsEqual(TPoint(0.5, 0.5, 0), result);
}

TEST(TPolygon, IntersectionOutsidePolygon) {
    TPolygon square = CreateSquare();
    TLine line(TPoint(2, 2, -1), TPoint(2, 2, 1));
    auto result = square.intersection(line);
    EXPECT_FALSE(result.has_value());
}

TEST(TPolygon, IntersectionLineMissesPlane) {
    TPolygon square = CreateSquare();
    TLine line(TPoint(0, 0, 1), TPoint(1, 1, 1));
    auto result = square.intersection(line);
    EXPECT_FALSE(result.has_value());
}

TEST(TPolygon, IntersectionLineTangentToPolygonEdge) {
    TPolygon square = CreateSquare();
    TLine line(TPoint(0, 0.5, 0), TPoint(1, 0.5, 0));
    EXPECT_THROW(square.intersection(line), std::runtime_error);
}
