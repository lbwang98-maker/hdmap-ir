#include "geo/geometry/segment.h"
#include <gtest/gtest.h>

using hdmap::geo::DistancePointToSegment;
using hdmap::geo::ProjectPointToSegment;
using hdmap::geo::Segment;
using hdmap::geo::SegmentAABB;
using hdmap::geo::Vec2;

TEST(SegmentTest, ProjectionInside) {
  Segment s({0.0f, 0.0f}, {2.0f, 0.0f});
  float t = -1.0f;
  auto p = ProjectPointToSegment({1.0f, 1.0f}, s, &t);
  EXPECT_NEAR(t, 0.5f, 1e-6);
  EXPECT_NEAR(p.x, 1.0f, 1e-6);
  EXPECT_NEAR(p.y, 0.0f, 1e-6);
}

TEST(SegmentTest, ProjectionOutside) {
  Segment s({0.0f, 0.0f}, {2.0f, 0.0f});
  float t = -1.0f;
  auto p = ProjectPointToSegment({-1.0f, 2.0f}, s, &t);
  EXPECT_NEAR(t, 0.0f, 1e-6); // 落在端点 a
  EXPECT_NEAR(p.x, 0.0f, 1e-6);
  EXPECT_NEAR(p.y, 0.0f, 1e-6);

  p = ProjectPointToSegment({3.0f, -1.0f}, s, &t);
  EXPECT_NEAR(t, 1.0f, 1e-6); // 落在端点 b
  EXPECT_NEAR(p.x, 2.0f, 1e-6);
  EXPECT_NEAR(p.y, 0.0f, 1e-6);
}

TEST(SegmentTest, DegenerateSegment) {
  Segment s({1.0f, 1.0f}, {1.0f, 1.0f}); // 退化
  float dist = DistancePointToSegment({2.0f, 1.0f}, s);
  EXPECT_NEAR(dist, 1.0f, 1e-6);
}

TEST(SegmentTest, AabbBasic) {
  Segment s({-1.0f, 2.0f}, {3.0f, -2.0f});
  auto box = SegmentAABB(s);
  EXPECT_TRUE(box.Contains({-1.0f, 2.0f}));
  EXPECT_TRUE(box.Contains({3.0f, -2.0f}));
  EXPECT_FALSE(box.Contains({3.1f, -2.0f}));
}
