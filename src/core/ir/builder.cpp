#include "core/ir/builder.h"

#include <cmath>

namespace hdmap::ir {

Lane BuildLane(LaneId id, const std::vector<hdmap::geo::Vec2>& polyline) {
  Lane lane;
  lane.id = id;
  lane.centerline = polyline;
  lane.cum_s.reserve(polyline.size());
  float acc{0.0f};
  for (size_t i = 0; i < polyline.size(); i++) {
    if (i == 0) {
      lane.cum_s.push_back(0.0f);
    } else {
      const auto& p0 = polyline[i - 1];
      const auto& p1 = polyline[i];
      float dx = p1.x - p0.x;
      float dy = p1.y - p0.y;
      acc += std::sqrt(dx * dx + dy * dy);
      lane.cum_s.push_back(acc);
    }
  }
  return lane;
}

std::vector<SegmentMeta> BuildSegmentsForLane(const Lane& lane, SegmentId start_id) {
  std::vector<SegmentMeta> segs;
  if (lane.centerline.size() < 2) {
    return segs;  // 不足以形成线段
  }
  segs.reserve(lane.centerline.size() - 1);
  SegmentId sid = start_id;

  for (size_t i = 0; i + 1 < lane.centerline.size(); ++i, ++sid) {
    SegmentMeta sm;
    sm.id = sid;
    sm.lane_id = lane.id;
    sm.s0 = lane.cum_s[i];
    sm.s1 = lane.cum_s[i + 1];
    sm.bbox.min = lane.centerline[i];
    sm.bbox.max = lane.centerline[i];
    sm.bbox.Expand(lane.centerline[i + 1]);
    segs.push_back(sm);
  }
  return segs;
}

TileIR BuildTile(const TileId& tile_id, const std::vector<Lane>& lanes, SegmentId start_seg_id) {
  TileIR tile;
  tile.id = tile_id;
  tile.lanes = lanes;

  SegmentId sid = start_seg_id;
  for (const auto& lane : lanes) {
    auto segs = BuildSegmentsForLane(lane, sid);
    sid += static_cast<SegmentId>(segs.size());
    tile.segments.insert(tile.segments.end(), segs.begin(), segs.end());
  }
  return tile;
}

std::shared_ptr<const TileSnapshot> MakeTileSnapshot(TileIR tile) {
  auto snap = std::make_shared<TileSnapshot>();
  snap->id = tile.id;
  snap->ir = std::make_shared<TileIR>(std::move(tile));  // move 避免拷贝
  return snap;
}

std::shared_ptr<const TileSetSnapshot> MakeTileSetSnapshot(
    const MapId& map_id, const VersionId& version,
    std::vector<std::shared_ptr<const TileSnapshot>> tiles) {
  auto set = std::make_shared<TileSetSnapshot>();
  set->map_id = map_id;
  set->version = version;
  set->tiles = std::move(tiles);
  return set;
}

std::shared_ptr<const TileSetSnapshot> BuildTileSetSnapshot(
    const MapId& map_id, const VersionId& version,
    const std::unordered_map<TileId, std::vector<Lane>>& lanes_by_tile, SegmentId start_seg_id) {
  std::vector<std::shared_ptr<const TileSnapshot>> tiles;
  tiles.reserve(lanes_by_tile.size());

  SegmentId cur = start_seg_id;
  for (const auto& kv : lanes_by_tile) {
    const TileId& tid = kv.first;
    const auto& lanes = kv.second;
    TileIR tile = BuildTile(tid, lanes, cur);
    cur += static_cast<SegmentId>(tile.segments.size());
    tiles.push_back(MakeTileSnapshot(std::move(tile)));
  }
  return MakeTileSetSnapshot(map_id, version, std::move(tiles));
}

Status PublishTileSet(MapCatalog* catalog, const MapId& map_id, const VersionId& version,
                      const std::unordered_map<TileId, std::vector<Lane>>& lanes_by_tile,
                      SegmentId start_seg_id) {
  auto snap = BuildTileSetSnapshot(map_id, version, lanes_by_tile, start_seg_id);
  return catalog->Put(map_id, version, std::move(snap));
}
}  // namespace hdmap::ir