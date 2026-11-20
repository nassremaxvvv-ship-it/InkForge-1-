#pragma once
#include "document.hpp"
#include <vector>

namespace inkforge {
struct BrushSettings {
    float size{12.0f};
    float opacity{1.0f};
    Color color{0, 0, 0, 255};
};

class Brush {
public:
    explicit Brush(BrushSettings settings = {});
    void setSettings(const BrushSettings& settings);
    const BrushSettings& settings() const { return settings_; }
    void beginStroke(Document& doc, std::size_t layer, Point point);
    void continueStroke(Point point);
    void endStroke();
private:
    void dab(Point point);
    void drawSegment(Point from, Point to);
    BrushSettings settings_;
    Document* document_{nullptr};
    std::size_t layer_{0};
    Point previous_{};
};
}
