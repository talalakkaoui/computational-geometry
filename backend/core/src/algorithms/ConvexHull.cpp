#include <vector>
#include <stdexcept>
#include <algorithm>
#include "primitives/Point2D.h"
#include "primitives/predicates.h"
#include "algorithms/sortPoint2D.h"
#include "algorithms/ConvexHull.h"

namespace cg {


    Polygon2D SlowConvexHull(const std::vector<Point2D>& points) {
        if (points.size() < 3) {
            throw std::invalid_argument("At least 3 points are required to compute a convex hull.");
        }

        std::vector<Point2D> hull;
        for (Point2D current : points) {
            for (Point2D next : points) {
                if (current.x == next.x && current.y == next.y) {
                    continue;
                }
                bool isLeft = true;
                for (Point2D other : points) {
                    if (other.x == current.x && other.y == current.y) {
                        continue;
                    }
                    if (other.x == next.x && other.y == next.y) {
                        continue;
                    }
                    double crossProduct = cg::crossProduct(current, next, other);
                    if (crossProduct < 0) {
                        isLeft = false;
                        break;
                    }
                }
                if (isLeft) {
                    hull.push_back(current);
                    break;
        }
            }
        }
        return Polygon2D(hull);
    }

    Polygon2D convexHullGrahamsScan(const std::vector<Point2D>& points) {
        if (points.size() < 3) {
            throw std::invalid_argument("At least 3 points are required to compute a convex hull.");
        }

        std::vector<Point2D> sortedPoints = sortbyX(points);
        std::vector<Point2D> hull;

        std::vector<Point2D> upperHull;
        for (int i = (int)sortedPoints.size() - 1; i >= 0; --i) {
            while (upperHull.size() >= 2 &&
                cg::crossProduct(upperHull[upperHull.size() - 2], upperHull.back(), sortedPoints[i]) <= 0) {
                upperHull.pop_back();
            }
            upperHull.push_back(sortedPoints[i]);
        }

        std::vector<Point2D> lowerHull;
        lowerHull.push_back(sortedPoints[0]);
        lowerHull.push_back(sortedPoints[1]);
        for (size_t i = 2; i < sortedPoints.size(); ++i) {
            while (lowerHull.size() >= 2 &&
                cg::crossProduct(lowerHull[lowerHull.size() - 2], lowerHull.back(), sortedPoints[i]) <= 0) {
                lowerHull.pop_back();
            }
            lowerHull.push_back(sortedPoints[i]);
        }

        hull.insert(hull.end(), upperHull.begin(), upperHull.end() - 1);
        hull.insert(hull.end(), lowerHull.begin(), lowerHull.end() - 1);
        return Polygon2D(hull);
    }


    Polygon2D convexHullJarvisMarch(const std::vector<Point2D>& points) {
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
                double crossProduct = cg::crossProduct(points[current], points[next], points[i]);
                if (crossProduct < 0) {
                    next = i;
                }
            }

            current = next;
        } while (current != leftmost);

        return Polygon2D(hull);
    }
}