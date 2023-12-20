#include <iostream>
#include <vector>
#include <cmath>

typedef long long lint;

struct point{
	lint x;
	lint y;
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	int N;
	double area=0.0;
	
	std::cin >> N;
	std::vector<point> points(N);

	for(int i=0;i<N;++i) {
		std::cin >> points[i].x >> points[i].y;
	}
	lint base_x = points[0].x;
	lint base_y = points[0].y;

	for(int i=1;i<N-1;++i) {
		area+=(double)(((base_x-points[i].x)*(base_y-points[i+1].y))-((base_x-points[i+1].x)*(base_y-points[i].y)))/2;
	}
	if(area<0) area=-area;
	
	std::cout << std::fixed;
	std::cout.precision(1);
	std::cout << area;
	
	return 0;
}