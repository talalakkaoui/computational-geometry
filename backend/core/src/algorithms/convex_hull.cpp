#include <vector>
#include <stdexcept>
#include <algorithm>
#include "primitives/Point2D.h"
#include "primitives/predicates.h"
#include "algorithms/sort_points_2d.h"
#include "algorithms/convex_hull.h"

namespace cg {


    Polygon2D slow_convex_hull(const std::vector<Point2D>& points) {
        if (points.size() < 3) {
            throw std::invalid_argument("At least 3 points are required to compute a convex hull.");
        }

        std::vector<Point2D> hull;
        for (Point2D current : points) {
            for (Point2D next : points) {
                if (current.x == next.x && current.y == next.y) {
                    continue;
                }
                bool is_left = true;
                for (Point2D other : points) {
                    if (other.x == current.x && other.y == current.y) {
                        continue;
                    }
                    if (other.x == next.x && other.y == next.y) {
                        continue;
                    }
                    double cross_product = cg::cross_product(current, next, other);
                    if (cross_product < 0) {
                        is_left = false;
                        break;
                    }
                }
                if (is_left) {
                    hull.push_back(current);
                    break;
        }
            }
        }
        return Polygon2D(hull, true);
    }

    Polygon2D convex_hull_grahams_scan(const std::vector<Point2D>& points) {
        if (points.size() < 3) {
            throw std::invalid_argument("At least 3 points are required to compute a convex hull.");
        }

        std::vector<Point2D> sorted_points = sort_by_x(points);
        std::vector<Point2D> hull;

        std::vector<Point2D> upper_hull;
        for (int i = (int)sorted_points.size() - 1; i >= 0; --i) {
            while (upper_hull.size() >= 2 &&
                cg::cross_product(upper_hull[upper_hull.size() - 2], upper_hull.back(), sorted_points[i]) <= 0) {
                upper_hull.pop_back();
            }
            upper_hull.push_back(sorted_points[i]);
        }

        std::vector<Point2D> lower_hull;
        lower_hull.push_back(sorted_points[0]);
        lower_hull.push_back(sorted_points[1]);
        for (size_t i = 2; i < sorted_points.size(); ++i) {
            while (lower_hull.size() >= 2 &&
                cg::cross_product(lower_hull[lower_hull.size() - 2], lower_hull.back(), sorted_points[i]) <= 0) {
                lower_hull.pop_back();
            }
            lower_hull.push_back(sorted_points[i]);
        }

        hull.insert(hull.end(), upper_hull.begin(), upper_hull.end() - 1);
        hull.insert(hull.end(), lower_hull.begin(), lower_hull.end() - 1);
        return Polygon2D(hull, true);
    }


    Polygon2D convex_hull_jarvis_march(const std::vector<Point2D>& points) {
        if (points.size() < 3) {
            throw std::invalid_argument("At least 3 points are required to compute a convex hull.");
        }

        int leftmost = 0;
        for (size_t i = 1; i < points.size(); ++i) {
            if (points[i].y < points[leftmost].y || 
                (points[i].y == points[leftmost].y && points[i].x < points[leftmost].x)) {
                leftmost = i;
            }
        }

        std::vector<Point2D> hull;
        int current = leftmost;

        do {
            hull.push_back(points[current]);
            int next = (current + 1) % points.size();

            for (size_t i = 0; i < points.size(); ++i) {
                double cross_product = cg::cross_product(points[current], points[next], points[i]);
                if (cross_product < 0) {
                    next = i;
                }
            }

            current = next;
        } while (current != leftmost);

        return Polygon2D(hull, true);
    }
}