#pragma once
#include <memory>
#include <unordered_map>
#include <vector>

#include "core/ir/catalog.h"
#include "core/ir/lane.h"
#include "core/ir/status.h"
#include "core/ir/tile.h"
#include "geo/geometry/aabb.h"
#include "geo/geometry/vec2.h"

namespace hdmap::ir {

// 根据 polyline 构造 Lane（填充 id/centerline/cum_s）
Lane BuildLane(LaneId id, const std::vector<hdmap::geo::Vec2>& polyline);

// 为给定 Lane 生成分段元数据（SegmentMeta）
// start_id：段 ID 起始值，便于多个 lane 连续编号
std::vector<SegmentMeta> BuildSegmentsForLane(const Lane& lane, SegmentId start_id = 0);

// 构造 TileIR：收集传入的 lanes，并生成其所有 segments
TileIR BuildTile(const TileId& tile_id, const std::vector<Lane>& lanes, SegmentId start_seg_id = 0);

// 将 TileIR 封装为不可变快照（共享所有权，避免拷贝）
std::shared_ptr<const TileSnapshot> MakeTileSnapshot(TileIR tile);

// 将多个 TileSnapshot 组装成 TileSetSnapshot（同一 map_id + version）
std::shared_ptr<const TileSetSnapshot> MakeTileSetSnapshot(
    const MapId& map_id, const VersionId& version,
    std::vector<std::shared_ptr<const TileSnapshot>> tiles);

// 辅助：把 tile_id -> lanes 的映射批量构建并封装为 TileSetSnapshot
std::shared_ptr<const TileSetSnapshot> BuildTileSetSnapshot(
    const MapId& map_id, const VersionId& version,
    const std::unordered_map<TileId, std::vector<Lane>>& lanes_by_tile, SegmentId start_seg_id = 0);

// 可选：直接发布到 MapCatalog
Status PublishTileSet(MapCatalog* catalog, const MapId& map_id, const VersionId& version,
                      const std::unordered_map<TileId, std::vector<Lane>>& lanes_by_tile,
                      SegmentId start_seg_id = 0);

}  // namespace hdmap::ir
