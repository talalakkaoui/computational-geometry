#include <vector>
#include <algorithm>
#include "primitives/Point2D.h"

namespace cg {

    std::vector<Point2D> sort_by_x(const std::vector<Point2D>& points) {
        
        std::vector<Point2D> sorted_points(points);
        std::sort(sorted_points.begin(), sorted_points.end(), [](const Point2D& a, const Point2D& b) {
            return (a.x < b.x) || (a.x == b.x && a.y < b.y);
        });
        return sorted_points;
    }

    std::vector<Point2D> sort_by_y(const std::vector<Point2D>& points) {
        
        std::vector<Point2D> sorted_points(points);
        std::sort(sorted_points.begin(), sorted_points.end(), [](const Point2D& a, const Point2D& b) {
            return (a.y < b.y) || (a.y == b.y && a.x < b.x);
        });
        return sorted_points;
    }
}