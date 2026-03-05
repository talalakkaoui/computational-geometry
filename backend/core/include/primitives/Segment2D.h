#pragma once
#include "Point2D.h"

namespace cg {

struct Segment2D {
    Point2D start, end;

    Segment2D(const Point2D& start, const Point2D& end) : start(start), end(end) {}

    Point2D upper() const {
        if (start.y > end.y) return start;
        if (end.y > start.y) return end;
        return (start.x < end.x) ? start : end; // horizontal: left is upper
    }

    Point2D lower() const {
        if (start.y < end.y) return start;
        if (end.y < start.y) return end;
        return (start.x > end.x) ? start : end; // horizontal: right is lower
    }

    bool operator==(const Segment2D& other) const {
        return start.x == other.start.x && start.y == other.start.y
            && end.x == other.end.x     && end.y == other.end.y;
    }

    bool operator!=(const Segment2D& other) const {
        return !(*this == other);
    }
};

}