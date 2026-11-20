#include "inkforge/brush.hpp"
#include <cmath>
#include <algorithm>
#include <unordered_map>

namespace inkforge {
Brush::Brush(BrushSettings s) : settings_(s) {}
void Brush::setSettings(const BrushSettings& s) { settings_ = s; }
void Brush::beginStroke(Document& doc, std::size_t layer, Point p) {
    if (layer >= doc.layerCount()) return;
    document_ = &doc; layer_ = layer; document_->activeStroke_.clear();
    previous_ = p; dab(p);
}
void Brush::continueStroke(Point p) { if (!document_) return; drawSegment(previous_, p); previous_ = p; }
void Brush::endStroke() {
    if (!document_) return;
    if (!document_->activeStroke_.empty()) document_->undo_.push_back(std::move(document_->activeStroke_));
    document_->redo_.clear(); document_ = nullptr;
}
void Brush::drawSegment(Point a, Point b) {
    const float dx = b.x-a.x, dy = b.y-a.y;
    const float distance = std::sqrt(dx*dx+dy*dy);
    const float spacing = std::max(1.0f, settings_.size * 0.18f);
    const int steps = std::max(1, static_cast<int>(std::ceil(distance/spacing)));
    for (int i=1; i<=steps; ++i) {
        const float t = static_cast<float>(i)/steps;
        dab(Point{a.x+dx*t, a.y+dy*t, a.pressure+(b.pressure-a.pressure)*t});
    }
}
void Brush::dab(Point p) {
    if (!document_) return;
    const float pressure = std::clamp(p.pressure, 0.05f, 1.0f);
    const float radius = std::max(0.5f, settings_.size * pressure * 0.5f);
    const int minX = static_cast<int>(std::floor(p.x-radius)), maxX = static_cast<int>(std::ceil(p.x+radius));
    const int minY = static_cast<int>(std::floor(p.y-radius)), maxY = static_cast<int>(std::ceil(p.y+radius));
    Layer& layer = document_->layer(layer_);
    for (int y=minY; y<=maxY; ++y) for (int x=minX; x<=maxX; ++x) {
        const float dx=(x+0.5f)-p.x, dy=(y+0.5f)-p.y;
        const float d=std::sqrt(dx*dx+dy*dy);
        if (d>radius) continue;
        const int tx = x>=0 ? x/TileSize : (x-TileSize+1)/TileSize;
        const int ty = y>=0 ? y/TileSize : (y-TileSize+1)/TileSize;
        const int px=x-tx*TileSize, py=y-ty*TileSize;
        Pixel& dst=layer.tile(tx,ty).at(px,py);
        Pixel before=dst;
        const float edge=std::clamp(radius-d+0.5f,0.0f,1.0f);
        const float sa=(settings_.opacity*pressure*edge*settings_.color.a)/255.0f;
        const float da=dst.a/255.0f, outA=sa+da*(1-sa);
        if (outA<=0) continue;
        dst.r=clampByte((settings_.color.r*sa+dst.r*da*(1-sa))/outA);
        dst.g=clampByte((settings_.color.g*sa+dst.g*da*(1-sa))/outA);
        dst.b=clampByte((settings_.color.b*sa+dst.b*da*(1-sa))/outA);
        dst.a=clampByte(outA*255.0f);
        if (before.r!=dst.r || before.g!=dst.g || before.b!=dst.b || before.a!=dst.a)
            document_->record(Document::PixelChange{layer_,x,y,before,dst});
    }
}
}
