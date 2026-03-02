#pragma once

#include "primitives/Point2D.h"
#include "primitives/Segment2D.h"

namespace cg {

double distance2D(const Point2D& a, const Point2D& b);

double segment2DLength(Segment2D segment);
}
