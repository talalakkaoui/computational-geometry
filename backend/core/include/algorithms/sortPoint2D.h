#pragma once

#include <vector>
#include "primitives/Point2D.h"

namespace cg {

    std::vector<Point2D> sortbyX(const std::vector<Point2D>& points);

    std::vector<Point2D> sortbyY(const std::vector<Point2D>& points);
}