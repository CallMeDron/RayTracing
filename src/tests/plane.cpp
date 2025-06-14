#include "../ray_tracing_lib/all.h"

#include <gtest/gtest.h>

using namespace NRayTracingLib;

static constexpr double TINY = ACCURACY / 2.0;
static constexpr double NOT_TINY = ACCURACY * 2.0;

//=== TPlane Tests ===

TEST(TPlane, Constructor_PointAndNormal_ValidNormal_Succeeds) {
    TPoint p{0, 0, 0};
    TVector n{0, 0, 1};
    TPlane plane(p, n);
    EXPECT_EQ(plane.Point, p);
    EXPECT_EQ(plane.Normal, n);
}

TEST(TPlane, Constructor_PointAndNormal_ZeroNormal_Throws) {
    TPoint p{0, 0, 0};
    TVector zeroVec{0, 0, 0};
    EXPECT_THROW(TPlane(p, zeroVec), std::runtime_error);
}

TEST(TPlane, Constructor_PointAndTwoVectors_ValidNormal_Succeeds) {
    TPoint p{0, 0, 0};
    TVector v1{1, 0, 0};
    TVector v2{0, 1, 0};
    TPlane plane(p, v1, v2);
    EXPECT_EQ(plane.Point, p);
    EXPECT_EQ(plane.Normal, v1 ^ v2);
}

TEST(TPlane, Constructor_PointAndTwoVectors_ZeroNormal_Throws) {
    TPoint p{0, 0, 0};
    TVector v{1, 0, 0};
    EXPECT_THROW(TPlane(p, v, v), std::runtime_error);
}

TEST(TPlane, Constructor_ThreePoints_ValidNormal_Succeeds) {
    TPoint p1{0, 0, 0};
    TPoint p2{1, 0, 0};
    TPoint p3{0, 1, 0};
    TPlane plane(p1, p2, p3);
    EXPECT_EQ(plane.Point, p1);
    EXPECT_EQ(plane.Normal, (p2 - p1) ^ (p3 - p1));
}

TEST(TPlane, Constructor_ThreePoints_Colinear_Throws) {
    TPoint p1{0, 0, 0};
    TPoint p2{1, 1, 1};
    TPoint p3{2, 2, 2};
    EXPECT_THROW(TPlane(p1, p2, p3), std::runtime_error);
}

TEST(TPlane, Constructor_TwoLines_Intersecting_Succeeds) {
    TPoint p1{0, 0, 0};
    TVector v1{1, 0, 0};
    TLine line1{p1, v1};
    TPoint p2{0, 0, 0};
    TVector v2{0, 1, 0};
    TLine line2{p2, v2};
    TPlane plane(line1, line2);
    EXPECT_EQ(plane.Point, p1);
    EXPECT_EQ(plane.Normal, v1 ^ v2);
}

TEST(TPlane, Constructor_TwoLines_Parallel_NoThrows) {
    TPoint p1{0, 0, 0};
    TVector v{1, 0, 0};
    TLine line1{p1, v};
    TPoint p2{0, 1, 0};
    TLine lineParallel{p2, v};
    EXPECT_NO_THROW(TPlane(line1, lineParallel));
}

TEST(TPlane, PointLiesOnPlane) {
    TPoint p{0, 0, 0};
    TVector n{0, 0, 1};
    TPlane plane(p, n);
    TPoint onPlane{1, 2, 0};
    EXPECT_EQ(plane.distToPoint(onPlane), 0);
    EXPECT_TRUE(plane.containsPoint(onPlane));
}

TEST(TPlane, PointAbovePlane) {
    TPoint p{0, 0, 0};
    TVector n{0, 0, 1};
    TPlane plane(p, n);
    TPoint above{0, 0, 5};
    EXPECT_EQ(plane.distToPoint(above), 5);
    EXPECT_FALSE(plane.containsPoint(above));
}

TEST(TPlane, PointBelowPlane) {
    TPoint p{0, 0, 0};
    TVector n{0, 0, 1};
    TPlane plane(p, n);
    TPoint below{0, 0, -3};
    EXPECT_EQ(plane.distToPoint(below), 3);
    EXPECT_FALSE(plane.containsPoint(below));
}

TEST(TPlane, DistanceIsSymmetric) {
    TPoint p{0, 0, 0};
    TVector n{0, 0, 1};
    TPlane plane(p, n);
    TPoint above{0, 0, 2};
    TPoint below{0, 0, -2};
    EXPECT_EQ(plane.distToPoint(above), 2);
    EXPECT_EQ(plane.distToPoint(below), 2);
}

TEST(TPlane, PlaneDefinedByThreePoints) {
    TPoint a{0, 0, 0};
    TPoint b{1, 0, 0};
    TPoint c{0, 1, 0};
    TPlane plane(a, b, c);
    TPoint onPlane{0.5, 0.5, 0};
    TPoint offPlane{0.5, 0.5, 1};
    EXPECT_TRUE(plane.containsPoint(onPlane));
    EXPECT_FALSE(plane.containsPoint(offPlane));
    EXPECT_EQ(plane.distToPoint(offPlane), 1);
}

TEST(TPlane, PlaneDefinedByPointAndTwoVectors) {
    TPoint origin{0, 0, 0};
    TVector v1{1, 0, 0};
    TVector v2{0, 1, 0};
    TPlane plane(origin, v1, v2);
    TPoint onPlane{2, 3, 0};
    TPoint offPlane{2, 3, 5};
    EXPECT_TRUE(plane.containsPoint(onPlane));
    EXPECT_FALSE(plane.containsPoint(offPlane));
    EXPECT_EQ(plane.distToPoint(offPlane), 5);
}

TEST(TPlane, LineLiesInPlane2) {
    TPlane plane(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TLine line(TPoint{1, 2, 0}, TVector{1, 0, 0});
    EXPECT_TRUE(plane.containsLine(line));
}

TEST(TPlane, LineParallelButNotInPlane) {
    TPlane plane(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TLine line(TPoint{1, 2, 1}, TVector{1, 0, 0});
    EXPECT_FALSE(plane.containsLine(line));
}

TEST(TPlane, LineIntersectsButNotInPlane) {
    TPlane plane(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TLine line(TPoint{0, 0, 1}, TVector{0, 0, -1});
    EXPECT_FALSE(plane.containsLine(line));
}

TEST(TPlane, PlaneEqualityIdenticalPlanes) {
    TPlane p1(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TPlane p2(TPoint{0, 0, 0}, TVector{0, 0, 1});
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 != p2);
}

TEST(TPlane, PlaneEqualityDifferentPointsSameNormal) {
    TPlane p1(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TPlane p2(TPoint{1, 1, 0}, TVector{0, 0, 1});
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 != p2);
}

TEST(TPlane, PlaneEqualityOppositeNormal) {
    TPlane p1(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TPlane p2(TPoint{1, 1, 0}, TVector{0, 0, -1});
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 != p2);
}

TEST(TPlane, DifferentPlanes) {
    TPlane p1(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TPlane p2(TPoint{0, 0, 1}, TVector{0, 0, 1});
    EXPECT_FALSE(p1 == p2);
    EXPECT_TRUE(p1 != p2);
}

TEST(TPlane, NonParallelNormals) {
    TPlane p1(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TPlane p2(TPoint{0, 0, 0}, TVector{0, 1, 0});
    EXPECT_FALSE(p1 == p2);
    EXPECT_TRUE(p1 != p2);
}

TEST(TPlane, NearEqualPlanesWithTolerance) {
    TPlane p1(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TPlane p2(TPoint{NOT_TINY, -NOT_TINY, 0}, TVector{0, 0, 1 + NOT_TINY});
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 != p2);
}

TEST(TPlane, NearDifferentPlanesBeyondTolerance) {
    TPlane p1(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TPlane p2(TPoint{0, 0, NOT_TINY}, TVector{0, 0, 1});
    EXPECT_FALSE(p1 == p2);
    EXPECT_TRUE(p1 != p2);
}

TEST(TPlane, PlaneLineIntersectsAtSinglePoint) {
    TPlane plane(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TLine line(TPoint{1, 1, 1}, TVector{0, 0, -1});
    std::optional<std::pair<TPoint, TPointContainment>> result = plane.intersection(line);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().first, (TPoint{1, 1, 0}));
}

TEST(TPlane, PlaneLineParallelNoIntersection) {
    TPlane plane(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TLine line(TPoint{0, 0, 1}, TVector{1, 0, 0});
    std::optional<std::pair<TPoint, TPointContainment>> result = plane.intersection(line);
    EXPECT_FALSE(result.has_value());
}

TEST(TPlane, LineLiesInPlane) {
    TPlane plane(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TLine line(TPoint{1, 1, 0}, TVector{1, 0, 0});
    EXPECT_THROW(plane.intersection(line), std::runtime_error);
}

TEST(TPlane, PerpendicularIntersection) {
    TPlane plane(TPoint{0, 0, 0}, TVector{0, 1, 0});
    TLine line(TPoint{0, 1, 0}, TVector{0, -1, 0});
    std::optional<std::pair<TPoint, TPointContainment>> result = plane.intersection(line);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().first, (TPoint{0, 0, 0}));
}

TEST(TPlane, IntersectionAtOrigin) {
    TPlane plane(TPoint{0, 0, 0}, TVector{-1, 1, 1});
    TLine line(TPoint{1, -1, 0}, TVector{-1, 1, 0});
    std::optional<std::pair<TPoint, TPointContainment>> result = plane.intersection(line);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().first, (TPoint{0, 0, 0}));
}

TEST(TPlane, SkewLineIntersects) {
    TPlane plane(TPoint{0, 0, 0}, TVector{0, 1, 0});
    TLine line(TPoint{1, 1, 1}, TVector{-1, -1, -1});
    std::optional<std::pair<TPoint, TPointContainment>> result = plane.intersection(line);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().first, (TPoint{0, 0, 0}));
}

TEST(TPlane, LineParallelAndAbovePlane) {
    TPlane plane(TPoint{0, 0, 0}, TVector{0, 1, 0});
    TLine line(TPoint{0, 1, 0}, TVector{1, 0, 0});
    std::optional<std::pair<TPoint, TPointContainment>> result = plane.intersection(line);
    EXPECT_FALSE(result.has_value());
}

TEST(TPlane, LineParallelAndInPlane) {
    TPlane plane(TPoint{0, 0, 0}, TVector{0, 1, 0});
    TLine line(TPoint{1, 0, 1}, TVector{1, 0, 0});
    EXPECT_THROW(plane.intersection(line), std::runtime_error);
}

TEST(TPlane, TPlanePlaneIntersectsInLine) {
    TPlane plane1(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TPlane plane2(TPoint{0, 0, 1}, TVector{0, 1, -1});
    std::optional<TLine> result = plane1.intersection(plane2);
    ASSERT_TRUE(result.has_value());
    TPoint p = result->Point;
    EXPECT_EQ(p.Z, 0);
    TSafeDouble val = (p.X * plane2.Normal.X + p.Y * plane2.Normal.Y + p.Z * plane2.Normal.Z);
    TSafeDouble d =
        plane2.Normal.X * plane2.Point.X + plane2.Normal.Y * plane2.Point.Y + plane2.Normal.Z * plane2.Point.Z;
    EXPECT_EQ(val, d);
}

TEST(TPlane, PlanesAreEqual_Throws) {
    TPlane plane1(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TPlane plane2(TPoint{1, 1, 0}, TVector{0, 0, 1});
    EXPECT_THROW(plane1.intersection(plane2), std::runtime_error);
}

TEST(TPlane, PlanesAreParallelNoIntersection) {
    TPlane p1(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TPlane p2(TPoint{0, 0, 1}, TVector{0, 0, 1});
    std::optional<TLine> result = p1.intersection(p2);
    EXPECT_FALSE(result.has_value());
}

TEST(TPlane, Intersection_WithPerpendicularPlanes) {
    TPlane plane1(TPoint{0, 0, 0}, TVector{1, 0, 0});
    TPlane plane2(TPoint{0, 0, 0}, TVector{0, 1, 0});
    std::optional<TLine> result = plane1.intersection(plane2);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->Point, (TPoint{0, 0, 0}));
    EXPECT_EQ(result->Vector, (TVector{1, 0, 0} ^ TVector{0, 1, 0}));
}

TEST(TPlane, Intersection_WithSkewPlanes) {
    TPlane plane1(TPoint{0, 0, 0}, TVector{1, 1, 0});
    TPlane plane2(TPoint{0, 0, 1}, TVector{1, -1, 0});
    std::optional<TLine> result = plane1.intersection(plane2);
    ASSERT_TRUE(result.has_value());
    TPoint p = result->Point;
    EXPECT_EQ(plane1.Normal ^ plane2.Normal, result->Vector);
}

TEST(TPlane, Intersection_WithPlanesSharingLine) {
    TPlane plane1(TPoint{0, 0, 0}, TVector{0, 1, 0});
    TPlane plane2(TPoint{0, 0, 0}, TVector{1, 0, 0});
    std::optional<TLine> result = plane1.intersection(plane2);
    ASSERT_TRUE(result.has_value());
    TLine line = result.value();
    EXPECT_EQ(line.Point, (TPoint{0, 0, 0}));
    EXPECT_EQ(line.Vector, (TVector{0, 1, 0} ^ TVector{1, 0, 0}));
}

TEST(TPlane, Intersection_ParallelAndDifferentPoints) {
    TPlane plane1(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TPlane plane2(TPoint{0, 0, 1}, TVector{0, 0, 1});
    EXPECT_EQ(plane1.intersection(plane2), std::nullopt);
}

TEST(TPlane, Intersection_PerpendicularLineCrossingPlane) {
    TPlane plane(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TLine line(TPoint{1, 1, 1}, TVector{0, 0, -1});
    std::optional<std::pair<TPoint, TPointContainment>> result = plane.intersection(line);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().first, (TPoint{1, 1, 0}));
}

TEST(TPlane, Intersection_LineLiesInPlane) {
    TPlane plane(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TLine line(TPoint{1, 2, 0}, TVector{1, 0, 0});
    EXPECT_THROW(plane.intersection(line), std::runtime_error);
}

TEST(TPlane, Intersection_SkewLineNotIntersecting) {
    TPlane plane(TPoint{0, 0, 0}, TVector{0, 1, 0});
    TLine line(TPoint{1, 1, 2}, TVector{1, 0, 0});
    EXPECT_FALSE(plane.intersection(line).has_value());
}

TEST(TPlane, Intersection_LineParallelAbovePlane) {
    TPlane plane(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TLine line(TPoint{0, 0, 1}, TVector{1, 0, 0});
    EXPECT_FALSE(plane.intersection(line).has_value());
}

TEST(TPlane, Intersection_TwoPlanesAreIdentical) {
    TPlane p1(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TPlane p2(TPoint{0, 0, 0}, TVector{0, 0, 1});
    EXPECT_THROW(p1.intersection(p2), std::runtime_error);
}

TEST(TPlane, Intersection_TwoPlanesAreParallelButNotSame) {
    TPlane p1(TPoint{0, 0, 0}, TVector{0, 0, 1});
    TPlane p2(TPoint{0, 0, 1}, TVector{0, 0, 1});
    std::optional<TLine> result = p1.intersection(p2);
    EXPECT_FALSE(result.has_value());
}

TEST(TPlane, Intersection_ObliquePlanesCrossing) {
    TPlane p1(TPoint{0, 0, 0}, TVector{1, 0, 1});
    TPlane p2(TPoint{0, 0, 0}, TVector{0, 1, 1});
    std::optional<TLine> result = p1.intersection(p2);
    ASSERT_TRUE(result.has_value());
    TLine line = result.value();
    EXPECT_EQ(line.Point, (TPoint{0, 0, 0}));
    EXPECT_TRUE(line.Vector.isParallel(TVector{1, 0, 1} ^ TVector{0, 1, 1}));
}

TEST(TPlane, Intersection_WithVerticalPlaneAndHorizontalPlane) {
    TPlane vertical(TPoint{0, 0, 0}, TVector{1, 0, 0});
    TPlane horizontal(TPoint{0, 0, 0}, TVector{0, 0, 1});
    std::optional<TLine> result = vertical.intersection(horizontal);
    ASSERT_TRUE(result.has_value());
    TLine line = result.value();
    EXPECT_EQ(line.Point, (TPoint{0, 0, 0}));
    EXPECT_EQ(line.Vector, (TVector{1, 0, 0} ^ TVector{0, 0, 1}));
}
