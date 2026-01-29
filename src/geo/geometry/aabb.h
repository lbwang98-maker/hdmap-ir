#pragma once

#include <limits>

#include "geo/geometry/vec2.h"

namespace hdmap::geo {

struct AABB {
  Vec2 min;
  Vec2 max;

  AABB()
      : min(Vec2(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity())),
        max(Vec2(-std::numeric_limits<float>::infinity(),
                 -std::numeric_limits<float>::infinity())) {}
  AABB(const Vec2& min_val, const Vec2& max_val) : min(min_val), max(max_val) {}

  // 扩展包围盒以包含点或另一个盒
  void Expand(const Vec2& p);
  void Expand(const AABB& box);

  float Width() const {
    return max.x - min.x;
  };
  float Height() const {
    return max.y - min.y;
  };
  Vec2 Center() const {
    return Vec2((min.x + max.x) * 0.5f, (min.y + max.y) * 0.5f);
  }

  bool IsValid() const {
    return min.x <= max.x && min.y <= max.y;
  }

  bool Contains(const Vec2& p) const;

  bool Intersect(const AABB& box) const;

  // 点到盒子的欧式距离（0表示在盒内或边上）
  float Distance(const Vec2& p) const;
};
}  // namespace hdmap::geo
