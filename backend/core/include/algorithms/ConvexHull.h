#pragma once
#include "primitives/Point2D.h"
#include "primitives/Polygon2D.h"

namespace cg {
    
    Polygon2D SlowConvexHull(const std::vector<Point2D>& points);
    
    Polygon2D convexHullGrahamsScan(const std::vector<Point2D>& points);
    
    Polygon2D convexHullJarvisMarch(const std::vector<Point2D>& points);
}