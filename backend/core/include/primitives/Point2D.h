#pragma once
#include <cmath>

namespace cg {

struct Point2D {
    double x, y;

    Point2D(double x, double y) : x(x), y(y) {}

    bool operator==(const Point2D& other) const {
        return std::abs(x - other.x) < 1e-10 && std::abs(y - other.y) < 1e-10;
    }

    bool operator!=(const Point2D& other) const {
        return !(*this == other);
    }
};

}
