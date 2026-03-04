add_library(core
    src/algorithms/distance.cpp
    src/algorithms/ConvexHull.cpp
    src/algorithms/sortPoint2D.cpp
)

target_include_directories(core PUBLIC include)
