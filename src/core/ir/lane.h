#pragma once
#include <vector>

#include "core/ir/ids.h"
#include "geo/geometry/aabb.h"
#include "geo/geometry/vec2.h"

namespace hdmap::ir {

struct Lane {
  LaneId id;
  std::vector<hdmap::geo::Vec2> centerline;
  std::vector<LaneId> successors;
  std::vector<LaneId> predecessors;
  std::vector<float> cum_s;  // arc-length prefix
};

struct SegmentMeta {
  SegmentId id;
  LaneId lane_id;
  float s0{0.0f};
  float s1{0.0f};
  hdmap::geo::AABB bbox;
};

}  // namespace hdmap::ir