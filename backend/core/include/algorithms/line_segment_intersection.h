#pragma once

#include <vector>
#include "primitives/Segment2D.h"

namespace cg {

    // Output type: one entry per intersection point, with all segments through it
    struct Intersection {
        Point2D point;
        std::vector<Segment2D> segments;
    };

    std::vector<Intersection> line_segment_intersection(const std::vector<Segment2D>& segments);

}