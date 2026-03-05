#include <vector>
#include <algorithm>
#include <cmath>
#include "primitives/Point2D.h"
#include "primitives/Segment2D.h"
#include "primitives/predicates.h"
#include "algorithms/line_segment_intersection.h"

namespace cg {

static constexpr double kTolerance  = 1e-10;  // floating point comparison epsilon
static constexpr double kSweepNudge = 1e-9;   // small offset below event point to re-order T

struct EventPoint {
    Point2D point;
    std::vector<const Segment2D*> upper_segs;
};

static bool ep_less(const EventPoint& a, const EventPoint& b) {
    if (std::abs(a.point.y - b.point.y) > kTolerance) return a.point.y > b.point.y;
    return a.point.x < b.point.x;
}

static void insert_into_Q(std::vector<EventPoint>& Q, const Point2D& p,
                           const Segment2D* seg = nullptr) {
    for (auto& ep : Q) {
        if (ep.point == p) {
            if (seg) ep.upper_segs.push_back(seg);
            return;
        }
    }
    EventPoint ep{p, {}};
    if (seg) ep.upper_segs.push_back(seg);
    auto pos = std::lower_bound(Q.begin(), Q.end(), ep, ep_less);
    Q.insert(pos, ep);
}

static void find_new_event(const Segment2D* sl, const Segment2D* sr,
                            const Point2D& p, std::vector<EventPoint>& Q) {
    if (!sl || !sr) return;
    auto pt = segment_intersection_point(*sl, *sr);
    if (!pt) return;
    bool below = pt->y < p.y - kTolerance;
    bool same_right = std::abs(pt->y - p.y) < kTolerance && pt->x > p.x + kTolerance;
    if (below || same_right) {
        insert_into_Q(Q, *pt);
    }
}

static void handle_event_point(const EventPoint& ep,
                                std::vector<const Segment2D*>& T,
                                std::vector<EventPoint>& Q,
                                std::vector<Intersection>& results) {
    const Point2D& p = ep.point;

    std::vector<const Segment2D*> U = ep.upper_segs;

    std::vector<const Segment2D*> L, C;
    for (const Segment2D* s : T) {
        if (s->lower() == p) {
            L.push_back(s);
        } else if (std::abs(x_at_y(*s, p.y) - p.x) < kTolerance) {
            C.push_back(s);
        }
    }

    if (U.size() + L.size() + C.size() > 1) {
        Intersection inter{p, {}};
        for (auto* s : U) inter.segments.push_back(*s);
        for (auto* s : L) inter.segments.push_back(*s);
        for (auto* s : C) inter.segments.push_back(*s);
        results.push_back(inter);
    }

    T.erase(std::remove_if(T.begin(), T.end(), [&](const Segment2D* s) {
        for (auto* l : L) if (s == l) return true;
        for (auto* c : C) if (s == c) return true;
        return false;
    }), T.end());

    double y_below = p.y - kSweepNudge;
    std::vector<const Segment2D*> to_insert;
    for (auto* s : U) to_insert.push_back(s);
    for (auto* s : C) to_insert.push_back(s);

    for (const Segment2D* s : to_insert) {
        auto pos = std::lower_bound(T.begin(), T.end(), s,
            [y_below](const Segment2D* a, const Segment2D* b) {
                return x_at_y(*a, y_below) < x_at_y(*b, y_below);
            });
        T.insert(pos, s);
    }

    if (to_insert.empty()) {
        const Segment2D* sl = nullptr;
        const Segment2D* sr = nullptr;
        for (int i = 0; i < (int)T.size(); i++) {
            if (x_at_y(*T[i], y_below) < p.x) sl = T[i];
            else if (!sr) sr = T[i];
        }
        find_new_event(sl, sr, p, Q);
    } else {
        auto cmp = [y_below](const Segment2D* a, const Segment2D* b) {
            return x_at_y(*a, y_below) < x_at_y(*b, y_below);
        };
        const Segment2D* s_left  = *std::min_element(to_insert.begin(), to_insert.end(), cmp);
        const Segment2D* s_right = *std::max_element(to_insert.begin(), to_insert.end(), cmp);

        const Segment2D* sl = nullptr;
        const Segment2D* sr = nullptr;
        for (int i = 0; i < (int)T.size(); i++) {
            if (T[i] == s_left  && i > 0)              sl = T[i - 1];
            if (T[i] == s_right && i < (int)T.size()-1) sr = T[i + 1];
        }
        find_new_event(sl, s_left,  p, Q);
        find_new_event(s_right, sr, p, Q);
    }
}

std::vector<Intersection> line_segment_intersection(const std::vector<Segment2D>& segments) {
    std::vector<EventPoint> Q;
    std::vector<const Segment2D*> T;
    std::vector<Intersection> results;

    for (const Segment2D& s : segments) {
        insert_into_Q(Q, s.upper(), &s);
        insert_into_Q(Q, s.lower());
    }

    while (!Q.empty()) {
        EventPoint ep = Q.front();
        Q.erase(Q.begin());
        handle_event_point(ep, T, Q, results);
    }

    return results;
}

}
