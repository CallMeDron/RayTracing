#include "../ray_tracing_lib/all.h"

#include <gtest/gtest.h>
#include <random>

using namespace NRayTracingLib;

static constexpr double TINY = ACCURACY / 2.0;
static constexpr double NOT_TINY = ACCURACY * 2.0;

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

TEST(TPoint, LessDifferentX) {
    TPoint p1{0.0, 0.0, 0.0};
    TPoint p2{1.0, 0.0, 0.0};
    EXPECT_TRUE(p1 < p2);
    EXPECT_FALSE(p2 < p1);
}

TEST(TPoint, LessDifferentY) {
    TPoint p1{1.0, 0.0, 0.0};
    TPoint p2{1.0, 1.0, 0.0};
    EXPECT_TRUE(p1 < p2);
    EXPECT_FALSE(p2 < p1);
}

TEST(TPoint, LessDifferentZ) {
    TPoint p1{1.0, 1.0, 0.0};
    TPoint p2{1.0, 1.0, 1.0};
    EXPECT_TRUE(p1 < p2);
    EXPECT_FALSE(p2 < p1);
}

TEST(TPoint, EqualPoints) {
    TPoint p1{2.0, 3.0, 4.0};
    TPoint p2{2.0, 3.0, 4.0};
    EXPECT_FALSE(p1 < p2);
    EXPECT_FALSE(p2 < p1);
    EXPECT_TRUE(p1 == p2);
}

TEST(TPoint, LessWithNegativeValues) {
    TPoint p1{-1.0, 0.0, 0.0};
    TPoint p2{0.0, 0.0, 0.0};
    EXPECT_TRUE(p1 < p2);
}

TEST(TPoint, SortingOrder) {
    std::vector<TPoint> points = {TPoint{1.0, 2.0, 3.0}, TPoint{0.0, 5.0, 6.0}, TPoint{1.0, 2.0, 2.0},
                                  TPoint{0.0, 4.0, 7.0}};

    std::vector<TPoint> expected_sorted = {TPoint{0.0, 4.0, 7.0}, TPoint{0.0, 5.0, 6.0}, TPoint{1.0, 2.0, 2.0},
                                           TPoint{1.0, 2.0, 3.0}};

    std::sort(points.begin(), points.end());
    EXPECT_EQ(points, expected_sorted);
}

TEST(TPoint, NoInfiniteLoopOnSort) {
    std::vector<TPoint> points;
    for (int i = 0; i < 1000; ++i) {
        points.push_back(TPoint{i, i * 2, i * 3});
    }
    std::vector<TPoint> shuffled_points = points;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(shuffled_points.begin(), shuffled_points.end(), gen);
    std::sort(shuffled_points.begin(), shuffled_points.end());
    EXPECT_EQ(shuffled_points, points);
}

TEST(TPoint, ConsistencyWithEquality) {
    TPoint p1{5.2, -3.1, 0.0};
    TPoint p2{5.2, -3.1, 0.0};
    EXPECT_FALSE(p1 < p2);
    EXPECT_FALSE(p2 < p1);
    EXPECT_FALSE(p1 < p1);
}

TEST(TPoint, LongDistanceCalculation) {
    TPoint p1{0.0, 0.0, 0.0};
    TPoint p2{1e6, -1e6, 1e6};
    auto dist = p1.distToPoint(p2);
    EXPECT_EQ(dist.Value, std::sqrt(3 * 1e12));
}

TEST(TPoint, DistanceToLine_PerpendicularPoint) {
    TPoint p{0.0, 1.0, 0.0};
    TLine line{TPoint{0.0, 0.0, 0.0}, TVector{1.0, 0.0, 0.0}};
    EXPECT_EQ(p.distToLine(line).Value, 1.0);
}

TEST(TPoint, DistanceToLine_AlongLine) {
    TPoint p{5.0, 0.0, 0.0};
    TLine line{TPoint{0.0, 0.0, 0.0}, TVector{1.0, 0.0, 0.0}};
    EXPECT_EQ(p.distToLine(line).Value, 0.0);
}

TEST(TPoint, DistanceToLine_FarAway) {
    TPoint p{0.0, 100.0, 100.0};
    TLine line{TPoint{0.0, 0.0, 0.0}, TVector{1.0, 0.0, 0.0}};
    EXPECT_EQ(p.distToLine(line).Value, sqrt(100.0 * 100.0 + 100.0 * 100.0));
}

TEST(TPoint, InsertAndFindClosePoints) {
    std::unordered_set<TPoint> points;
    TPoint p1{1.0, 2.0, 3.0};
    TPoint p2{1.0 + TINY / 2.0, 2.0, 3.0};
    points.insert(p1);
    EXPECT_TRUE(points.find(p2) != points.end());
    TPoint p3{1.0 + NOT_TINY, 2.0, 3.0};
    EXPECT_TRUE(points.find(p3) == points.end());
}

TEST(TPoint, HashConsistencyForClosePoints) {
    TPoint p1{1.23456, 7.89012, 3.45678};
    TPoint p2{1.23456 + TINY / 2, 7.89012, 3.45678};
    std::hash<TPoint> hasher;
    EXPECT_EQ(hasher(p1), hasher(p2));
}

TEST(TPoint, HashDivergesForDistinctPoints) {
    TPoint p1{1.0, 2.0, 3.0};
    TPoint p2{1.0 + NOT_TINY, 2.0, 3.0};
    std::hash<TPoint> hasher;
    EXPECT_NE(hasher(p1), hasher(p2));
}

TEST(TPoint, LessOrderForVariousPoints) {
    TPoint p1{0.0, 0.0, 0.0};
    TPoint p2{0.0, 0.0, 1.0};
    TPoint p3{0.0, 1.0, 0.0};
    TPoint p4{1.0, 0.0, 0.0};
    EXPECT_TRUE(p1 < p2);
    EXPECT_TRUE(p2 < p3);
    EXPECT_TRUE(p3 < p4);
    EXPECT_FALSE(p4 < p1);
}

TEST(TPoint, SortingMultiplePoints) {
    std::vector<TPoint> pts = {TPoint{2.0, 0.0, 0.0}, TPoint{0.0, 3.0, 0.0}, TPoint{0.0, 0.0, 4.0},
                               TPoint{1.0, 1.0, 1.0}};
    std::vector<TPoint> sortedPts = pts;
    std::sort(sortedPts.begin(), sortedPts.end());
    EXPECT_EQ(sortedPts[0], (TPoint{0.0, 0.0, 4.0}));
    EXPECT_EQ(sortedPts[1], (TPoint{0.0, 3.0, 0.0}));
    EXPECT_EQ(sortedPts[2], (TPoint{1.0, 1.0, 1.0}));
    EXPECT_EQ(sortedPts[3], (TPoint{2.0, 0.0, 0.0}));
}

TEST(TPoint, InsertMultipleCloseAndFarPoints) {
    std::unordered_set<TPoint> set;
    set.insert(TPoint{1.0, 2.0, 3.0});
    set.insert(TPoint{1.0 + TINY / 2, 2.0, 3.0});
    set.insert(TPoint{1.0 + NOT_TINY, 2.0, 3.0});
    EXPECT_EQ(set.size(), 2u);
}

TEST(TPoint, DistToPointZeroDistance) {
    TPoint p{5.0, -3.0, 10.0};
    EXPECT_EQ(p.distToPoint(p).Value, 0.0);
}

TEST(TPoint, DistToLineWithNegativeCoordinates) {
    TPoint p{-10.0, -10.0, -10.0};
    TLine line{TPoint{-20.0, 0.0, 0.0}, TVector{1.0, 0.0, 0.0}};
    EXPECT_EQ(p.distToLine(line).Value, sqrt(200));
}

TEST(TPoint, LargeCoordinatesDistance) {
    TPoint p1{1e12, -1e12, 1e12};
    TPoint p2{-1e12, 1e12, -1e12};
    auto dist = p1.distToPoint(p2);
    EXPECT_EQ(dist.Value, std::sqrt(3 * 4e24));
}

TEST(TPoint, DistanceBetweenClosePointsIsCorrect) {
    TPoint p1{0.0, 0.0, 0.0};
    TPoint p2{TINY, TINY, TINY};
    auto dist = p1.distToPoint(p2);
    auto expected = TSafeDouble{std::sqrt(3.0 * TINY * TINY)};
    EXPECT_EQ(dist.Value, expected.Value);
}

TEST(TPoint, EqualityWithCoordinatesCloseToZero) {
    TPoint p1{TINY / 2, TINY / 2, TINY / 2};
    TPoint p2{TINY / 2 + ACCURACY / 4, TINY / 2 + ACCURACY / 4, TINY / 2 + ACCURACY / 4};
    EXPECT_TRUE(p1 == p2);
}

TEST(TPoint, InequalityWithCoordinatesExceedingTolerance) {
    TPoint p1{1.0, 2.0, 3.0};
    TPoint p2{1.0 + TINY, 2.0, 3.0};
    EXPECT_TRUE(p1 == p2);
}

TEST(TPoint, ComparisonOperatorsOnEdgeCases) {
    TPoint p1{0.0, 0.0, 0.0};
    TPoint p2{0.0, 0.0, TINY / 2};
    EXPECT_FALSE(p1 < p2);
    EXPECT_FALSE(p2 < p1);
}

TEST(TPoint, HashingConsistentForEqualPoints) {
    TPoint p1{9.8, -7.6, 5.4};
    TPoint p2{9.8 + TINY / 2, -7.6, 5.4};
    std::hash<TPoint> hasher;
    EXPECT_EQ(hasher(p1), hasher(p2));
}

TEST(TPoint, HashingDifferentForDifferentPoints) {
    TPoint p1{1.0, 2.0, 3.0};
    TPoint p2{1.0 + NOT_TINY, 2.0, 3.0};
    std::hash<TPoint> hasher;
    EXPECT_NE(hasher(p1), hasher(p2));
}
