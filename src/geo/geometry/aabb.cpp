#include "geo/geometry/aabb.h"

#include <algorithm>
#include <cmath>

namespace hdmap::geo {

void AABB::Expand(const Vec2& p) {
  min.x = std::min(min.x, p.x);
  min.y = std::min(min.y, p.y);
  max.x = std::max(max.x, p.x);
  max.y = std::max(max.y, p.y);
}

void AABB::Expand(const AABB& box) {
  Expand(box.min);
  Expand(box.max);
}

bool AABB::Contains(const Vec2& p) const {
  return p.x >= min.x && p.x <= max.x && p.y >= min.y && p.y <= max.y;
}

bool AABB::Intersect(const AABB& box) const {
  if (!IsValid() || !box.IsValid()) return false;
  bool sep_x = max.x < box.min.x || min.x > box.max.x;
  bool sep_y = max.y < box.min.y || min.y > box.max.y;
  return !(sep_x || sep_y);
}

float AABB::Distance(const Vec2& p) const {
  // 投影到盒内并计算向量长度
  float dx = 0.0f;
  if (p.x < min.x)
    dx = min.x - p.x;
  else if (p.x > max.x)
    dx = p.x - max.x;

  float dy = 0.0f;
  if (p.y < min.y)
    dy = min.y - p.y;
  else if (p.y > max.y)
    dy = p.y - max.y;

  return std::sqrt(dx * dx + dy * dy);
}

}  // namespace hdmap::geo