#include "..\src\geometry3D\line\line.h"
#include "..\src\geometry3D\point\point.h"
#include "..\src\geometry3D\safeDouble\safeDouble.h"
#include "..\src\geometry3D\vector\vector.h"

#include <gtest/gtest.h>

using namespace NGeometry3D;

TEST(SafeDoubleTest, Equal) {
    TSafeDouble x = 0.0;
    EXPECT_EQ(x, x);
    TSafeDouble y = 1e-16;
    EXPECT_EQ(y, y);
    EXPECT_EQ(x, y);
}

TEST(SafeDoubleTest, NotEqual) {
    TSafeDouble x = 0.0;
    TSafeDouble y = 1e-14;
    EXPECT_NE(x, y);
    TSafeDouble z = -1e-14;
    EXPECT_NE(y, z);
}

TEST(SafeDoubleTest, GreaterAndLess) {
    TSafeDouble x = 0.0;
    TSafeDouble y = 1e-14;
    EXPECT_GT(y, x);
    TSafeDouble z = -1e-14;
    EXPECT_LT(z, x);
}

TEST(SafeDoubleTest, Sum) {
    TSafeDouble x = 1.0;
    TSafeDouble y = 2.0;
    TSafeDouble z = 3.0;
    EXPECT_EQ(x + y, z);
    TSafeDouble a = 1e-16;
    TSafeDouble b = 1e-17;
    TSafeDouble c = 0.0;
    EXPECT_EQ(a + b, c);
}

TEST(SafeDoubleTest, Diff) {
    TSafeDouble x = 1.0;
    TSafeDouble y = 2.0;
    TSafeDouble z = -1.0;
    EXPECT_EQ(x - y, z);
    TSafeDouble a = 1e-16;
    TSafeDouble b = 1e-17;
    TSafeDouble c = 0.0;
    EXPECT_EQ(a - b, c);
}

TEST(SafeDoubleTest, Abs) {
    TSafeDouble x = 1.0;
    TSafeDouble y = -1.0;
    EXPECT_EQ(x.abs(), y.abs());
}

TEST(SafeDoubleTest, Product) {
    TSafeDouble x = 2.0;
    TSafeDouble y = 4.5;
    TSafeDouble z = 9.0;
    EXPECT_EQ(x * y, z);
    TSafeDouble a = 2.0;
    TSafeDouble b = 1e-16;
    TSafeDouble c = 0.0;
    EXPECT_EQ(a * b, c);
}

TEST(SafeDoubleTest, Division) {
    TSafeDouble x = 2.0;
    TSafeDouble y = 4.5;
    TSafeDouble z = 9.0;
    EXPECT_EQ(z / x, y);
    TSafeDouble a = 1.0;
    TSafeDouble b = 1e-16;
    EXPECT_THROW(a / b, std::runtime_error);
    TSafeDouble u = 1.0;
    TSafeDouble v = 1e-14;
    TSafeDouble w = 1e14;
    EXPECT_EQ(u / v, w);
}

TEST(SafeDoubleTest, Power) {
    TSafeDouble x = 2.0;
    TSafeDouble y = 4.0;
    TSafeDouble z = 16.0;
    EXPECT_EQ(x ^ y, z);
    TSafeDouble u = 4.0;
    TSafeDouble v = 0.5;
    TSafeDouble w = 2.0;
    EXPECT_EQ(u ^ v, w);
}

TEST(PointTest, Equal) {
    TPoint x{1.0, 0.0, 3.0};
    TPoint y{1.0, 1e-16, 3.0};
    EXPECT_EQ(x, y);
    EXPECT_EQ(x, x);
}

TEST(PointTest, Diff) {
    TPoint x{1.0, 2.0, 3.0};
    TPoint y{1.0, 1.0, 3.0};
    TVector z{0.0, 1.0, 0.0};
    EXPECT_EQ(x - y, z);
}

TEST(PointTest, Add) {
    TPoint x{1.0, 2.0, 3.0};
    TPoint y{1.0, 3.0, 3.0};
    TVector z{0.0, 1.0, 0.0};
    EXPECT_EQ(x + z, y);
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