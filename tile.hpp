#pragma once
#include "types.hpp"
#include <array>
#include <cstddef>

namespace inkforge {
constexpr int TileSize = 256;
struct Pixel { std::uint8_t r, g, b, a; };

class Tile {
public:
    Tile() { clear(); }
    void clear() { pixels_.fill(Pixel{0, 0, 0, 0}); }
    Pixel& at(int x, int y) { return pixels_[static_cast<std::size_t>(y) * TileSize + x]; }
    const Pixel& at(int x, int y) const { return pixels_[static_cast<std::size_t>(y) * TileSize + x]; }
    const Pixel* data() const { return pixels_.data(); }
private:
    std::array<Pixel, TileSize * TileSize> pixels_{};
};
}
