#include <iostream>

struct point {
	double x;
	double y;

	point() : x(0.0), y(0.0) {}
	point(double _x, double _y) : x(_x), y(_y) {}

	bool operator<=(const point& in) const;
	bool operator==(const point& in) const;
};

int ccw(point base, point A, point B) {
	point v1, v2;
	v1.x=A.x-base.x;
	v1.y=A.y-base.y;
	v2.x=B.x-base.x;
	v2.y=B.y-base.y;

	double cross_v = v1.x*v2.y-v1.y*v2.x;
	// 외적이 양수면 base A B ccw
	if(cross_v>0) return 1;
	else if(cross_v<0) return -1;
	
	return 0;  
}

void swap(point& point1, point& point2) {
	point tmp;
	tmp.x=point1.x;
	tmp.y=point1.y;
	point1.x=point2.x;
	point1.y=point2.y;
	point2.x=tmp.x;
	point2.y=tmp.y;
}

point find_crosspoint(const point* points);

void cross(point* &points) {
	int A = ccw(points[0],points[1],points[2]);
	int B = ccw(points[0],points[1],points[3]);
	int C = ccw(points[3],points[2],points[0]);
	int D = ccw(points[3],points[2],points[1]);

	if(A*B==0&&C*D==0) { // 일직선 , ㄴ ㄱ 모양
		if(!(points[0]<=points[1])) swap(points[0],points[1]);
		if(!(points[2]<=points[3])) swap(points[2],points[3]);
		
		// 예외 더있음
		if(points[0]<=points[3]&&points[2]<=points[1]) {
			std::cout << "1\n";
			point ans_point = find_crosspoint(points);
			std::cout << std::fixed;
			std::cout.precision(9);
			std::cout << ans_point.x << ' ' << ans_point.y << '\n';
		}
		else {
			std::cout << "0\n";
		}
		//
	}
	else if(A*B<=0&&C*D<=0) { //
		std::cout << "1\n";
		point ans_point = find_crosspoint(points);
		std::cout << std::fixed;
		std::cout.precision(9);
		std::cout << ans_point.x << ' ' << ans_point.y << '\n';
	}
	else {
		std::cout << "0\n";
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	point* points = new point[4];

	for(int i=0;i<4;++i) {
		std::cin >> points[i].x >> points[i].y;
	}

	cross(points);

	delete[] points;
	return 0;
}


point find_crosspoint(const point* points) {
	double px = (points[0].x*points[1].y-points[0].y*points[1].x)*(points[2].x-points[3].x) - (points[0].x-points[1].x)*(points[2].x*points[3].y-points[2].y*points[3].x);
	double py = (points[0].x*points[1].y-points[0].y*points[1].x)*(points[2].y-points[3].y) - (points[0].y-points[1].y)*(points[2].x*points[3].y-points[2].y*points[3].x);
	double p = (points[0].x-points[1].x)*(points[2].y-points[3].y) - (points[0].y-points[1].y)*(points[2].x-points[3].x);

	if(p==0) { // 일직선
		if(points[1]==points[2]) return point(points[1].x, points[1].y);
		if(points[3]==points[0]) return point(points[0].x, points[0].y);
	}

	return point(px/p,py/p);
}

bool point::operator==(const point& in) const {
	if(this->x==in.x&&this->y==in.y)
		return true;
	return false;
}

bool point::operator<=(const point& in) const {
	if(this->x==in.x) {
		return this->y <= in.y;
	}
	return this->x <= in.x;
}