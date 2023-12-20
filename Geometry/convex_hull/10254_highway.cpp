#include <bits/stdc++.h>

typedef long long lint;

struct Point {
    lint x, y;

    Point() : x(0), y(0) {}

    Point(lint _x, lint _y) : x(_x), y(_y) {}

    Point(const Point &p) {
        x = p.x;
        y = p.y;
    }

    lint dist(const Point &p) {
        return (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y);
    }

    Point operator-(const Point &p) const {
        return Point(x-p.x,y-p.y);
    }
};

std::istream &operator>>(std::istream &in, Point &p) {
    in >> p.x >> p.y;

    return in;
}

lint cross_product(const Point &O, const Point &A, const Point &B) { return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x); }

std::vector<Point> convex_hull(std::vector<Point> &p_set) {
    std::vector<Point> ret;

    ret.push_back(p_set[0]);
    ret.push_back(p_set[1]);

    Point first, second;

    for (int i = 2; i < p_set.size(); ++i) {
        while (ret.size() >= 2) {
            first = ret[ret.size() - 2];
            second = ret[ret.size() - 1];

            lint ccw = cross_product(first, second, p_set[i]);

            if (ccw > 0) break;

            ret.pop_back();
        }

        ret.push_back(p_set[i]);
    }

    return ret;
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    
    while(tc--) {
        int n;
        std::cin >> n;

        std::vector<Point> p_set;


        for (int i = 0; i < n; ++i) {
            Point p;

            std::cin >> p;
            p_set.push_back(p);
        }

        std::sort(p_set.begin(), p_set.end(), [](Point &A, Point &B) {
            if (A.y == B.y) return A.x < B.x;

            return A.y < B.y;
        });

        std::sort(p_set.begin() + 1, p_set.end(), [&p_set](Point &A, Point &B) {
            lint ccw = cross_product(p_set[0], A, B);
            if (ccw == 0) {
                if (A.y == B.y) return A.x < B.x;
                return A.y < B.y;
            }

            return ccw > 0;
        });

        std::vector<Point> valence(convex_hull(p_set));

        lint max_dist(0);
        Point ans1, ans2;

        int j = 1;
        for (int i = 0; i < valence.size(); ++i) {
            int ni = (i + 1) % valence.size();

            while (true) {
                int nj = (j + 1) % valence.size();

                Point v1 = valence[ni] - valence[i];
                Point v2 = valence[nj] - valence[j];

                lint ccw = cross_product(Point(), v1, v2);

                if(ccw > 0) {
                    j = nj;
                    continue;
                }

                break;
            }
            
            lint dist = valence[i].dist(valence[j]);
            
            if(dist > max_dist) {
                max_dist = dist;
                ans1 = valence[i];
                ans2 = valence[j];
            }
        }

        std::cout << ans1.x << ' ' << ans1.y << ' ' << ans2.x << ' ' << ans2.y << '\n';

    }
    return 0;
}