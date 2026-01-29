#pragma once

#include "geo/geometry/aabb.h"
#include "geo/geometry/vec2.h"

namespace hdmap::geo {

struct Segment {
  Vec2 start;
  Vec2 end;

  Segment() = default;
  Segment(const Vec2& s, const Vec2& e) : start(s), end(e) {}
};

// 辅助函数
float SegmentLengthSquares(const Segment& s);
float SegmentLength(const Segment& s);

// 将点 p 投影到线段 s，返回最近点；可选输出参数 t ∈ [0,1] 表示在段上的比例
Vec2 ProjectPointToSegment(const Vec2& p, const Segment& s, float* t_out = nullptr);

// 点到线段的最短距离
float DistancePointToSegment(const Vec2& p, const Segment& s);

// 生成线段的AABB（便于索引）
AABB SegmentAABB(const Segment& s);

}  // namespace hdmap::geo