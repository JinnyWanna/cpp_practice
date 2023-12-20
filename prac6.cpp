#include <bits/stdc++.h>
// Point
struct Point {
    double x, y;

    Point() : x(0), y(0) {}

    Point(double _x, double _y) : x(_x), y(_y) {}

    Point(const Point &p) :x(p.x), y(p.y) {}

    bool operator==(const Point &p) { return (((this->x == p.x) && (this->y == p.y)) == true); }

	bool operator<=(const Point &in) const {  // A<=B true 나오면 1 // x먼저 비교 x작은순 정렬 같으면 y
        if (this->x == in.x) {
            return this->y <= in.y;
        }
        return this->x <= in.x;
    }    
};

std::istream &operator>>(std::istream &in, Point &p) {
    in >> p.x >> p.y;

    return in;
}
// Line
struct Line {
    Point p1;
    Point p2;

    Line() : p1(), p2() {}

    Line(Point _p1, Point _p2) : p1(_p1), p2(_p2) {}

    Line(const Line &l) {
        this->p1 = l.p1;
        this->p2 = l.p2;
    }

    void swap() {
        Point tmp;
        tmp.x = p1.x;
        tmp.y = p1.y;
        p1.x = p2.x;
        p1.y = p2.y;
        p2.x = tmp.x;
        p2.y = tmp.y;
    }
};

// Polygon ///////////////////////
typedef std::vector<Point> Polygon;

// function ///////////////////////

double CCW(const Point &O, const Point &A, const Point &B) { return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x); }

int ccw(Point O, Point A, Point B) {

    double cross_v = CCW(O, A, B);
    // 외적이 양수면 O A B ccw
    if (cross_v > 0)
        return 1;
    else if (cross_v < 0)
        return -1;

    return 0;
}

void input(Polygon &black, Polygon &white, const double n, const double m) {
    for (double i = 0; i < n; ++i) {
        Point p;
        std::cin >> p;

        black.push_back(p);
    }
    for (double i = 0; i < m; ++i) {
        Point p;
        std::cin >> p;

        white.push_back(p);
    }
}

void sortALL(Polygon &black, Polygon &white) {
    std::sort(black.begin(), black.end(), [](const Point &A, const Point &B) {
        if (A.y == B.y) return A.x < B.x;
        return A.y < B.y;
    });
    std::sort(black.begin() + 1, black.end(), [&black](const Point &A, const Point &B) {
        double ccw = CCW(black[0], A, B);
        if (ccw != 0) {
            return ccw > 0;
        }
        if (A.y == B.y) return A.x < B.x;

        return A.y < B.y;
    });

    std::sort(white.begin(), white.end(), [](const Point &A, const Point &B) {
        if (A.y == B.y) return A.x < B.x;
        return A.y < B.y;
    });
    std::sort(white.begin() + 1, white.end(), [&white](const Point &A, const Point &B) {
        double ccw = CCW(white[0], A, B);
        if (ccw != 0) {
            return ccw > 0;
        }
        if (A.y == B.y) return A.x < B.x;

        return A.y < B.y;
    });
}

Polygon convex_hull(Polygon &color) {
    Polygon ret;

    if (color.size() == 1) {
        ret.push_back(color[0]);
        return ret;
    }

    ret.push_back(color[0]);
    ret.push_back(color[1]);

    Point first, second;

    for (auto i = color.begin() + 2; i < color.end(); ++i) {
        while (ret.size() >= 2) {
            first = ret[ret.size() - 2];
            second = ret[ret.size() - 1];

            double ccw = CCW(first, second, *i);

            if (ccw > 0) break;

            ret.pop_back();
        }

        ret.push_back(*i);
    }

    return ret;
}

bool in_polygon(const Polygon &convex_color, const Point &p) {
    int ret = 0;

    for (int i = 0; i < convex_color.size(); ++i) {
        int j = (i + 1) % convex_color.size();

        if (((p.y - convex_color[i].y) > 0) != ((p.y - convex_color[j].y) > 0)) {
            auto intersect = (convex_color[j].x - convex_color[i].x) * (p.y - convex_color[i].y) / (convex_color[j].y - convex_color[i].y) + convex_color[i].x;

            if (intersect > p.x) {
                ret++;
            }
        }
    }
    // 홀수면 점이 내부(true) // 접하는건 다른함수에서 예외처리 하겠음;
    return ((ret % 2) != 0);
}

bool on_line(Line &l1, Line &l2) {
    int A = ccw(l1.p1, l1.p2, l2.p1);
    int B = ccw(l1.p1, l1.p2, l2.p2);
    int C = ccw(l2.p2, l2.p1, l1.p1);
    int D = ccw(l2.p2, l2.p1, l1.p2);

    if (A * B == 0 && C * D == 0) {  // 일직선
        if (!(l1.p1 <= l1.p2)) l1.swap();
        if (!(l2.p1 <= l2.p2)) l2.swap();

        // 예외 더있음
        if (l1.p1 <= l2.p2 && l2.p1 <= l1.p2) {
            return true;
        } else {
			return false;                       
        }
        //
    } else if (A * B <= 0 && C * D <= 0) {
		return true;
	} else {
        return false;
    }
}

bool point_line(Polygon &convex_color, Point p) {
    double x = p.x;
    double y = p.y;
    double minx = std::min(convex_color[0].x, convex_color[1].x);
    double maxx = std::max(convex_color[0].x, convex_color[1].x);

    double miny = std::min(convex_color[0].y, convex_color[1].y);
    double maxy = std::max(convex_color[0].y, convex_color[1].y);

    if (minx <= x && x <= maxx && miny <= y && y <= maxy) {
        double a, b, c;
        Point p1 = convex_color[0];
        Point p2 = convex_color[1];
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = p1.x * (p2.y - p1.y) + p1.y * (p1.x - p2.x);
    
        if(a*x + b*y == c) return false;
    }
    return true;
}

bool solved(Polygon &convex_white, Polygon &convex_black) {
    // 점 하나인경우 체크 추가

    if (convex_white.size() == 1) {
        if (convex_black.size() == 2) {
            if(point_line(convex_black, convex_white[0])) {
                return true;
            }

            return false;
        }
    }

    if (convex_black.size() == 1) {

        if (convex_white.size() == 2) {
            if(point_line(convex_white, convex_black[0])) {
                return true;
            }

            return false;
        }
    }
    for (int i = 0; i < convex_white.size(); ++i) {
        int ni = (i + 1) % convex_white.size();

        Line l1(convex_white[i], convex_white[ni]);

        for (int j = 0; j < convex_black.size(); ++j) {
            int nj = (j + 1) % convex_black.size();

            Line l2(convex_black[j], convex_black[nj]);

            if (on_line(l1, l2)) {
                return false;
            }
        }
    }

    for (auto i = convex_white.begin(); i < convex_white.end(); ++i) {
        if (in_polygon(convex_black, *i)) {
            return false;
        }
    }
    for (auto i = convex_black.begin(); i < convex_black.end(); ++i) {
        if (in_polygon(convex_white, *i)) {
            return false;
        }
    }

    return true;
}

// main
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;

    while (tc--) {
        int n, m;
        std::cin >> n >> m;

        Polygon black;
        Polygon white;

        input(black, white, n, m);

        sortALL(black, white);

        Polygon convex_black = convex_hull(black);
        Polygon convex_white = convex_hull(white);

        if (solved(convex_white, convex_black)) {
            std::cout << "YES\n";
        }

        else {
            std::cout << "NO\n";
        }

        black = Polygon();
        white = Polygon();
    }

    return 0;
}