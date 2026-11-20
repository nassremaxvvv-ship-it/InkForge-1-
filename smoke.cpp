#include "inkforge/brush.hpp"
#include <cassert>
int main() {
    inkforge::Document doc;
    inkforge::Brush brush({8.0f, 1.0f, {220, 20, 30, 255}});
    brush.beginStroke(doc, 0, {20, 20, 1.0f});
    brush.continueStroke({40, 20, 1.0f});
    brush.endStroke();
    assert(doc.layer(0).allocatedTileCount() == 1);
    const auto *tile = doc.layer(0).findTile(0, 0);
    assert(tile && tile->at(20, 20).a > 0);
    assert(doc.undo());
    assert(doc.layer(0).findTile(0, 0)->at(20, 20).a == 0);
    assert(doc.redo());
    assert(doc.layer(0).findTile(0, 0)->at(20, 20).a > 0);
}
