#pragma once

#include <vector>
#include "primitives/Point2D.h"

namespace cg {

    std::vector<Point2D> sort_by_x(const std::vector<Point2D>& points);

    std::vector<Point2D> sort_by_y(const std::vector<Point2D>& points);
}