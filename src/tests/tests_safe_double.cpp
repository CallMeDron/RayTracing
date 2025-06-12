#include "../ray_tracing_lib/all.h"

#include <gtest/gtest.h>

using namespace NRayTracingLib;

static constexpr double TINY = ACCURACY / 2.0;
static constexpr double NOT_TINY = ACCURACY * 2.0;

//=== TSafeDouble tests ===

TEST(TSafeDouble, Constructor_Default_SetsZero) {
    TSafeDouble a;
    EXPECT_DOUBLE_EQ(a.Value, 0.0);
}

TEST(TSafeDouble, Constructor_FromInt_SetsCorrectValue) {
    int v = 42;
    TSafeDouble a(v);
    EXPECT_DOUBLE_EQ(a.Value, static_cast<double>(v));
}

TEST(TSafeDouble, Constructor_FromSize_t_SetsCorrectValue) {
    size_t v = 42;
    TSafeDouble a(v);
    EXPECT_DOUBLE_EQ(a.Value, static_cast<double>(v));
}

TEST(TSafeDouble, Constructor_FromDouble_SetsCorrectValue) {
    double v = 3.1415;
    TSafeDouble a(v);
    EXPECT_DOUBLE_EQ(a.Value, v);
}

TEST(TSafeDouble, EqualityOperator_WithValuesWithinTolerance_ReturnsTrue) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 + TINY);
    EXPECT_TRUE(a == b);
}

TEST(TSafeDouble, EqualityOperator_WithValuesOutsideTolerance_ReturnsFalse) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 + NOT_TINY);
    EXPECT_FALSE(a == b);
}

TEST(TSafeDouble, InequalityOperator_WithValuesOutsideTolerance_ReturnsTrue) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 + NOT_TINY);
    EXPECT_TRUE(a != b);
}

TEST(TSafeDouble, InequalityOperator_WithValuesWithinTolerance_ReturnsFalse) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 + TINY);
    EXPECT_FALSE(a != b);
}

TEST(TSafeDouble, GreaterThanOperator_CorrectComparison) {
    TSafeDouble a(2.0);
    TSafeDouble b(1.0);
    EXPECT_TRUE(a > b);
    EXPECT_FALSE(b > a);

    TSafeDouble c(2.0 + TINY);
    EXPECT_FALSE(a > c);
}

TEST(TSafeDouble, LessThanOperator_CorrectComparison) {
    TSafeDouble a(1.0);
    TSafeDouble b(2.0);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);

    TSafeDouble c(1.0 - TINY);
    EXPECT_FALSE(a < c);
}

TEST(TSafeDouble, GreaterEqualOperator_Behavior) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 + TINY);
    TSafeDouble c(0.9);
    EXPECT_TRUE(a >= b);
    EXPECT_TRUE(a >= c);
    EXPECT_FALSE(c >= a);
}

TEST(TSafeDouble, LessEqualOperator_Behavior) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 - TINY);
    TSafeDouble c(1.1);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a <= c);
    EXPECT_FALSE(c <= a);
}

TEST(TSafeDouble, UnaryMinus_NegatesValue) {
    TSafeDouble a(5.0);
    TSafeDouble b = -a;
    EXPECT_DOUBLE_EQ(b.Value, -5.0);
    TSafeDouble c = -b;
    EXPECT_DOUBLE_EQ(c.Value, 5.0);
}

TEST(TSafeDouble, Abs_ReturnsAbsoluteValue_ForNegative) {
    TSafeDouble a(-3.5);
    TSafeDouble result = a.abs();
    EXPECT_DOUBLE_EQ(result.Value, 3.5);
}

TEST(TSafeDouble, Abs_ReturnsZero_ForZero) {
    TSafeDouble a(0.0);
    TSafeDouble result = a.abs();
    EXPECT_DOUBLE_EQ(result.Value, 0.0);
}

TEST(TSafeDouble, Abs_ReturnsSameValue_ForPositive) {
    TSafeDouble a(4.2);
    TSafeDouble result = a.abs();
    EXPECT_DOUBLE_EQ(result.Value, 4.2);
}

TEST(TSafeDouble, Addition_AddsValues) {
    TSafeDouble a(1.5);
    TSafeDouble b(2.5);
    TSafeDouble c = a + b;
    EXPECT_DOUBLE_EQ(c.Value, 4.0);
}

TEST(TSafeDouble, Subtraction_SubtractsValues) {
    TSafeDouble a(5.0);
    TSafeDouble b(3.0);
    TSafeDouble c = a - b;
    EXPECT_DOUBLE_EQ(c.Value, 2.0);
}

TEST(TSafeDouble, Multiplication_MultipliesValues) {
    TSafeDouble a(2.0);
    TSafeDouble b(4.0);
    TSafeDouble c = a * b;
    EXPECT_DOUBLE_EQ(c.Value, 8.0);
}

TEST(TSafeDouble, Division_DividesValues) {
    TSafeDouble a(10.0);
    TSafeDouble b(2.0);
    TSafeDouble c = a / b;
    EXPECT_DOUBLE_EQ(c.Value, 5.0);
}

TEST(TSafeDouble, Division_ByZero_Throws) {
    TSafeDouble a(1.0);
    TSafeDouble zero(0.0);
    EXPECT_THROW(a / zero, std::runtime_error);
}

TEST(TSafeDouble, PlusEquals_AddsAndAssigns) {
    TSafeDouble a(1.0);
    TSafeDouble b(2.0);
    a += b;
    EXPECT_DOUBLE_EQ(a.Value, 3.0);
}

TEST(TSafeDouble, MinusEquals_SubtractsAndAssigns) {
    TSafeDouble a(5.0);
    TSafeDouble b(3.0);
    a -= b;
    EXPECT_DOUBLE_EQ(a.Value, 2.0);
}

TEST(TSafeDouble, MultiplyEquals_MultipliesAndAssigns) {
    TSafeDouble a(3.0);
    TSafeDouble b(4.0);
    a *= b;
    EXPECT_DOUBLE_EQ(a.Value, 12.0);
}

TEST(TSafeDouble, DivideEquals_DividesAndAssigns) {
    TSafeDouble a(8.0);
    TSafeDouble b(2.0);
    a /= b;
    EXPECT_DOUBLE_EQ(a.Value, 4.0);
}

TEST(TSafeDouble, Pow_RaisesToPower_CorrectResult) {
    TSafeDouble a(2.0);
    TSafeDouble exponent(3.0);
    TSafeDouble result = a.pow(exponent);
    EXPECT_DOUBLE_EQ(result.Value, 8.0);
}