add_library(core
    src/algorithms/distance.cpp
    src/algorithms/convex_hull.cpp
    src/algorithms/sort_points_2d.cpp
    src/algorithms/line_segment_intersection.cpp
)

target_include_directories(core PUBLIC include)
