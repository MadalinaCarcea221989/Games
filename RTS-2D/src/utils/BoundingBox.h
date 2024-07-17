#pragma once
#include <algorithm>
namespace Tmpl8 {
    struct BoundingBox {
        int left;
        int top;
        int right;
        int bottom;
    };
    BoundingBox CreateBoundingBox(int startX, int startY, int endX, int endY){
        BoundingBox box;
        box.left = std::min(startX, endX);
        box.top = std::min(startY, endY);
        box.right = std::max(startX, endX);
        box.bottom = std::max(startY, endY);
        return box;
    }
    bool PointInsideBoundingBox(int x, int y, const BoundingBox& box) {
    return x >= box.left && x <= box.right && y >= box.top && y <= box.bottom;
}

}