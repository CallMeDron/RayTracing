#include "..\ray_tracing_lib\line.h"
#include "..\ray_tracing_lib\plane.h"
#include "..\ray_tracing_lib\point.h"
#include "..\ray_tracing_lib\polygon.h"
#include "..\ray_tracing_lib\safe_double.h"
#include "..\ray_tracing_lib\vector.h"

#include <gtest/gtest.h>

using namespace NRayTracingLib;

//=== TSafeDouble tests ===

TEST(TSafeDouble, Constructor_SetsValueCorrectly) {
    TSafeDouble a(3.14);
    EXPECT_DOUBLE_EQ(a.Value, 3.14);
}

TEST(TSafeDouble, EqualityOperator_WithinTolerance_ReturnsTrue) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 + (ACCURACY / 10));
    EXPECT_TRUE(a == b);
}

TEST(TSafeDouble, EqualityOperator_OutsideTolerance_ReturnsFalse) {
    TSafeDouble a(1.0);
    TSafeDouble c(1.0 + (ACCURACY * 10));
    EXPECT_FALSE(a == c);
}

TEST(TSafeDouble, InequalityOperator_OutsideTolerance_ReturnsTrue) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 + (ACCURACY * 10));
    EXPECT_TRUE(a != b);
}

TEST(TSafeDouble, InequalityOperator_WithinTolerance_ReturnsFalse) {
    TSafeDouble a(1.0);
    TSafeDouble c(1.0 + (ACCURACY / 10));
    EXPECT_FALSE(a != c);
}

TEST(TSafeDouble, GreaterThanOperator_CorrectBehavior) {
    TSafeDouble a(2.0);
    TSafeDouble b(1.0);
    EXPECT_TRUE(a > b);
    EXPECT_FALSE(b > a);
    TSafeDouble c(2.0 + (ACCURACY / 10));
    EXPECT_FALSE(a > c);
}

TEST(TSafeDouble, LessThanOperator_CorrectBehavior) {
    TSafeDouble a(1.0);
    TSafeDouble b(2.0);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
    TSafeDouble c(1.0 - (ACCURACY / 10));
    EXPECT_FALSE(a < c);
}

TEST(TSafeDouble, GreaterEqualOperator_CorrectBehavior) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 + (ACCURACY / 10));
    TSafeDouble c(0.9);
    EXPECT_TRUE(a >= b);
    EXPECT_TRUE(a >= c);
    EXPECT_FALSE(c >= a);
}

TEST(TSafeDouble, LessEqualOperator_CorrectBehavior) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 - (ACCURACY / 10));
    TSafeDouble c(1.1);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a <= c);
    EXPECT_FALSE(c <= a);
}

TEST(TSafeDouble, UnaryMinusOperator_NegatesValue) {
    TSafeDouble a(5.0);
    TSafeDouble b = -a;
    EXPECT_DOUBLE_EQ(b.Value, -5.0);
    TSafeDouble c = -b;
    EXPECT_DOUBLE_EQ(c.Value, 5.0);
}

TEST(TSafeDouble, AbsMethod_ReturnsAbsoluteValue) {
    TSafeDouble a(-3.5);
    TSafeDouble b(3.5);
    TSafeDouble c(0.0);
    EXPECT_DOUBLE_EQ(a.abs().Value, 3.5);
    EXPECT_DOUBLE_EQ(b.abs().Value, 3.5);
    EXPECT_DOUBLE_EQ(c.abs().Value, 0.0);
}

TEST(TSafeDouble, AdditionOperator_AddsValues) {
    TSafeDouble a(1.5);
    TSafeDouble b(2.5);
    TSafeDouble c = a + b;
    EXPECT_DOUBLE_EQ(c.Value, 4.0);
}

TEST(TSafeDouble, SubtractionOperator_SubtractsValues) {
    TSafeDouble a(5.0);
    TSafeDouble b(3.0);
    TSafeDouble c = a - b;
    EXPECT_DOUBLE_EQ(c.Value, 2.0);
}

TEST(TSafeDouble, MultiplicationOperator_MultipliesValues) {
    TSafeDouble a(2.0);
    TSafeDouble b(4.0);
    TSafeDouble c = a * b;
    EXPECT_DOUBLE_EQ(c.Value, 8.0);
}

TEST(TSafeDouble, DivisionOperator_DividesValues) {
    TSafeDouble a(10.0);
    TSafeDouble b(2.0);
    TSafeDouble c = a / b;
    EXPECT_DOUBLE_EQ(c.Value, 5.0);
}

TEST(TSafeDouble, DivisionOperator_DivideByZero_Throws) {
    TSafeDouble a(1.0);
    TSafeDouble zero(0.0);
    EXPECT_THROW(a / zero, std::runtime_error);
}

TEST(TSafeDouble, CompoundAdditionOperator_AddsAndAssigns) {
    TSafeDouble a(1.0);
    TSafeDouble b(2.0);
    a += b;
    EXPECT_DOUBLE_EQ(a.Value, 3.0);
}

TEST(TSafeDouble, CompoundSubtractionOperator_SubtractsAndAssigns) {
    TSafeDouble a(5.0);
    TSafeDouble b(3.0);
    a -= b;
    EXPECT_DOUBLE_EQ(a.Value, 2.0);
}

TEST(TSafeDouble, CompoundMultiplicationOperator_MultipliesAndAssigns) {
    TSafeDouble a(3.0);
    TSafeDouble b(4.0);
    a *= b;
    EXPECT_DOUBLE_EQ(a.Value, 12.0);
}

TEST(TSafeDouble, CompoundDivisionOperator_DividesAndAssigns) {
    TSafeDouble a(8.0);
    TSafeDouble b(2.0);
    a /= b;
    EXPECT_DOUBLE_EQ(a.Value, 4.0);
}

TEST(TSafeDouble, PowMethod_RaisesToPower) {
    TSafeDouble a(2.0);
    TSafeDouble b(3.0);
    TSafeDouble c = a.pow(b);
    EXPECT_DOUBLE_EQ(c.Value, 8.0);
}

//=== TPoint tests ===

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

//=== TVector tests ===

TEST(TVector, Constructor_FromPointAndCoordinates_WorksCorrectly) {
    TPoint p{1.0, 2.0, 3.0};
    TVector fromPoint{p};
    TVector fromCoords{1.0, 2.0, 3.0};
    EXPECT_EQ(fromPoint, fromCoords);

    TPoint a{1.0, 2.0, 3.0};
    TPoint b{2.0, 3.0, 4.0};
    TVector diff{1.0, 1.0, 1.0};
    EXPECT_EQ(TVector(a, b), diff);
}

TEST(TVector, AdditionAndSubtraction_WorksCorrectly) {
    TVector a{1.0, 2.0, 3.0};
    TVector b{4.0, 3.0, 2.0};
    TVector sum{5.0, 5.0, 5.0};
    TVector diff{-3.0, -1.0, 1.0};
    EXPECT_EQ(a + b, sum);
    EXPECT_EQ(a - b, diff);
}

TEST(TVector, MultiplicationAndDivision_ByScalar_WorksCorrectly) {
    TVector a{1.0, 2.0, 3.0};
    TVector b{3.0, 6.0, 9.0};
    EXPECT_EQ(a * 3.0, b);
    EXPECT_EQ(b / 3.0, a);
    EXPECT_THROW(b / (ACCURACY / 10), std::runtime_error);
}

TEST(TVector, ScalarProduct_ComputesCorrectly) {
    TVector a{1.0, 2.0, 3.0};
    TVector b{3.0, 6.0, 9.0};
    EXPECT_EQ(a * b, 42.0);
}

TEST(TVector, VectorProduct_ComputesCorrectly) {
    TVector a{1.0, 2.0, 3.0};
    TVector b{3.0, 2.0, 1.0};
    TVector expected{-4.0, 8.0, -4.0};
    EXPECT_EQ(a ^ b, expected);
}

TEST(TVector, Length_ComputesCorrectly) {
    TVector v{0.0, 3.0, 4.0};
    EXPECT_EQ(v.length(), 5.0);
}

TEST(TVector, Normalization_WorksCorrectly) {
    TVector v{0.0, 3.0, 4.0};
    v.normalize();
    TVector expected{0.0, 0.6, 0.8};
    EXPECT_EQ(v, expected);

    TVector v2{0.0, 3.0, 4.0};
    EXPECT_EQ(v2.getNormalized(), expected);

    TVector zeroVec{0.0, 0.0, 0.0};
    EXPECT_THROW(zeroVec.getNormalized(), std::runtime_error);
}

TEST(TVector, CosineOfAngle_ComputesCorrectly) {
    TVector a{1.0, 2.0, 3.0};
    TVector b{3.0, 2.0, 1.0};
    EXPECT_DOUBLE_EQ(a.cos(b).Value, 5.0 / 7.0);
    EXPECT_DOUBLE_EQ(b.cos(a).Value, 5.0 / 7.0);
}

TEST(TVector, IsParallel_ReturnsCorrectly) {
    TVector a{1.0, 2.0, 3.0};
    TVector b{5.0, 10.0, 15.0};
    EXPECT_TRUE(a.isParallel(a));
    EXPECT_TRUE(a.isParallel(-a));
    EXPECT_TRUE(a.isParallel(b));
    EXPECT_TRUE(b.isParallel(a));

    TVector zeroVec{0.0, 0.0, 0.0};
    EXPECT_THROW(zeroVec.isParallel(zeroVec), std::runtime_error);

    TVector c{6.0, 10.0, 15.0};
    EXPECT_FALSE(a.isParallel(c));
    EXPECT_FALSE(c.isParallel(a));

    TVector d{5.0 + (ACCURACY / 10), 10.0 + (ACCURACY / 10), 15.0 + (ACCURACY / 10)};
    EXPECT_TRUE(d.isParallel(b));
}

TEST(TVector, IsPerpendicular_ReturnsCorrectly) {
    TVector x{1.0, 0.0, 0.0};
    TVector y{0.0, 1.0, 0.0};
    TVector z{0.0, 0.0, 1.0};
    EXPECT_TRUE(x.isPerpendicular(y));
    EXPECT_TRUE(x.isPerpendicular(z));
    EXPECT_TRUE(y.isPerpendicular(x));
    EXPECT_TRUE(y.isPerpendicular(z));
    EXPECT_TRUE(z.isPerpendicular(x));
    EXPECT_TRUE(z.isPerpendicular(y));

    TVector w{6.0, 10.0, 15.0};
    EXPECT_FALSE(x.isPerpendicular(w));
    EXPECT_FALSE(w.isPerpendicular(x));

    TVector v{0.0 + (ACCURACY / 10), 1.0 + (ACCURACY / 10), 0.0 + (ACCURACY / 10)};
    EXPECT_TRUE(v.isPerpendicular(x));
}

TEST(TVector, Projection_ReturnsCorrectProjection) {
    TVector x{1.0, 0.0, 0.0};
    TVector y{0.0, 1.0, 0.0};
    EXPECT_EQ(x.projectTo(x), x);
    EXPECT_TRUE(x.projectTo(y).isZero());

    TVector v{1.0, 2.0, 3.0};
    TVector w{-3.0, 2.0, 7.0};
    TVector expected{-33.0 / 31.0, 22.0 / 31.0, 77.0 / 31.0};
    EXPECT_EQ(v.projectTo(w), expected);
}

//=== TLine tests ===

TEST(TLine, CosineOfAngle_ComputesCorrectly) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector x{1.0, 2.0, 3.0};
    TVector y{3.0, 2.0, 1.0};
    TLine lineX{origin, x};
    TLine lineY{origin, y};
    EXPECT_DOUBLE_EQ(lineX.cos(lineY).Value, 5.0 / 7.0);
    EXPECT_DOUBLE_EQ(lineY.cos(lineX).Value, 5.0 / 7.0);
}

TEST(TLine, IsParallel_ReturnsCorrectly) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector x{1.0, 2.0, 3.0};
    TVector y{5.0, 10.0, 15.0};
    TLine lineX{origin, x};
    TLine lineY{origin, y};
    EXPECT_TRUE(lineX.isParallel(lineX));
    EXPECT_TRUE(lineX.isParallel(lineY));
    EXPECT_TRUE(lineY.isParallel(lineX));

    TVector zeroVec{0.0, 0.0, 0.0};
    EXPECT_THROW(TLine(origin, zeroVec), std::runtime_error);

    TVector w{6.0, 10.0, 15.0};
    TLine lineW{origin, w};
    EXPECT_FALSE(lineX.isParallel(lineW));
    EXPECT_FALSE(lineW.isParallel(lineX));

    TVector v{5.0 + (ACCURACY / 10), 10.0 + (ACCURACY / 10), 15.0 + (ACCURACY / 10)};
    TLine lineV{origin, v};
    EXPECT_TRUE(lineV.isParallel(lineY));
}

TEST(TLine, IsPerpendicular_ReturnsCorrectly) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector x{1.0, 0.0, 0.0};
    TVector y{0.0, 1.0, 0.0};
    TVector z{0.0, 0.0, 1.0};
    TLine lineX{origin, x};
    TLine lineY{origin, y};
    TLine lineZ{origin, z};
    EXPECT_TRUE(lineX.isPerpendicular(lineY));
    EXPECT_TRUE(lineX.isPerpendicular(lineZ));
    EXPECT_TRUE(lineY.isPerpendicular(lineX));
    EXPECT_TRUE(lineY.isPerpendicular(lineZ));
    EXPECT_TRUE(lineZ.isPerpendicular(lineX));
    EXPECT_TRUE(lineZ.isPerpendicular(lineY));

    TVector w{6.0, 10.0, 15.0};
    TLine lineW{origin, w};
    EXPECT_FALSE(lineX.isPerpendicular(lineW));
    EXPECT_FALSE(lineW.isPerpendicular(lineX));

    TVector v{0.0 + (ACCURACY / 10), 1.0 + (ACCURACY / 10), 0.0 + (ACCURACY / 10)};
    TLine lineV{origin, v};
    EXPECT_TRUE(lineV.isPerpendicular(lineX));
}

TEST(TLine, DistToPoint_ComputesCorrectly) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector dir{1.0, 0.0, 0.0};
    TLine line{origin, dir};

    EXPECT_DOUBLE_EQ(line.distToPoint(TPoint{1.0, 0.0, 0.0}).Value, 0.0);
    EXPECT_DOUBLE_EQ(line.distToPoint(TPoint{0.0, 0.0, 0.0}).Value, 0.0);
    EXPECT_DOUBLE_EQ(line.distToPoint(TPoint{10000.0, 0.0, 0.0}).Value, 0.0);
    EXPECT_DOUBLE_EQ(line.distToPoint(TPoint{10000.0, 5.0, 0.0}).Value, 5.0);
    EXPECT_DOUBLE_EQ(line.distToPoint(TPoint{10000.0, 3.0, 4.0}).Value, 5.0);
}

TEST(TLine, ContainsPoint_ReturnsCorrectly) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector dir{1.0, 0.0, 0.0};
    TLine line{origin, dir};

    EXPECT_TRUE(line.containsPoint(origin));
    EXPECT_TRUE(line.containsPoint(TPoint{1.0, 0.0, 0.0}));
    EXPECT_FALSE(line.containsPoint(TPoint{1.0 + (ACCURACY * 10), -(ACCURACY * 10), -(ACCURACY * 10)}));
    EXPECT_TRUE(line.containsPoint(TPoint{1.0 + (ACCURACY / 10), -(ACCURACY / 10), -(ACCURACY / 10)}));
}

TEST(TLine, EqualityOperators_WorkCorrectly) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector x{1.0, 0.0, 0.0};
    TVector y{1.0 + 0.01, -0.01, -0.01};
    TVector z{1.0 + (ACCURACY / 10), -(ACCURACY / 10), -(ACCURACY / 10)};
    TLine lineX{origin, x};
    TLine lineY{origin, y};
    TLine lineZ{origin, z};

    EXPECT_EQ(lineX, lineZ);
    EXPECT_EQ(lineZ, lineX);
    EXPECT_NE(lineX, lineY);
    EXPECT_NE(lineY, lineX);
    EXPECT_NE(lineY, lineZ);
    EXPECT_NE(lineZ, lineY);
}

TEST(TLine, Intersection_ReturnsCorrectPointOrThrows) {
    TPoint p1{0.0, 0.0, 0.0};
    TVector v1{1.0, 1.0, 1.0};
    TLine l1{p1, v1};

    TPoint p2{1.0, 0.0, 0.0};
    TVector v2{0.0, 1.0, 1.0};
    TLine l2{p2, v2};

    EXPECT_EQ(l1.intersection(l2), TPoint(1.0, 1.0, 1.0));

    TPoint p3{0.0, 0.0, 0.0};
    TVector v3{1.0, 1.0, 1.0};
    TLine l3{p3, v3};

    TPoint p4{1.0, 0.0, 0.0};
    TVector v4{1.0, 1.0, 1.0};
    TLine l4{p4, v4};

    EXPECT_EQ(l3.intersection(l4), std::nullopt);

    TPoint p5{0.0, 0.0, 0.0};
    TVector v5{1.0, 1.0, 1.0};
    TLine l5{p5, v5};

    TPoint p6{1.0, 1.0, 1.0};
    TVector v6{1.0, 1.0, 1.0};
    TLine l6{p6, v6};

    EXPECT_THROW(l5.intersection(l6), std::runtime_error);

    TPoint p7{1.0, 2.0, 3.0};
    TVector v7{-1.0, -2.0, -3.0};
    TLine l7{p7, v7};

    TPoint p8{13.0, -4.0, 5.0};
    TVector v8{-13.0, 4.0, -5.0};
    TLine l8{p8, v8};

    EXPECT_EQ(l7.intersection(l8), TPoint(0.0, 0.0, 0.0));
}

//=== TPlane tests ===

class TPlaneTest : public ::testing::Test {
  protected:
    TPoint p1{0, 0, 0};
    TPoint p2{1, 0, 0};
    TPoint p3{0, 1, 0};
    TPoint p4{0, 0, 1};

    TVector v1{1, 0, 0};
    TVector v2{0, 1, 0};
    TVector v3{0, 0, 1};
    TVector zeroVec{0, 0, 0};

    TLine line1{p1, v1};
    TLine line2{p1, v2};
    TLine line3{p4, v3};
    TLine lineParallel{p2, v1};
};

TEST_F(TPlaneTest, Constructor_PointAndNormal_ValidNormal_Succeeds) {
    TPlane plane(p1, v3);
    EXPECT_EQ(plane.Point, p1);
    EXPECT_EQ(plane.Normal, v3);
}

TEST_F(TPlaneTest, Constructor_PointAndNormal_ZeroNormal_Throws) {
    EXPECT_THROW(TPlane(p1, zeroVec), std::runtime_error);
}

TEST_F(TPlaneTest, Constructor_PointAndTwoVectors_ValidNormal_Succeeds) {
    TPlane plane(p1, v1, v2);
    TVector expectedNormal = v1 ^ v2;
    EXPECT_EQ(plane.Point, p1);
    EXPECT_EQ(plane.Normal, expectedNormal);
}

TEST_F(TPlaneTest, Constructor_PointAndTwoVectors_ZeroNormal_Throws) {
    EXPECT_THROW(TPlane(p1, v1, v1), std::runtime_error);
}

TEST_F(TPlaneTest, Constructor_ThreePoints_ValidNormal_Succeeds) {
    TPlane plane(p1, p2, p3);
    TVector expectedNormal = (p2 - p1) ^ (p3 - p1);
    EXPECT_EQ(plane.Point, p1);
    EXPECT_EQ(plane.Normal, expectedNormal);
}

TEST_F(TPlaneTest, Constructor_ThreePoints_Colinear_Throws) { EXPECT_THROW(TPlane(p1, p2, p2), std::runtime_error); }

TEST_F(TPlaneTest, Constructor_PointAndLine_ZeroNormal_Throws) { EXPECT_THROW(TPlane(p1, line1), std::runtime_error); }

TEST_F(TPlaneTest, Constructor_TwoLines_Intersecting_Succeeds) {
    TPlane plane(line1, line2);
    TVector expectedNormal = line1.Vector ^ line2.Vector;
    EXPECT_EQ(plane.Point, p1);
    EXPECT_EQ(plane.Normal, expectedNormal);
}

TEST_F(TPlaneTest, Constructor_TwoLines_Parallel_Throws) {
    EXPECT_THROW(TPlane(line1, lineParallel), std::runtime_error);
}

TEST(TPlane, PointLiesOnPlane) {
    TPoint p0{0, 0, 0};
    TVector normal{0, 0, 1};
    TPlane plane(p0, normal);

    TPoint onPlane{1, 2, 0};

    EXPECT_EQ(plane.distToPoint(onPlane), TSafeDouble{0});
    EXPECT_TRUE(plane.containsPoint(onPlane));
}

TEST(TPlane, PointAbovePlane) {
    TPoint p0{0, 0, 0};
    TVector normal{0, 0, 1};
    TPlane plane(p0, normal);

    TPoint above{0, 0, 5};

    EXPECT_EQ(plane.distToPoint(above), TSafeDouble{5});
    EXPECT_FALSE(plane.containsPoint(above));
}

TEST(TPlane, PointBelowPlane) {
    TPoint p0{0, 0, 0};
    TVector normal{0, 0, 1};
    TPlane plane(p0, normal);

    TPoint below{0, 0, -3};

    EXPECT_EQ(plane.distToPoint(below), TSafeDouble{3});
    EXPECT_FALSE(plane.containsPoint(below));
}

TEST(TPlane, DistanceIsSymmetric) {
    TPoint p0{0, 0, 0};
    TVector normal{0, 0, 1};
    TPlane plane(p0, normal);

    TPoint above{0, 0, 2};
    TPoint below{0, 0, -2};

    EXPECT_EQ(plane.distToPoint(above), TSafeDouble{2});
    EXPECT_EQ(plane.distToPoint(below), TSafeDouble{2});
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
    EXPECT_EQ(plane.distToPoint(offPlane), TSafeDouble{1});
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
    EXPECT_EQ(plane.distToPoint(offPlane), TSafeDouble{5});
}

TEST(TPlane, LineLiesInPlane) {
    TPlane plane(TPoint(0, 0, 0), TVector(0, 0, 1));
    TLine line(TPoint(1, 2, 0), TVector(1, 0, 0));

    EXPECT_TRUE(plane.containsLine(line));
}

TEST(TPlane, LineParallelButNotInPlane) {
    TPlane plane(TPoint(0, 0, 0), TVector(0, 0, 1));
    TLine line(TPoint(1, 2, 1), TVector(1, 0, 0));

    EXPECT_FALSE(plane.containsLine(line));
}

TEST(TPlane, LineIntersectsButNotInPlane) {
    TPlane plane(TPoint(0, 0, 0), TVector(0, 0, 1));
    TLine line(TPoint(0, 0, 1), TVector(0, 0, -1));

    EXPECT_FALSE(plane.containsLine(line));
}

TEST(TPlaneEquality, IdenticalPlanesAreEqual) {
    TPoint p{0, 0, 0};
    TVector n{0, 0, 1};
    TPlane plane1(p, n);
    TPlane plane2(p, n);

    EXPECT_TRUE(plane1 == plane2);
    EXPECT_FALSE(plane1 != plane2);
}

TEST(TPlaneEquality, SamePlaneDifferentPoint) {
    TPoint p1{0, 0, 0};
    TPoint p2{1, 1, 0};
    TVector n{0, 0, 1};
    TPlane plane1(p1, n);
    TPlane plane2(p2, n);

    EXPECT_TRUE(plane1 == plane2);
    EXPECT_FALSE(plane1 != plane2);
}

TEST(TPlaneEquality, SamePlaneOppositeNormal) {
    TPoint p1{0, 0, 0};
    TPoint p2{1, 1, 0};
    TVector n1{0, 0, 1};
    TVector n2{0, 0, -1};
    TPlane plane1(p1, n1);
    TPlane plane2(p2, n2);

    EXPECT_TRUE(plane1 == plane2);
    EXPECT_FALSE(plane1 != plane2);
}

TEST(TPlaneEquality, DifferentPlanes) {
    TPoint p1{0, 0, 0};
    TPoint p2{0, 0, 1};
    TVector n{0, 0, 1};
    TPlane plane1(p1, n);
    TPlane plane2(p2, n);

    EXPECT_FALSE(plane1 == plane2);
    EXPECT_TRUE(plane1 != plane2);
}

TEST(TPlaneEquality, NonParallelNormals) {
    TPoint p{0, 0, 0};
    TVector n1{0, 0, 1};
    TVector n2{0, 1, 0};
    TPlane plane1(p, n1);
    TPlane plane2(p, n2);

    EXPECT_FALSE(plane1 == plane2);
    EXPECT_TRUE(plane1 != plane2);
}

TEST(TPlaneEquality, NearEqualPlanesWithTolerance) {
    TPoint p1{0, 0, 0};
    TPoint p2{(ACCURACY * 10), -(ACCURACY * 10), 0};
    TVector n1{0, 0, 1};
    TVector n2{0, 0, 1.0000001};
    TPlane plane1(p1, n1);
    TPlane plane2(p2, n2);

    EXPECT_TRUE(plane1 == plane2);
    EXPECT_FALSE(plane1 != plane2);
}

TEST(TPlaneEquality, NearDifferentPlanesBeyondTolerance) {
    TPoint p1{0, 0, 0};
    TPoint p2{0, 0, (ACCURACY * 10)};
    TVector n{0, 0, 1};
    TPlane plane1(p1, n);
    TPlane plane2(p2, n);

    EXPECT_FALSE(plane1 == plane2);
    EXPECT_TRUE(plane1 != plane2);
}

TEST(PlaneLineIntersectionTest, IntersectsAtSinglePoint) {
    TPlane plane{TPoint{0, 0, 0}, TVector{0, 0, 1}};
    TLine line{TPoint{1, 1, 1}, TVector{0, 0, -1}};

    auto result = plane.intersection(line);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), (TPoint{1, 1, 0}));
}

TEST(PlaneLineIntersectionTest, ParallelNoIntersection) {
    TPlane plane{TPoint{0, 0, 0}, TVector{0, 0, 1}};
    TLine line{TPoint{0, 0, 1}, TVector{1, 0, 0}};

    auto result = plane.intersection(line);
    EXPECT_FALSE(result.has_value());
}

TEST(PlaneLineIntersectionTest, LineLiesInPlane) {
    TPlane plane{TPoint{0, 0, 0}, TVector{0, 0, 1}};
    TLine line{TPoint{1, 1, 0}, TVector{1, 0, 0}};

    EXPECT_THROW(plane.intersection(line), std::runtime_error);
}

TEST(PlaneLineIntersectionTest, PerpendicularIntersection) {
    TPlane plane{TPoint{0, 0, 0}, TVector{0, 1, 0}};
    TLine line{TPoint{0, 1, 0}, TVector{0, -1, 0}};

    auto result = plane.intersection(line);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), (TPoint{0, 0, 0}));
}

TEST(PlaneLineIntersectionTest, IntersectionAtOrigin) {
    TPlane plane{TPoint{0, 0, 0}, TVector{-1, 1, 1}};
    TLine line{TPoint{1, -1, 0}, TVector{-1, 1, 0}};

    auto result = plane.intersection(line);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), (TPoint{0, 0, 0}));
}

TEST(PlaneLineIntersectionTest, SkewLineIntersects) {
    TPlane plane{TPoint{0, 0, 0}, TVector{0, 1, 0}};
    TLine line{TPoint{1, 1, 1}, TVector{-1, -1, -1}};

    auto result = plane.intersection(line);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), (TPoint{0, 0, 0}));
}

TEST(PlaneLineIntersectionTest, LineParallelAndAbovePlane) {
    TPlane plane{TPoint{0, 0, 0}, TVector{0, 1, 0}};
    TLine line{TPoint{0, 1, 0}, TVector{1, 0, 0}};

    auto result = plane.intersection(line);
    EXPECT_FALSE(result.has_value());
}

TEST(PlaneLineIntersectionTest, LineParallelAndInPlane) {
    TPlane plane{TPoint{0, 0, 0}, TVector{0, 1, 0}};
    TLine line{TPoint{1, 0, 1}, TVector{1, 0, 0}};

    EXPECT_THROW(plane.intersection(line), std::runtime_error);
}

TEST(TPlanePlaneIntersection, IntersectsInLine) {
    TPlane plane1{TPoint{0, 0, 0}, TVector{0, 0, 1}};
    TPlane plane2{TPoint{0, 0, 1}, TVector{0, 1, -1}};

    auto result = plane1.intersection(plane2);
    ASSERT_TRUE(result.has_value());

    TPoint p = result->Point;
    EXPECT_EQ(p.Z, TSafeDouble(0.0));

    TSafeDouble val = (p.X * plane2.Normal.X + p.Y * plane2.Normal.Y + p.Z * plane2.Normal.Z);
    TSafeDouble d =
        plane2.Normal.X * plane2.Point.X + plane2.Normal.Y * plane2.Point.Y + plane2.Normal.Z * plane2.Point.Z;
    EXPECT_EQ(val, d);
}

TEST(TPlanePlaneIntersection, PlanesAreEqual) {
    TPlane plane1{TPoint{0, 0, 0}, TVector{0, 0, 1}};
    TPlane plane2{TPoint{1, 1, 0}, TVector{0, 0, 1}};

    EXPECT_THROW(plane1.intersection(plane2), std::runtime_error);
}

TEST(TPlanePlaneIntersection, PlanesAreParallelNoIntersection) {
    TPlane plane1{TPoint{0, 0, 0}, TVector{0, 0, 1}};
    TPlane plane2{TPoint{0, 0, 1}, TVector{0, 0, 1}};

    auto result = plane1.intersection(plane2);
    EXPECT_FALSE(result.has_value());
}

TEST(TPolygonTest, CreatesPolygonWithUniquePointsSuccessfully) {
    std::vector<TPoint> points = {
        TPoint(0.0, 0.0, 0.0), TPoint(1.0, 0.0, 0.0), TPoint(0.0, 1.0, 0.0),
        TPoint(1.0, 1.0, 0.0), TPoint(0.0, 0.0, 0.0),
    };

    EXPECT_NO_THROW({ TPolygon polygon(points); });
}

TEST(TPolygonTest, ThrowsWhenLessThanThreeUniquePoints) {
    std::vector<TPoint> points = {
        TPoint(0.0, 0.0, 0.0),
        TPoint(0.0, 0.0, 0.0),
        TPoint(0.0, 0.0, 0.0),
    };

    EXPECT_THROW({ TPolygon polygon(points); }, std::runtime_error);
}

TEST(TPolygonTest, ThrowsWhenPointsNotOnSamePlane) {
    std::vector<TPoint> points = {
        TPoint(0.0, 0.0, 0.0),
        TPoint(1.0, 0.0, 0.0),
        TPoint(0.0, 1.0, 0.0),
        TPoint(0.0, 0.0, 1.0),
    };

    EXPECT_THROW({ TPolygon polygon(points); }, std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}