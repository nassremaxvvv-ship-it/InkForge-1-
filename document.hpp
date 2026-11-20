#pragma once
#include "tile.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace inkforge {
struct TileCoord {
    int x, y;
    bool operator==(const TileCoord& o) const noexcept { return x == o.x && y == o.y; }
};
struct TileCoordHash {
    std::size_t operator()(const TileCoord& p) const noexcept {
        const auto a = static_cast<std::uint32_t>(p.x);
        const auto b = static_cast<std::uint32_t>(p.y);
        return (static_cast<std::size_t>(a) * 0x9e3779b1u) ^ static_cast<std::size_t>(b);
    }
};

class Layer {
public:
    explicit Layer(std::string name);
    const std::string& name() const { return name_; }
    void setVisible(bool v) { visible_ = v; }
    bool visible() const { return visible_; }
    void setOpacity(float v);
    float opacity() const { return opacity_; }
    Tile& tile(int tileX, int tileY);
    const Tile* findTile(int tileX, int tileY) const;
    std::size_t allocatedTileCount() const { return tiles_.size(); }
private:
    std::string name_;
    bool visible_{true};
    float opacity_{1.0f};
    std::unordered_map<TileCoord, std::unique_ptr<Tile>, TileCoordHash> tiles_;
};

class Document {
public:
    Document();
    std::size_t addLayer(const std::string& name);
    Layer& layer(std::size_t index);
    const Layer& layer(std::size_t index) const;
    std::size_t layerCount() const { return layers_.size(); }
    bool undo();
    bool redo();
    void clearHistory();
private:
    struct PixelChange { std::size_t layer; int x, y; Pixel before, after; };
    friend class Brush;
    void record(PixelChange change);
    void apply(const PixelChange& change, bool useAfter);
    std::vector<std::unique_ptr<Layer>> layers_;
    std::vector<std::vector<PixelChange>> undo_;
    std::vector<std::vector<PixelChange>> redo_;
    std::vector<PixelChange> activeStroke_;
};
}
