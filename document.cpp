#include "inkforge/document.hpp"
#include <stdexcept>

namespace inkforge {
Layer::Layer(std::string name) : name_(std::move(name)) {}
void Layer::setOpacity(float v) { opacity_ = v < 0 ? 0 : (v > 1 ? 1 : v); }
Tile& Layer::tile(int tx, int ty) {
    TileCoord key{tx, ty};
    auto& ptr = tiles_[key];
    if (!ptr) ptr = std::make_unique<Tile>();
    return *ptr;
}
const Tile* Layer::findTile(int tx, int ty) const {
    auto it = tiles_.find(TileCoord{tx, ty});
    return it == tiles_.end() ? nullptr : it->second.get();
}
Document::Document() { addLayer("Layer 1"); }
std::size_t Document::addLayer(const std::string& name) {
    layers_.push_back(std::make_unique<Layer>(name));
    return layers_.size() - 1;
}
Layer& Document::layer(std::size_t i) { if (i >= layers_.size()) throw std::out_of_range("layer index"); return *layers_[i]; }
const Layer& Document::layer(std::size_t i) const { if (i >= layers_.size()) throw std::out_of_range("layer index"); return *layers_[i]; }
void Document::record(PixelChange c) { activeStroke_.push_back(c); }
void Document::apply(const PixelChange& c, bool after) {
    const int tx = c.x >= 0 ? c.x / TileSize : (c.x - TileSize + 1) / TileSize;
    const int ty = c.y >= 0 ? c.y / TileSize : (c.y - TileSize + 1) / TileSize;
    const int px = c.x - tx * TileSize, py = c.y - ty * TileSize;
    layer(c.layer).tile(tx, ty).at(px, py) = after ? c.after : c.before;
}
bool Document::undo() {
    if (undo_.empty()) return false;
    auto stroke = std::move(undo_.back()); undo_.pop_back();
    for (auto it = stroke.rbegin(); it != stroke.rend(); ++it) apply(*it, false);
    redo_.push_back(std::move(stroke)); return true;
}
bool Document::redo() {
    if (redo_.empty()) return false;
    auto stroke = std::move(redo_.back()); redo_.pop_back();
    for (const auto& c : stroke) apply(c, true);
    undo_.push_back(std::move(stroke)); return true;
}
void Document::clearHistory() { undo_.clear(); redo_.clear(); activeStroke_.clear(); }
}
