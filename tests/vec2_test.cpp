#include "ml/vec2.hpp"
#include <gtest/gtest.h>
#include <type_traits>

TEST(Vec2, CompoundMultiplyReturnsSelf) {
  ml::Vec2 v{1.0, 2.0};
  // `auto&` binds an alias; plain `auto` would copy and the addresses
  // could never match.
  auto&    r = (v *= 2.0);
  EXPECT_EQ(&r, &v);
}

TEST(Vec2, CompoundMultiplyReturnsReference) {
  ml::Vec2 v{1.0, 2.0};
  // Compile-time check only; decltype does not evaluate the expression.
  static_assert(std::is_same_v<decltype(v *= 2.0), ml::Vec2&>);
}

TEST(Vec2, CompoundMultiplyScales) {
  ml::Vec2 v{1.0, 2.0};
  v *= 2.0;
  // Literal expectations, so the test does not repeat the code's arithmetic.
  EXPECT_DOUBLE_EQ(v.x, 2.0);
  EXPECT_DOUBLE_EQ(v.y, 4.0);
}

TEST(Vec2, CompoundMultiplyCanBeChained) {
  ml::Vec2 v{1.0, 2.0};
  // Chaining only accumulates if the first call returns a reference to v;
  // a returned copy would leave v scaled by 2 only.
  (v *= 2.0) *= 3.0;
  EXPECT_DOUBLE_EQ(v.x, 6.0);
  EXPECT_DOUBLE_EQ(v.y, 12.0);
}

TEST(Vec2, ScalarMultiplyDoesNotMutateThis) {
  ml::Vec2 v{1.0, 2.0};
  // Capture the result: this checks its value and stays valid if the
  // operator is later marked [[nodiscard]].
  auto r = v * 2.0;
  EXPECT_DOUBLE_EQ(r.x, 2.0);
  EXPECT_DOUBLE_EQ(r.y, 4.0);
  // The operand must be unchanged.
  EXPECT_DOUBLE_EQ(v.x, 1.0);
  EXPECT_DOUBLE_EQ(v.y, 2.0);
}

// v * s == s * v is commutativity; associativity would be (a*b)*c == a*(b*c).
TEST(Vec2, ScalarMultiplyIsCommutative) {
  ml::Vec2 v{1.0, 2.0};
  auto     r1 = v * 2.0;
  auto     r2 = 2.0 * v;
  EXPECT_DOUBLE_EQ(r1.x, r2.x);
  EXPECT_DOUBLE_EQ(r1.y, r2.y);
}
