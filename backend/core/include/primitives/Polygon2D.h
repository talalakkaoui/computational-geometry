#pragma once
#include <vector>
#include <stdexcept>
#include "Point2D.h"

namespace cg {

struct Polygon2D {
    std::vector<Point2D> vertices;

    explicit Polygon2D(std::vector<Point2D> vertices) : vertices(std::move(vertices)) {
        if (this->vertices.size() < 3) {
            throw std::invalid_argument("A polygon must have at least 3 vertices.");
        }
    }
};

}