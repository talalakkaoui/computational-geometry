#include "algorithms/distance.h"
#include <cmath>

namespace cg {

double distance_2d(const Point2D& a, const Point2D& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

double segment_2d_length(Segment2D segment) {
    return distance_2d(segment.start, segment.end);
}

}
