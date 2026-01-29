#include "geo/geometry/segment.h"

#include <algorithm>
#include <cmath>

namespace hdmap::geo {

float SegmentLengthSquares(const Segment& s) {
  return (s.end - s.start).SquaredNorm();
}

float SegmentLength(const Segment& s) {
  return std::sqrt(SegmentLengthSquares(s));
}

Vec2 ProjectPointToSegment(const Vec2& p, const Segment& s, float* t_out) {
  Vec2 ab = s.end - s.start;
  float ab_len2 = ab.SquaredNorm();
  if (ab_len2 < kEps) {  // 退化段：a 与 b 重合
    if (t_out) *t_out = 0.0f;
    return s.start;
  }
  float t = (p - s.start).Dot(ab) / ab_len2;  // 在线段延长线的投影比例
  t = std::clamp(t, 0.0f, 1.0f);              // 限制到 [0,1]
  if (t_out) *t_out = t;
  return s.start + ab * t;
}

float DistancePointToSegment(const Vec2& p, const Segment& s) {
  Vec2 nearest = ProjectPointToSegment(p, s, nullptr);
  return (p - nearest).Norm();
}

AABB SegmentAABB(const Segment& s) {
  AABB box;
  box.Expand(s.start);
  box.Expand(s.end);
  return box;
}

}  // namespace hdmap::geo