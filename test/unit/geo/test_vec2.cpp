#include <gtest/gtest.h>

#include "geo/geometry/vec2.h"
using hdmap::geo::Cross2D;
using hdmap::geo::NearEqual;
using hdmap::geo::Vec2;

TEST(Vec2Test, BasicOps) {
  Vec2 a(1.0f, 2.0f);
  Vec2 b(-3.0f, 0.5f);
  auto c = a + b;
  EXPECT_NEAR(c.x, -2.0f, 1e-6);
  EXPECT_NEAR(c.y, 2.5f, 1e-6);

  c = a - b;
  EXPECT_NEAR(c.x, 4.0f, 1e-6);
  EXPECT_NEAR(c.y, 1.5f, 1e-6);

  c = a * 2.0f;
  EXPECT_NEAR(c.x, 2.0f, 1e-6);
  EXPECT_NEAR(c.y, 4.0f, 1e-6);

  c = a / 2.0f;
  EXPECT_NEAR(c.x, 0.5f, 1e-6);
  EXPECT_NEAR(c.y, 1.0f, 1e-6);
}

TEST(Vec2Test, DotCrossNorm) {
  Vec2 a(3.0f, 4.0f);
  Vec2 b(-4.0f, 3.0f);
  EXPECT_NEAR(a.Dot(b), 0.0f, 1e-6);
  EXPECT_NEAR(a.Norm(), 5.0f, 1e-6);
  EXPECT_NEAR(Cross2D(a, b), 25.0f, 1e-6);
}

TEST(Vec2Test, NormalizeAndEqual) {
  Vec2 a(0.0f, 0.0f);
  auto n0 = a.Normalized();
  EXPECT_TRUE(NearEqual(n0, Vec2::Zero()));

  Vec2 b(2.0f, 0.0f);
  auto n1 = b.Normalized();
  EXPECT_NEAR(n1.x, 1.0f, 1e-6);
  EXPECT_NEAR(n1.y, 0.0f, 1e-6);

  Vec2 c(1.0f + 1e-7f, 2.0f - 1e-7f);
  Vec2 d(1.0f, 2.0f);
  EXPECT_TRUE(c == d);  // 近似比较
}
