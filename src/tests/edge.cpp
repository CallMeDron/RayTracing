#include "../ray_tracing_lib/all.h"

#include <gtest/gtest.h>

using namespace NRayTracingLib;

static constexpr double TINY = ACCURACY / 2.0;
static constexpr double NOT_TINY = ACCURACY * 2.0;

//=== TEdge tests ===

TEST(TEdge, CreateEdgeWithDifferentPoints) {
    TPoint p1{0, 0, 0};
    TPoint p2{1, 1, 1};
    TEdge edge(p1, p2);
    std::vector<NRayTracingLib::TPoint> points = edge.getPoints();
    EXPECT_EQ(points.size(), 2);
    EXPECT_TRUE((points[0] == p1 && points[1] == p2) || (points[0] == p2 && points[1] == p1));
}

TEST(TEdge, CreateEdgeWithSamePointsThrows) {
    TPoint p1{0, 0, 0};
    TPoint pSameAsP1{0, 0, 0};
    EXPECT_THROW(TEdge(p1, pSameAsP1), std::runtime_error);
}

TEST(TEdge, PointsAreSorted) {
    TPoint p1{1, 1, 1};
    TPoint p2{0, 0, 0};
    TEdge edge(p2, p1);
    std::vector<NRayTracingLib::TPoint> points = edge.getPoints();
    EXPECT_EQ(points[0], (TPoint{0, 0, 0}));
    EXPECT_EQ(points[1], (TPoint{1, 1, 1}));
}

TEST(TEdge, EqualEdges) {
    TPoint p1{0, 0, 0};
    TPoint p2{1, 1, 1};
    TEdge edge1(p1, p2);
    TEdge edge2(p2, p1);
    EXPECT_TRUE(edge1 == edge2);
}

TEST(TEdge, NotEqualEdges) {
    TPoint p1{0, 0, 0};
    TPoint p2{1, 1, 1};
    TPoint p3{2, 2, 2};
    TEdge edge1(p1, p2);
    TEdge edge2(p1, p3);
    EXPECT_FALSE(edge1 == edge2);
}

TEST(TEdge, HashConsistencyForEqualEdges) {
    TPoint p1{0, 0, 0};
    TPoint p2{1, 1, 1};
    TEdge edge1(p1, p2);
    TEdge edge2(p2, p1);
    std::hash<TEdge> hasher;
    EXPECT_EQ(hasher(edge1), hasher(edge2));
}

TEST(TEdge, GetPointsReturnsCorrectPoints) {
    TPoint p1{0, 0, 0};
    TPoint p3{2, 2, 2};
    TEdge edge(p1, p3);
    const std::vector<NRayTracingLib::TPoint>& points = edge.getPoints();
    EXPECT_EQ(points.size(), 2);
    EXPECT_TRUE((points[0] == p1 && points[1] == p3) || (points[0] == p3 && points[1] == p1));
}

TEST(TEdge, LargeCoordinates) {
    TPoint largePoint1{1000000, 2000000, 3000000};
    TPoint largePoint2{4000000, 5000000, 6000000};
    TEdge edge(largePoint1, largePoint2);
    std::vector<NRayTracingLib::TPoint> points = edge.getPoints();
    EXPECT_TRUE((points[0] == largePoint1 && points[1] == largePoint2) ||
                (points[0] == largePoint2 && points[1] == largePoint1));
}

TEST(TEdge, CreateEdgeWithNegativeCoordinates) {
    TPoint p1{-1, -2, -3};
    TPoint p2{-4, -5, -6};
    TEdge edge(p1, p2);
    std::vector<NRayTracingLib::TPoint> points = edge.getPoints();
    EXPECT_EQ(points.size(), 2);
    EXPECT_TRUE((points[0] == p1 && points[1] == p2) || (points[0] == p2 && points[1] == p1));
}

TEST(TEdge, CreateEdgeWithMixedCoordinates) {
    TPoint p1{-1, 2, -3};
    TPoint p2{4, -5, 6};
    TEdge edge(p1, p2);
    std::vector<NRayTracingLib::TPoint> points = edge.getPoints();
    EXPECT_EQ(points.size(), 2);
    EXPECT_TRUE((points[0] == p1 && points[1] == p2) || (points[0] == p2 && points[1] == p1));
}

TEST(TEdge, CreateEdgeWithPointsOnBoundaryValues) {
    TPoint p1{std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), 0.0};
    TPoint p2{0.0, std::numeric_limits<double>::max(), std::numeric_limits<double>::lowest()};
    TEdge edge(p1, p2);
    std::vector<NRayTracingLib::TPoint> points = edge.getPoints();
    EXPECT_EQ(points.size(), 2);
    EXPECT_TRUE((points[0] == p1 && points[1] == p2) || (points[0] == p2 && points[1] == p1));
}

TEST(TEdge, CreateEdgeWithPointsHavingSameCoordinatesDifferentOrder) {
    TPoint p1{1.0, 2.0, 3.0};
    TPoint p2{3.0, 2.0, 1.0};
    TEdge edge(p1, p2);
    std::vector<NRayTracingLib::TPoint> points = edge.getPoints();
    EXPECT_EQ(points.size(), 2);
    EXPECT_TRUE((points[0] == p1 && points[1] == p2) || (points[0] == p2 && points[1] == p1));
}

TEST(TEdge, EqualityWithDifferentOrderPoints) {
    TPoint p1{0, 0, 0};
    TPoint p2{1, 1, 1};
    TEdge edge1(p1, p2);
    TEdge edge2(p2, p1);
    EXPECT_TRUE(edge1 == edge2);
}

TEST(TEdge, InequalityWithDifferentPoints) {
    TPoint p1{0, 0, 0};
    TPoint p2{1, 1, 1};
    TPoint p3{2, 2, 2};
    TEdge edge1(p1, p2);
    TEdge edge2(p1, p3);
    EXPECT_FALSE(edge1 == edge2);
}

TEST(TEdge, HashEqualityForSameEdgesDifferentOrder) {
    TPoint p1{0, 0, 0};
    TPoint p2{1, 1, 1};
    TEdge edge1(p1, p2);
    TEdge edge2(p2, p1);
    std::hash<TEdge> hasher;
    EXPECT_EQ(hasher(edge1), hasher(edge2));
}

TEST(TEdge, HashDifferenceForDifferentEdges) {
    TPoint p1{0, 0, 0};
    TPoint p2{1, 1, 1};
    TPoint p3{2, 2, 2};
    TEdge edge1(p1, p2);
    TEdge edge2(p1, p3);
    std::hash<TEdge> hasher;
    EXPECT_NE(hasher(edge1), hasher(edge2));
}

TEST(TEdge, CreateEdgeWithPointsOnCoordinatePlanes) {
    TPoint p1{0.0, 0.0, 0.0};
    TPoint p2{0.0, 0.0, 1.0};
    TEdge edge(p1, p2);
    std::vector<NRayTracingLib::TPoint> points = edge.getPoints();
    EXPECT_EQ(points.size(), 2);
    EXPECT_TRUE((points[0] == p1 && points[1] == p2) || (points[0] == p2 && points[1] == p1));
}

TEST(TEdge, CreateEdgeWithLargeCoordinates) {
    TPoint p1{1e12, -1e12, 1e12};
    TPoint p2{-1e12, 1e12, -1e12};
    TEdge edge(p1, p2);
    std::vector<NRayTracingLib::TPoint> points = edge.getPoints();
    EXPECT_EQ(points.size(), 2);
    EXPECT_TRUE((points[0] == p1 && points[1] == p2) || (points[0] == p2 && points[1] == p1));
}

TEST(TEdge, CreateEdgeWithZeroCoordinates) {
    TPoint p1{0, 0, 0};
    TPoint p2{0, 0, 0};
    EXPECT_THROW(TEdge(p1, p2), std::runtime_error);
}

TEST(TEdge, CreateEdgeWithVeryClosePoints) {
    TPoint p1{1 + TINY, 2 + TINY, 3 + TINY};
    TPoint p2{1 + TINY * 2, 2 + TINY * 2, 3 + TINY * 2};
    EXPECT_THROW(TEdge(p1, p2), std::runtime_error);
}
