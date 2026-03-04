#pragma once
#include "primitives/Point2D.h"
#include "primitives/Polygon2D.h"

namespace cg {
    
    Polygon2D slow_convex_hull(const std::vector<Point2D>& points);
    
    Polygon2D convex_hull_grahams_scan(const std::vector<Point2D>& points);
    
    Polygon2D convex_hull_jarvis_march(const std::vector<Point2D>& points);
}