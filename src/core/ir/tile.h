#pragma once
#include <memory>
#include <vector>

#include "core/ir/ids.h"
#include "core/ir/lane.h"

namespace hdmap::ir {

struct TileIR {
  TileId id;
  std::vector<Lane> lanes;
  std::vector<SegmentMeta> segments;
};

struct TileSnapshot {
  TileId id;
  std::shared_ptr<const TileIR> ir;
};

struct TileSetSnapshot {
  MapId map_id;
  VersionId version;
  std::vector<std::shared_ptr<const TileSnapshot>> tiles;
};

}  // namespace hdmap::ir
