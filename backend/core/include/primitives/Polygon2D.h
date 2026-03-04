#pragma once
#include <vector>
#include <stdexcept>
#include "Point2D.h"

namespace cg {

struct Polygon2D {
    std::vector<Point2D> vertices;
    bool is_closed = false;

    explicit Polygon2D(std::vector<Point2D> vertices, bool is_closed = false) : vertices(std::move(vertices)), is_closed(is_closed) {
        if (this->vertices.size() < 3) {
            throw std::invalid_argument("A polygon must have at least 3 vertices.");
        }
    }
};

}