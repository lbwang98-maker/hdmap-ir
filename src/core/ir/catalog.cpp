#include "core/ir/catalog.h"

namespace hdmap::ir {

Status MapCatalog::Put(const MapId& map_id, const VersionId& version,
                       std::shared_ptr<const TileSetSnapshot> snapshot) {
  store_[{map_id, version}] = std::move(snapshot);
  return OkStatus();
}

StatusOr<std::shared_ptr<const TileSetSnapshot>> MapCatalog::Get(const MapId& map_id,
                                                                 const VersionId& version) const {
  auto it = store_.find({map_id, version});
  if (it == store_.end()) {
    return Status(StatusCode::kNotFound, "snapshot not found");
  }
  return it->second;
}

size_t MapCatalog::Size() const {
  return store_.size();
}

}  // namespace hdmap::ir
