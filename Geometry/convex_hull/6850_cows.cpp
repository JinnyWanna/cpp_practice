#include <bits/stdc++.h>

struct Point {
    int x, y;

    Point() : x(0), y(0) {}

    Point(int _x, int _y) : x(_x), y(_y) {}

    Point(const Point &p) {
        x = p.x;
        y = p.y;
    }
};

std::istream &operator>>(std::istream &in, Point &p) {
    in >> p.x >> p.y;

    return in;
}

int cross_product(const Point &O, const Point &A, const Point &B) { return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x); }

std::vector<Point> convex_hull(std::vector<Point> &p_set) {
    std::vector<Point> ret;

    ret.push_back(p_set[0]);
    ret.push_back(p_set[1]);

    Point first, second;

    for (int i = 2; i < p_set.size(); ++i) {
        while(ret.size() >= 2) {
            first = ret[ret.size() - 2];
            second = ret[ret.size() - 1];
            
            int ccw = cross_product(first, second, p_set[i]);

            if(ccw > 0) break;

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
        int ccw = cross_product(p_set[0], A, B);
        if (ccw == 0) {
            if (A.y == B.y) return A.x < B.x;
            return A.y < B.y;
        }

        return ccw > 0;
    });

    std::vector<Point> valence(convex_hull(p_set));

    double area = 0;

    for(int i=1;i<valence.size()-1; ++i) {
        area += (double)cross_product(valence[0], valence[i], valence[i+1]) / 2;
    }

    std::cout << floor(area/50) << '\n';

    return 0;
}