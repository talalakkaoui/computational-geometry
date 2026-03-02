add_library(core
    src/primitives/Point2D.cpp
    src/algorithms/distance.cpp
)

target_include_directories(core PUBLIC include)
