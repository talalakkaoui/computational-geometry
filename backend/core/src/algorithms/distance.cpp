#include "algorithms/distance.h"
#include <cmath>

namespace cg {

double distance2D(const Point2D& a, const Point2D& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

double segment2DLength(Segment2D segment) {
    return distance2D(segment.start, segment.end);
}

}
