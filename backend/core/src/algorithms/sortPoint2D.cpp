#include <vector>
#include <algorithm>
#include "primitives/Point2D.h"

namespace cg {

    std::vector<Point2D> sortbyX(const std::vector<Point2D>& points) {
        
        std::vector<Point2D> sortedPoints(points);
        std::sort(sortedPoints.begin(), sortedPoints.end(), [](const Point2D& a, const Point2D& b) {
            return (a.x < b.x) || (a.x == b.x && a.y < b.y);
        });
        return sortedPoints;
    }

    std::vector<Point2D> sortbyY(const std::vector<Point2D>& points) {
        
        std::vector<Point2D> sortedPoints(points);
        std::sort(sortedPoints.begin(), sortedPoints.end(), [](const Point2D& a, const Point2D& b) {
            return (a.y < b.y) || (a.y == b.y && a.x < b.x);
        });
        return sortedPoints;
    }
}