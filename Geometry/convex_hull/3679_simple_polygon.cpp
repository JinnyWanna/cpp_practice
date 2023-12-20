#include <bits/stdc++.h>

typedef long long lint;
struct Point {
	lint x, y, idx;

	Point() : x(0), y(0), idx(0) {}

	Point(lint _x, lint _y, lint _idx) : x(_x), y(_y), idx(_idx) {}

	Point(const Point &p) {
		x = p.x;
		y = p.y;
		idx = p.idx;
	}
};


std::istream& operator>>(std::istream& in, Point &p) {
	in >> p.x >> p.y;
	
	return in;
}

lint CCW(const Point &O, const Point &A, const Point &B){
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

lint dist(const Point A, const Point B) {
	return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y); 
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	int tc;
	std::cin >> tc;

	while(tc--) {
		int n;
		std::cin >> n;

		std::vector<Point> p_set;

		for(lint i=0; i<n; ++i) {
			Point p;
			std::cin >> p;
			p.idx = i;

			p_set.push_back(p);
		}

		std::sort(p_set.begin(), p_set.end(), [](const Point &A, const Point &B) {
			if(A.y == B.y) return A.x < B.x;
			return A.y < B.y;
		});

		std::sort(p_set.begin() + 1, p_set.end(), [&p_set](const Point &A, const Point &B) {
			lint ccw = CCW(p_set[0], A, B);

			if(ccw == 0) {
				return dist(p_set[0], A) < dist(p_set[0], B);
			}

			return ccw > 0;
		});

		int st = n - 1;

		for(int i = n-1; i >= 0; --i) {
			if(CCW(p_set[0], p_set[i], p_set[i-1]) == 0) {
				st = i - 1;
			}
			else break;
		}
		
		std::sort(p_set.begin()+st, p_set.end(),[&](const Point &A, const Point &B) {
            return dist(p_set[0], A) > dist(p_set[0], B);
        });

		for(int i=0; i<n; ++i) {
			std::cout << p_set[i].idx << ' ';
		}

		std::cout << '\n';
	}

	return 0;
}