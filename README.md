# hdmap-ir

High-precision map IR for Lanelet2/OpenDRIVE: unified geometry/IR, grid index, and high-performance queries (NearestLane/Project/BBox/LRS). Design doc: `hdmap-ir_design_doc_v0.3.pdf` (2026-01-29).

## Status
- 2026-01-29：完成 Day 1 几何基础（Vec2/AABB/Segment）及单元测试。
- 后续按设计文档路径推进：core/ir → index/grid → query/nearest → service。

## Repo layout
- `src/geo/geometry`：几何基础。
- `include/hdmap_ir`：公共头聚合。
- `test/unit`：GoogleTest 单测；`test/integration` 预留。
- `scripts/format*.sh`：clang-format 格式化/检查。
- `docs`：参考与性能记录。
- `cmake`, `proto`, `bench`, `data/samples`：按设计文档预留。

## Build & test (本地)
```bash
cmake -S . -B build -G "MinGW Makefiles" -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

## Code style
- clang-format 配置见 `.clang-format`。
- 快速格式化：`./scripts/format.sh`
- 仅检查：`./scripts/format_check.sh`

## CI
- `.github/workflows/ci.yml`：Ubuntu 上构建 + 测试 + 格式检查。

## Roadmap (简要)
1) `core/ir`：Lane/Segment IR、TileSnapshot/TileSetSnapshot/MapCatalog 不可变快照。
2) `index/grid`：Uniform Grid 索引与参数调优。
3) `query`：NearestLane/Project/BBox/LRS 查询管线。
4) `service`：gRPC 封装，支持多版本地图热切换。

欢迎在完成阶段性模块后持续 push；CI 会自动跑基础检查和测试。

