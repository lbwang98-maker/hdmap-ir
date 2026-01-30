#include <gtest/gtest.h>

#include <cmath>

#include "core/ir/builder.h"

using namespace hdmap;
using namespace hdmap::ir;
using hdmap::geo::Vec2;

TEST(IrBuilder, BuildLaneCumS) {
  std::vector<Vec2> pts{{0, 0}, {3, 0}, {3, 4}};
  auto lane = BuildLane(1, pts);
  ASSERT_EQ(lane.cum_s.size(), 3u);
  EXPECT_NEAR(lane.cum_s[0], 0.0, 1e-6);
  EXPECT_NEAR(lane.cum_s[1], 3.0, 1e-6);
  EXPECT_NEAR(lane.cum_s[2], 7.0, 1e-6);
}

TEST(IrBuilder, BuildSegments) {
  std::vector<Vec2> pts{{0, 0}, {1, 0}, {1, 1}};
  auto lane = BuildLane(2, pts);
  auto segs = BuildSegmentsForLane(lane, 10);
  ASSERT_EQ(segs.size(), 2u);
  EXPECT_EQ(segs[0].id, 10);
  EXPECT_EQ(segs[0].lane_id, 2);
  EXPECT_NEAR(segs[0].s0, 0.0, 1e-6);
  EXPECT_NEAR(segs[0].s1, 1.0, 1e-6);
  EXPECT_EQ(segs[1].id, 11);
  EXPECT_NEAR(segs[1].s0, 1.0, 1e-6);
  EXPECT_NEAR(segs[1].s1, 2.0, 1e-6);
}

TEST(IrBuilder, BuildTileMultiLane) {
  auto l1 = BuildLane(1, {{0, 0}, {1, 0}});
  auto l2 = BuildLane(2, {{0, 1}, {0, 2}, {0, 3}});
  TileIR tile = BuildTile("tile_a", {l1, l2}, /*start_seg_id=*/100);
  EXPECT_EQ(tile.id, "tile_a");
  EXPECT_EQ(tile.lanes.size(), 2u);
  EXPECT_EQ(tile.segments.size(), 1u + 2u);
  EXPECT_EQ(tile.segments.front().id, 100);
  EXPECT_EQ(tile.segments.back().id, 102);
}

TEST(IrBuilder, BuildTileSetSnapshot) {
  std::unordered_map<TileId, std::vector<Lane>> m;
  m["t1"] = {BuildLane(1, {{0, 0}, {1, 0}})};
  m["t2"] = {BuildLane(2, {{0, 1}, {0, 2}})};
  auto set = BuildTileSetSnapshot("city", "v1", m, 100);
  ASSERT_EQ(set->tiles.size(), 2u);
  EXPECT_EQ(set->map_id, "city");
  EXPECT_EQ(set->version, "v1");
  size_t seg_total = set->tiles[0]->ir->segments.size() + set->tiles[1]->ir->segments.size();
  EXPECT_EQ(seg_total, 2u);  // 每条 lane 1 段
}

TEST(IrBuilder, PublishToCatalog) {
  std::unordered_map<TileId, std::vector<Lane>> m;
  m["t1"] = {BuildLane(1, {{0, 0}, {1, 0}})};
  MapCatalog catalog;
  auto st = PublishTileSet(&catalog, "city", "v1", m, 0);
  ASSERT_TRUE(st.ok());
  auto got = catalog.Get("city", "v1");
  ASSERT_TRUE(got.ok());
  EXPECT_EQ(got.value()->tiles.size(), 1u);
}
