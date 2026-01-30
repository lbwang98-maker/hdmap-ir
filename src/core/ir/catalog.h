#pragma once
#include <functional>
#include <memory>
#include <unordered_map>
#include <utility>

#include "core/ir/status.h"
#include "core/ir/tile.h"

namespace hdmap::ir {

class MapCatalog {
 public:
  Status Put(const MapId& map_id, const VersionId& version,
             std::shared_ptr<const TileSetSnapshot> snapshot);

  StatusOr<std::shared_ptr<const TileSetSnapshot>> Get(const MapId& map_id,
                                                       const VersionId& version) const;

  size_t Size() const;

 private:
  struct PairHash {
    size_t operator()(const std::pair<MapId, VersionId>& p) const noexcept {
      return std::hash<MapId>{}(p.first) ^ (std::hash<VersionId>{}(p.second) << 1);
    }
  };
  // 字典-键值对，后续可加锁
  std::unordered_map<std::pair<MapId, VersionId>, std::shared_ptr<const TileSetSnapshot>, PairHash>
      store_;
};

}  // namespace hdmap::ir
