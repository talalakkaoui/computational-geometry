#pragma once
#include "Point2D.h"

namespace cg {

struct Segment2D {
    Point2D start, end;

    Segment2D(const Point2D& start, const Point2D& end) : start(start), end(end) {}
};

}