#include "primitives/Point2D.h"
#include "algorithms/distance.h"
#include "primitives/Segment2D.h"
#include "httplib.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main() {
    httplib::Server svr;

    svr.Post("/api/distance", [](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);
        cg::Point2D a(body["points"][0]["x"], body["points"][0]["y"]);
        cg::Point2D b(body["points"][1]["x"], body["points"][1]["y"]);
        json result = { {"distance", cg::distance2D(a, b)} };
        res.set_content(result.dump(), "application/json");
    });

    svr.Post("/api/segment-length", [](const httplib::Request& req, httplib::Response& res) {
        auto body = json::parse(req.body);
        cg::Point2D a(body["points"][0]["x"], body["points"][0]["y"]);
        cg::Point2D b(body["points"][1]["x"], body["points"][1]["y"]);
        cg::Segment2D segment(a, b);
        json result = { {"length", cg::segment2DLength(segment)} };
        res.set_content(result.dump(), "application/json");
    });

    svr.listen("0.0.0.0", 8080);
    return 0;
}