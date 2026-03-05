#pragma once
#include <optional>
#include "Point2D.h"
#include "Segment2D.h"

namespace cg {

    inline double cross_product(const Point2D& O, const Point2D& A, const Point2D& B) {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    }

    inline Point2D point_at_t(const Segment2D& s, double t) {
        return {
            s.start.x + t * (s.end.x - s.start.x),
            s.start.y + t * (s.end.y - s.start.y)
        };
    }

    inline double t_at_y(const Segment2D& s, double y) {
        return (y - s.start.y) / (s.end.y - s.start.y);
    }

    inline double x_at_y(const Segment2D& s, double y) {
        if (s.start.y == s.end.y) return s.start.x;
        double t = t_at_y(s, y);
        return s.start.x + t * (s.end.x - s.start.x);
    }

    inline std::optional<Point2D> segment_intersection_point(const Segment2D& s1, const Segment2D& s2) {
        double cp1 = cross_product(s1.start, s1.end, s2.start);
        double cp2 = cross_product(s1.start, s1.end, s2.end);
        double cp3 = cross_product(s2.start, s2.end, s1.start);
        double cp4 = cross_product(s2.start, s2.end, s1.end);
        if ((cp1 * cp2 < 0) && (cp3 * cp4 < 0)) {
            double t = cp3 / (cp3 - cp4);
            return Point2D{
                s1.start.x + t * (s1.end.x - s1.start.x),
                s1.start.y + t * (s1.end.y - s1.start.y)
            };
        }
        return std::nullopt;
    }
}