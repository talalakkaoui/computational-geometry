#include "primitives/Point2D.h"
#include "primitives/Polygon2D.h"
#include "algorithms/distance.h"
#include "algorithms/convex_hull.h"
#include "algorithms/line_segment_intersection.h"
#include "primitives/Segment2D.h"
#include "httplib.h"
#include "nlohmann/json.hpp"
#include <cstdlib>

using json = nlohmann::json;

int main() {
    httplib::Server svr;

    svr.set_post_routing_handler([](const httplib::Request&, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
    });

    svr.Options(".*", [](const httplib::Request&, httplib::Response& res) {
        res.status = 204;
    });

    svr.Post("/api/distance", [](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);
        cg::Point2D a(body["points"][0]["x"], body["points"][0]["y"]);
        cg::Point2D b(body["points"][1]["x"], body["points"][1]["y"]);
        json result = { {"distance", cg::distance_2d(a, b)} };
        res.set_content(result.dump(), "application/json");
    });

    svr.Post("/api/segment-length", [](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);
        cg::Point2D a(body["points"][0]["x"], body["points"][0]["y"]);
        cg::Point2D b(body["points"][1]["x"], body["points"][1]["y"]);
        cg::Segment2D segment(a, b);
        json result = { {"length", cg::segment_2d_length(segment)} };
        res.set_content(result.dump(), "application/json");
    });

    svr.Post("/api/convex-hull/slow", [](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);
        std::vector<cg::Point2D> points;
        for (const auto& point : body["points"]) {
            points.emplace_back(point["x"], point["y"]);
        }
        cg::Polygon2D hull = cg::slow_convex_hull(points);
        json vertices = json::array();
        for (const auto& point : hull.vertices) {
            vertices.push_back({ {"x", point.x}, {"y", point.y} });
        }
        json result = { {"polygon", { {"vertices", vertices}, {"is_closed", hull.is_closed} }} };
        res.set_content(result.dump(), "application/json");
    });

    svr.Post("/api/convex-hull/graham-scan", [](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);
        std::vector<cg::Point2D> points;
        for (const auto& point : body["points"]) {
            points.emplace_back(point["x"], point["y"]);
        }
        cg::Polygon2D hull = cg::convex_hull_grahams_scan(points);
        json vertices = json::array();
        for (const auto& point : hull.vertices) {
            vertices.push_back({ {"x", point.x}, {"y", point.y} });
        }
        json result = { {"polygon", { {"vertices", vertices}, {"is_closed", hull.is_closed} }} };
        res.set_content(result.dump(), "application/json");
    });

    svr.Post("/api/convex-hull/jarvis-march", [](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);
        std::vector<cg::Point2D> points;
        for (const auto& point : body["points"]) {
            points.emplace_back(point["x"], point["y"]);
        }
        cg::Polygon2D hull = cg::convex_hull_jarvis_march(points);
        json vertices = json::array();
        for (const auto& point : hull.vertices) {
            vertices.push_back({ {"x", point.x}, {"y", point.y} });
        }
        json result = { {"polygon", { {"vertices", vertices}, {"is_closed", hull.is_closed} }} };
        res.set_content(result.dump(), "application/json");
    });

    svr.Post("/api/line-segment-intersection", [](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);
        std::vector<cg::Segment2D> segments;
        for (const auto& seg : body["segments"]) {
            cg::Point2D start(seg[0]["x"], seg[0]["y"]);
            cg::Point2D end(seg[1]["x"],   seg[1]["y"]);
            segments.emplace_back(start, end);
        }
        std::vector<cg::Intersection> intersections = cg::line_segment_intersection(segments);
        json result = json::array();
        for (const auto& inter : intersections) {
            json segs = json::array();
            for (const auto& s : inter.segments) {
                segs.push_back({
                    {"start", {{"x", s.start.x}, {"y", s.start.y}}},
                    {"end",   {{"x", s.end.x},   {"y", s.end.y}}}
                });
            }
            result.push_back({
                {"point",    {{"x", inter.point.x}, {"y", inter.point.y}}},
                {"segments", segs}
            });
        }
        res.set_content(result.dump(), "application/json");
    });

    const char* port_env = std::getenv("PORT");
    int port = port_env ? std::stoi(port_env) : 8080;
    svr.listen("0.0.0.0", port);
    return 0;
}