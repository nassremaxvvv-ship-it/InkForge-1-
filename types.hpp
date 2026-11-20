#pragma once
#include <cstdint>
#include <algorithm>

namespace inkforge {
struct Color {
    std::uint8_t r{0}, g{0}, b{0}, a{255};
};
struct Point {
    float x{0}, y{0};
    float pressure{1.0f};
};
struct Rect {
    int x{0}, y{0}, width{0}, height{0};
};
inline std::uint8_t clampByte(float v) {
    return static_cast<std::uint8_t>(std::clamp(v, 0.0f, 255.0f));
}
}
