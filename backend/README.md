# Backend

C++ HTTP server exposing computational geometry algorithms via a REST API.

## Code Style ([Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html))

| Element | Convention | Example |
|---|---|---|
| Classes / Structs | `PascalCase` | `Point2D`, `Polygon2D` |
| Free functions | `snake_case` | `slow_convex_hull()`, `sort_by_x()` |
| Variables | `snake_case` | `sorted_points`, `left_most` |
| Constants / Macros | `UPPER_SNAKE_CASE` | `MAX_POINTS` |
| Namespaces | `snake_case` | `cg` |
| File names (class) | `PascalCase` | `Point2D.h`, `Polygon2D.h` |
| File names (other) | `snake_case` | `convex_hull.cpp`, `sort_points_2d.h` |
