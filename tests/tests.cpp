#include "..\src\ray_tracing_lib\line\line.h"
#include "..\src\ray_tracing_lib\point\point.h"
#include "..\src\ray_tracing_lib\safe_double\safe_double.h"
#include "..\src\ray_tracing_lib\vector\vector.h"

#include <gtest/gtest.h>

using namespace NRayTracingLib;

TEST(TSafeDoubleTest, ConstructorAndValue) {
    TSafeDouble a(3.14);
    EXPECT_DOUBLE_EQ(a.Value, 3.14);
}

TEST(TSafeDoubleTest, EqualityOperator) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 + 1e-16);
    EXPECT_TRUE(a == b);
    TSafeDouble c(1.0 + 1e-10);
    EXPECT_FALSE(a == c);
}

TEST(TSafeDoubleTest, InequalityOperator) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 + 1e-10);
    EXPECT_TRUE(a != b);
    TSafeDouble c(1.0 + 1e-16);
    EXPECT_FALSE(a != c);
}

TEST(TSafeDoubleTest, GreaterThanOperator) {
    TSafeDouble a(2.0);
    TSafeDouble b(1.0);
    EXPECT_TRUE(a > b);
    EXPECT_FALSE(b > a);
    TSafeDouble c(2.0 + 1e-16);
    EXPECT_FALSE(a > c);
}

TEST(TSafeDoubleTest, LessThanOperator) {
    TSafeDouble a(1.0);
    TSafeDouble b(2.0);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
    TSafeDouble c(1.0 - 1e-16);
    EXPECT_FALSE(a < c);
}

TEST(TSafeDoubleTest, GreaterEqualOperator) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 + 1e-16);
    TSafeDouble c(0.9);
    EXPECT_TRUE(a >= b);
    EXPECT_TRUE(a >= c);
    EXPECT_FALSE(c >= a);
}

TEST(TSafeDoubleTest, LessEqualOperator) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 - 1e-16);
    TSafeDouble c(1.1);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a <= c);
    EXPECT_FALSE(c <= a);
}

TEST(TSafeDoubleTest, UnaryMinusOperator) {
    TSafeDouble a(5.0);
    TSafeDouble b = -a;
    EXPECT_DOUBLE_EQ(b.Value, -5.0);
    TSafeDouble c = -b;
    EXPECT_DOUBLE_EQ(c.Value, 5.0);
}

TEST(TSafeDoubleTest, AbsMethod) {
    TSafeDouble a(-3.5);
    TSafeDouble b(3.5);
    TSafeDouble c(0.0);
    EXPECT_DOUBLE_EQ(a.abs().Value, 3.5);
    EXPECT_DOUBLE_EQ(b.abs().Value, 3.5);
    EXPECT_DOUBLE_EQ(c.abs().Value, 0.0);
}

TEST(TSafeDoubleTest, AdditionOperator) {
    TSafeDouble a(1.5);
    TSafeDouble b(2.5);
    TSafeDouble c = a + b;
    EXPECT_DOUBLE_EQ(c.Value, 4.0);
}

TEST(TSafeDoubleTest, SubtractionOperator) {
    TSafeDouble a(5.0);
    TSafeDouble b(3.0);
    TSafeDouble c = a - b;
    EXPECT_DOUBLE_EQ(c.Value, 2.0);
}

TEST(TSafeDoubleTest, MultiplicationOperator) {
    TSafeDouble a(2.0);
    TSafeDouble b(4.0);
    TSafeDouble c = a * b;
    EXPECT_DOUBLE_EQ(c.Value, 8.0);
}

TEST(TSafeDoubleTest, DivisionOperator) {
    TSafeDouble a(10.0);
    TSafeDouble b(2.0);
    TSafeDouble c = a / b;
    EXPECT_DOUBLE_EQ(c.Value, 5.0);
}

TEST(TSafeDoubleTest, DivisionByZeroThrows) {
    TSafeDouble a(1.0);
    TSafeDouble zero(0.0);
    EXPECT_THROW(a / zero, std::runtime_error);
}

TEST(TSafeDoubleTest, CompoundAdditionOperator) {
    TSafeDouble a(1.0);
    TSafeDouble b(2.0);
    a += b;
    EXPECT_DOUBLE_EQ(a.Value, 3.0);
}

TEST(TSafeDoubleTest, CompoundSubtractionOperator) {
    TSafeDouble a(5.0);
    TSafeDouble b(3.0);
    a -= b;
    EXPECT_DOUBLE_EQ(a.Value, 2.0);
}

TEST(TSafeDoubleTest, CompoundMultiplicationOperator) {
    TSafeDouble a(3.0);
    TSafeDouble b(4.0);
    a *= b;
    EXPECT_DOUBLE_EQ(a.Value, 12.0);
}

TEST(TSafeDoubleTest, CompoundDivisionOperator) {
    TSafeDouble a(8.0);
    TSafeDouble b(2.0);
    a /= b;
    EXPECT_DOUBLE_EQ(a.Value, 4.0);
}

TEST(TSafeDoubleTest, PowMethod) {
    TSafeDouble a(2.0);
    TSafeDouble b(3.0);
    TSafeDouble c = a.pow(b);
    EXPECT_DOUBLE_EQ(c.Value, 8.0);
}

class TPointTest : public ::testing::Test {
  protected:
    TPoint point1{1.0, 2.0, 3.0};
    TPoint point2{1.0, 2.0, 3.0};
    TPoint point3{4.0, 5.0, 6.0};
    TVector vector{1.0, 1.0, 1.0};
};

TEST_F(TPointTest, Constructor) {
    EXPECT_EQ(point1.X, 1.0);
    EXPECT_EQ(point1.Y, 2.0);
    EXPECT_EQ(point1.Z, 3.0);
}

TEST_F(TPointTest, EqualityOperator) {
    EXPECT_TRUE(point1 == point2);
    EXPECT_FALSE(point1 == point3);
}

TEST_F(TPointTest, InequalityOperator) {
    EXPECT_TRUE(point1 != point3);
    EXPECT_FALSE(point1 != point2);
}

TEST_F(TPointTest, SubtractionOperator) {
    TVector result = point1 - point3;
    EXPECT_EQ(result.X, -3.0);
    EXPECT_EQ(result.Y, -3.0);
    EXPECT_EQ(result.Z, -3.0);
}

TEST_F(TPointTest, AdditionOperator) {
    TPoint result = point1 + vector;
    EXPECT_EQ(result.X, 2.0);
    EXPECT_EQ(result.Y, 3.0);
    EXPECT_EQ(result.Z, 4.0);
}

TEST(VectorTest, Create) {
    TPoint x{1.0, 2.0, 3.0};
    TVector y{x};
    TVector z{1.0, 2.0, 3.0};
    EXPECT_EQ(y, z);
    TPoint a{1.0, 2.0, 3.0};
    TPoint b{2.0, 3.0, 4.0};
    TVector c{1.0, 1.0, 1.0};
    EXPECT_EQ(TVector(a, b), c);
}

TEST(VectorTest, SumAndDiff) {
    TVector x{1.0, 2.0, 3.0};
    TVector y{4.0, 3.0, 2.0};
    TVector z{5.0, 5.0, 5.0};
    TVector w{-3.0, -1.0, 1.0};
    EXPECT_EQ(x + y, z);
    EXPECT_EQ(x - y, w);
}

TEST(VectorTest, ProdAndDiv) {
    TVector x{1.0, 2.0, 3.0};
    TVector y{3.0, 6.0, 9.0};
    EXPECT_EQ(x * 3.0, y);
    EXPECT_EQ(y / 3.0, x);
    EXPECT_THROW(y / 1e-16, std::runtime_error);
}

TEST(VectorTest, ScalarProd) {
    TVector x{1.0, 2.0, 3.0};
    TVector y{3.0, 6.0, 9.0};
    EXPECT_EQ(x * y, 42.0);
}

TEST(VectorTest, VectorProd) {
    TVector x{1.0, 2.0, 3.0};
    TVector y{3.0, 2.0, 1.0};
    TVector z{-4.0, 8.0, -4.0};
    EXPECT_EQ(x ^ y, z);
}

TEST(VectorTest, Length) {
    TVector x{0.0, 3.0, 4.0};
    EXPECT_EQ(x.length(), 5.0);
}

TEST(VectorTest, Normalization) {
    TVector x{0.0, 3.0, 4.0};
    x.normalize();
    TVector y{0.0, 0.6, 0.8};
    EXPECT_EQ(x, y);
    TVector z{0.0, 3.0, 4.0};
    EXPECT_EQ(z.getNormalized(), y);
    TVector w{0.0, 0.0, 0.0};
    EXPECT_THROW(w.getNormalized(), std::runtime_error);
}

TEST(VectorTest, Cos) {
    TVector x{1.0, 2.0, 3.0};
    TVector y{3.0, 2.0, 1.0};
    EXPECT_EQ(x.cos(y), 5.0 / 7.0);
    EXPECT_EQ(y.cos(x), 5.0 / 7.0);
}

TEST(VectorTest, Parallel) {
    TVector x{1.0, 2.0, 3.0};
    TVector y{5.0, 10.0, 15.0};
    EXPECT_TRUE(x.isParallel(x));
    EXPECT_TRUE(x.isParallel(-x));
    EXPECT_TRUE(x.isParallel(y));
    EXPECT_TRUE(y.isParallel(x));
    TVector z{0.0, 0.0, 0.0};
    EXPECT_THROW(z.isParallel(z), std::runtime_error);
    TVector w{6.0, 10.0, 15.0};
    EXPECT_FALSE(x.isParallel(w));
    EXPECT_FALSE(w.isParallel(x));
    TVector v{5.0 + 1e-16, 10.0 + 1e-16, 15.0 + 1e-16};
    EXPECT_TRUE(v.isParallel(y));
}

TEST(VectorTest, Perpendicular) {
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
    TVector v{0.0 + 1e-16, 1.0 + 1e-16, 0.0 + 1e-16};
    EXPECT_TRUE(v.isPerpendicular(x));
}

TEST(VectorTest, Projection) {
    TVector x{1.0, 0.0, 0.0};
    TVector y{0.0, 1.0, 0.0};
    EXPECT_EQ(x.projectTo(x), x);
    EXPECT_TRUE(x.projectTo(y).isZero());
    TVector v{1.0, 2.0, 3.0};
    TVector w{-3.0, 2.0, 7.0};
    EXPECT_EQ(v.projectTo(w), TVector(-33.0 / 31.0, 22.0 / 31.0, 77.0 / 31.0));
}

TEST(LineTest, Cos) {
    TPoint o{0.0, 0.0, 0.0};
    TVector x{1.0, 2.0, 3.0};
    TVector y{3.0, 2.0, 1.0};
    TLine X{o, x};
    TLine Y{o, y};
    EXPECT_EQ(X.cos(Y), 5.0 / 7.0);
    EXPECT_EQ(Y.cos(X), 5.0 / 7.0);
}

TEST(LineTest, Parallel) {
    TPoint o{0.0, 0.0, 0.0};
    TVector x{1.0, 2.0, 3.0};
    TVector y{5.0, 10.0, 15.0};
    TLine X{o, x};
    TLine Y{o, y};
    EXPECT_TRUE(X.isParallel(X));
    EXPECT_TRUE(X.isParallel(Y));
    EXPECT_TRUE(Y.isParallel(X));
    TVector z{0.0, 0.0, 0.0};
    EXPECT_THROW(TLine(o, z), std::runtime_error);
    TVector w{6.0, 10.0, 15.0};
    TLine W{o, w};
    EXPECT_FALSE(X.isParallel(W));
    EXPECT_FALSE(W.isParallel(X));
    TVector v{5.0 + 1e-16, 10.0 + 1e-16, 15.0 + 1e-16};
    TLine V{o, v};
    EXPECT_TRUE(V.isParallel(Y));
}

TEST(LineTest, Perpendicular) {
    TPoint o{0.0, 0.0, 0.0};
    TVector x{1.0, 0.0, 0.0};
    TVector y{0.0, 1.0, 0.0};
    TVector z{0.0, 0.0, 1.0};
    TLine X{o, x};
    TLine Y{o, y};
    TLine Z{o, z};
    EXPECT_TRUE(X.isPerpendicular(Y));
    EXPECT_TRUE(X.isPerpendicular(Z));
    EXPECT_TRUE(Y.isPerpendicular(X));
    EXPECT_TRUE(Y.isPerpendicular(Z));
    EXPECT_TRUE(Z.isPerpendicular(X));
    EXPECT_TRUE(Z.isPerpendicular(Y));
    TVector w{6.0, 10.0, 15.0};
    TLine W{o, w};
    EXPECT_FALSE(X.isPerpendicular(W));
    EXPECT_FALSE(W.isPerpendicular(X));
    TVector v{0.0 + 1e-16, 1.0 + 1e-16, 0.0 + 1e-16};
    TLine V{o, v};
    EXPECT_TRUE(V.isPerpendicular(X));
}

TEST(LineTest, DistToPoint) {
    TPoint o{0.0, 0.0, 0.0};
    TVector w{1.0, 0.0, 0.0};
    TLine W{o, w};
    TPoint x{1.0, 0.0, 0.0};
    EXPECT_EQ(W.distToPoint(x), 0.0);
    TPoint y{0.0, 0.0, 0.0};
    EXPECT_EQ(W.distToPoint(y), 0.0);
    TPoint z{10000.0, 0.0, 0.0};
    EXPECT_EQ(W.distToPoint(z), 0.0);
    TPoint u{10000.0, 5.0, 0.0};
    EXPECT_EQ(W.distToPoint(u), 5.0);
    TPoint v{10000.0, 3.0, 4.0};
    EXPECT_EQ(W.distToPoint(v), 5.0);
}

TEST(LineTest, ContainsPoint) {
    TPoint o{0.0, 0.0, 0.0};
    TVector x{1.0, 0.0, 0.0};
    TLine X{o, x};
    EXPECT_TRUE(X.containsPoint(o));
    TPoint w{1.0, 0.0, 0.0};
    EXPECT_TRUE(X.containsPoint(w));
    TPoint y{1.0 + 1e-14, 0.0 - 1e-14, 0.0 - 1e-14};
    EXPECT_FALSE(X.containsPoint(y));
    TPoint z{1.0 + 1e-16, 0.0 - 1e-16, 0.0 - 1e-16};
    EXPECT_TRUE(X.containsPoint(z));
}

TEST(LineTest, EqualAndNotEqual) {
    TPoint o{0.0, 0.0, 0.0};
    TVector x{1.0, 0.0, 0.0};
    TVector y{1.0 + 1e-7, 0.0 - 1e-7, 0.0 - 1e-7};
    TVector z{1.0 + 1e-8, 0.0 - 1e-8, 0.0 - 1e-8};
    TLine X{o, x};
    TLine Y{o, y};
    TLine Z{o, z};
    EXPECT_EQ(X, Z);
    EXPECT_EQ(Z, X);
    EXPECT_NE(X, Y);
    EXPECT_NE(Y, X);
    EXPECT_NE(Y, Z);
    EXPECT_NE(Z, Y);
}

TEST(LineTest, Intersection) {
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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}