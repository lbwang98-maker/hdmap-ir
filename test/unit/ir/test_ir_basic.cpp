#include <gtest/gtest.h>

#include "core/ir/catalog.h"
#include "core/ir/lane.h"
#include "core/ir/tile.h"

using namespace hdmap::ir;

TEST(IrBasic, PutGet) {
  auto tile_ir = std::make_shared<TileIR>();
  tile_ir->id = "tile_1";
  Lane lane;
  lane.id = 1;
  tile_ir->lanes.push_back(lane);
  SegmentMeta seg;
  seg.id = 10;
  seg.lane_id = 1;
  tile_ir->segments.push_back(seg);

  auto tile_snap = std::make_shared<TileSnapshot>();
  tile_snap->id = "tile_1";
  tile_snap->ir = tile_ir;

  auto set = std::make_shared<TileSetSnapshot>();
  set->map_id = "city";
  set->version = "v1";
  set->tiles.push_back(tile_snap);

  MapCatalog catalog;
  auto st = catalog.Put("city", "v1", set);
  EXPECT_TRUE(st.ok());
  EXPECT_EQ(catalog.Size(), 1u);

  auto got = catalog.Get("city", "v1");
  EXPECT_TRUE(got.ok());
  auto snap = got.value();
  EXPECT_EQ(snap->tiles.size(), 1u);
  EXPECT_EQ(snap->tiles[0]->ir->lanes.size(), 1u);
  EXPECT_EQ(snap->tiles[0]->ir->lanes[0].id, 1);
}

TEST(IrBasic, NotFound) {
  MapCatalog catalog;
  auto res = catalog.Get("city", "missing");
  EXPECT_FALSE(res.ok());
  EXPECT_EQ(res.status().code(), StatusCode::kNotFound);
}
