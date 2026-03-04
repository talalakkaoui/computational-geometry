#pragma once
#include "Point2D.h"

namespace cg {

    inline double cross_product(const Point2D& O, const Point2D& A, const Point2D& B) {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    }
}