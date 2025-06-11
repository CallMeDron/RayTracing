#include "../ray_tracing_lib/all.h"

#include <gtest/gtest.h>
#include <unordered_set>

using namespace NRayTracingLib;

const double TINY = ACCURACY / 2.0;
const double NOT_TINY = ACCURACY * 2.0;

//=== TPoint Tests ===

TEST(TPoint, EqualityOperators_WorkCorrectly) {
    TPoint p1{1.0, 2.0, 3.0};
    TPoint p2{1.0, 2.0, 3.0};
    TPoint p3{1.0, 2.0, 4.0};

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 != p2);
    EXPECT_FALSE(p1 == p3);
    EXPECT_TRUE(p1 != p3);
}

TEST(TPoint, OperatorMinus_ReturnsVectorDifference) {
    TPoint p1{1.0, 2.0, 3.0};
    TPoint p2{0.5, 1.5, 2.0};

    TVector v = p1 - p2;
    EXPECT_DOUBLE_EQ(v.X.Value, 0.5);
    EXPECT_DOUBLE_EQ(v.Y.Value, 0.5);
    EXPECT_DOUBLE_EQ(v.Z.Value, 1.0);
}

TEST(TPoint, OperatorPlus_AddsVectorToPoint) {
    TPoint p{1.0, 2.0, 3.0};
    TVector v{0.5, 0.5, 0.5};

    TPoint p2 = p + v;
    EXPECT_DOUBLE_EQ(p2.X.Value, 1.5);
    EXPECT_DOUBLE_EQ(p2.Y.Value, 2.5);
    EXPECT_DOUBLE_EQ(p2.Z.Value, 3.5);
}

TEST(TPoint, DistToPoint_ComputesDistanceCorrectly) {
    TPoint p1{0.0, 0.0, 0.0};
    TPoint p2{3.0, 4.0, 0.0};

    auto dist = p1.distToPoint(p2);
    EXPECT_DOUBLE_EQ(dist.Value, 5.0);
}

TEST(TPoint, DistToLine_ComputesDistanceCorrectly) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector dir{1.0, 0.0, 0.0};
    TLine line{origin, dir};

    EXPECT_DOUBLE_EQ((TPoint{1.0, 0.0, 0.0}).distToLine(line).Value, 0.0);
    EXPECT_DOUBLE_EQ((TPoint{0.0, 0.0, 0.0}).distToLine(line).Value, 0.0);
    EXPECT_DOUBLE_EQ((TPoint{10000.0, 0.0, 0.0}).distToLine(line).Value, 0.0);
    EXPECT_DOUBLE_EQ((TPoint{10000.0, 5.0, 0.0}).distToLine(line).Value, 5.0);
    EXPECT_DOUBLE_EQ((TPoint{10000.0, 3.0, 4.0}).distToLine(line).Value, 5.0);
}

TEST(TPoint, InsertAndFind_ExactSamePoint) {
    std::unordered_set<TPoint> pointSet;
    TPoint p1{1.234, 5.678, 9.1011};

    pointSet.insert(p1);
    EXPECT_EQ(pointSet.size(), 1u);
    EXPECT_NE(pointSet.find(p1), pointSet.end());
}

TEST(TPoint, InsertAndFind_ClosePoints) {
    std::unordered_set<TPoint> pointSet;
    TPoint p1{1.0, 2.0, 3.0};
    TPoint p2{1.0 + TINY, 2.0, 3.0};

    pointSet.insert(p1);
    EXPECT_TRUE(pointSet.contains(p2));
}

TEST(TPoint, DifferentPoints_NotFound) {
    std::unordered_set<TPoint> pointSet;
    TPoint p1{1.0, 2.0, 3.0};
    TPoint p2{1.0 + NOT_TINY, 2.0, 3.0};

    pointSet.insert(p1);
    EXPECT_FALSE(pointSet.contains(p2));
}

TEST(TPoint, InsertMultiple_DifferentPoints) {
    std::unordered_set<TPoint> pointSet;
    TPoint p1{0.0, 0.0, 0.0};
    TPoint p2{0.0 + TINY, 0.0, 0.0};
    TPoint p3{0.0 + NOT_TINY, 0.0, 0.0};

    pointSet.insert(p1);
    EXPECT_EQ(pointSet.size(), 1u);

    pointSet.insert(p2);
    EXPECT_EQ(pointSet.size(), 1u);

    pointSet.insert(p3);
    EXPECT_EQ(pointSet.size(), 2u);
}

TEST(TPoint, Hash_IsConsistentForEquivalentPoints) {
    TPoint p1{123.456789, 987.654321, 0.123456};
    TPoint p2 = p1;
    TPoint p3{123.456789 + TINY, 987.654321 - TINY, 0.123456 + TINY};

    std::hash<TPoint> hasher;
    EXPECT_EQ(hasher(p1), hasher(p2));
    EXPECT_EQ(hasher(p1), hasher(p3));
}

TEST(TPoint, Hash_IsDifferentForDistinctPoints) {
    TPoint p1{1.0, 2.0, 3.0};
    TPoint p2{1.0 + NOT_TINY, 2.0, 3.0};

    std::hash<TPoint> hasher;
    EXPECT_NE(hasher(p1), hasher(p2));
}

TEST(TPoint, ConstructorWithCoordinates) {
    TPoint p{1.1, 2.2, 3.3};
    EXPECT_DOUBLE_EQ(p.X.Value, 1.1);
    EXPECT_DOUBLE_EQ(p.Y.Value, 2.2);
    EXPECT_DOUBLE_EQ(p.Z.Value, 3.3);
}

TEST(TPoint, DistToPoint_IdenticalPoints) {
    TPoint p{1.0, 2.0, 3.0};
    EXPECT_DOUBLE_EQ(p.distToPoint(p).Value, 0.0);
}

TEST(TPoint, DistToLine_PointOnLine) {
    TPoint p{0.0, 0.0, 0.0};
    TLine line{p, TVector{1.0, 0.0, 0.0}};
    EXPECT_DOUBLE_EQ(p.distToLine(line).Value, 0.0);
}

TEST(TPoint, DistToLine_PointFarAway) {
    TPoint p{0.0, 100.0, 0.0};
    TLine line{TPoint{0.0, 0.0, 0.0}, TVector{1.0, 0.0, 0.0}};
    EXPECT_NEAR(p.distToLine(line).Value, 100.0, TINY);
}

TEST(TPoint, NegativeCoordinates) {
    TPoint p1{-1.0, -2.0, -3.0};
    TPoint p2{-4.0, -5.0, -6.0};
    auto dist = p1.distToPoint(p2);
    EXPECT_NEAR(dist.Value, std::sqrt(3 * 3 + 3 * 3 + 3 * 3), TINY);
}

TEST(TPoint, ZeroVector) {
    TVector v{0.0, 0.0, 0.0};
    TPoint p{1.0, 1.0, 1.0};
    TPoint p2 = p + v;
    EXPECT_DOUBLE_EQ(p2.X.Value, 1.0);
    EXPECT_DOUBLE_EQ(p2.Y.Value, 1.0);
    EXPECT_DOUBLE_EQ(p2.Z.Value, 1.0);
}

TEST(TPoint, LargeCoordinates) {
    TPoint p{1e9, -1e9, 1e9};
    TPoint q{-1e9, 1e9, -1e9};
    auto dist = p.distToPoint(q);
    EXPECT_NEAR(dist.Value, std::sqrt(12 * 1e18), TINY);
}

TEST(TPoint, InsertClosePointsBehavior) {
    std::unordered_set<TPoint> pointSet;
    TPoint p1{0.0, 0.0, 0.0};
    TPoint p2{TINY, 0.0, 0.0};
    pointSet.insert(p1);
    pointSet.insert(p2);
    EXPECT_EQ(pointSet.size(), 1u);
}

TEST(TPoint, InsertFarPointsBehavior) {
    std::unordered_set<TPoint> pointSet;
    TPoint p1{0.0, 0.0, 0.0};
    TPoint p2{NOT_TINY, 0.0, 0.0};
    pointSet.insert(p1);
    pointSet.insert(p2);
    EXPECT_EQ(pointSet.size(), 2u);
}

TEST(TPoint, HashesForClosePoints) {
    TPoint p1{1.0, 2.0, 3.0};
    TPoint p2{1.0 + TINY, 2.0 + TINY, 3.0 + TINY};
    std::hash<TPoint> hasher;
    EXPECT_EQ(hasher(p1), hasher(p2));
}

TEST(TPoint, HashesForDifferentPoints) {
    TPoint p1{1.0, 2.0, 3.0};
    TPoint p2{1.0 + NOT_TINY, 2.0, 3.0};
    std::hash<TPoint> hasher;
    EXPECT_NE(hasher(p1), hasher(p2));
}