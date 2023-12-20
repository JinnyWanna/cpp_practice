#include <iostream>
#include <vector>
#include <algorithm>
// https://www.acmicpc.net/board/view/91251 문제

struct point {
	double x, y;

	point() : x(0), y(0) {}
	point(double _x, double _y) : x(_x), y(_y) {}

	bool operator<=(const point &in) const;
};

struct line {
	point point1;
	point point2;

	line() : point1({0,0}), point2({0,0}) {}
	line(point _point1, point _point2) : point1(_point1), point2(_point2) {}
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

void swap(line &_line) { // 해당 line의 두 점을 change
	point tmp;
	tmp.x=_line.point1.x;
	tmp.y=_line.point1.y;
	_line.point1.x=_line.point2.x;
	_line.point1.y=_line.point2.y;
	_line.point2.x=tmp.x;
	_line.point2.y=tmp.y;
}

bool cross(line line1, line line2) {
	int A = ccw(line1.point1,line1.point2,line2.point1);
	int B = ccw(line1.point1,line1.point2,line2.point2);
	int C = ccw(line2.point2,line2.point1,line1.point1);
	int D = ccw(line2.point2,line2.point1,line1.point2);

	if(A*B==0&&C*D==0) {
		if(!(line1.point1<=line1.point2)) swap(line1);
		if(!(line2.point1<=line2.point2)) swap(line2);

		if(line1.point1<=line2.point2&&line2.point1<=line1.point2) { // 만남
			return true;		
		}
		else { // 안만남
			return false;
		}
	}
	else if(A*B<=0&&C*D<=0) { // 만남
		return true;
	}
	else { // 안만남
		return false;
	}
	return false;
}

int get_parent(std::vector<int> &parent, int x) {
	if(x==parent[x]) return x;
	else {
		return parent[x]=get_parent(parent,parent[x]);
	}
}

void union_parent(std::vector<int> &parent, int x, int y) {
	x=get_parent(parent,x);
	y=get_parent(parent,y);
	if(x<y) parent[y]=x;
	else if(x>y) parent[x]=y;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	int groupnum;
	std::cin >> groupnum;

	std::vector<line> line_v;
	std::vector<int> line_parent(groupnum);

	for(int i=0;i<groupnum;++i) {
		line_parent[i]=i;
	}

	for(int i=0;i<groupnum;++i) {
		double p1x, p1y, p2x, p2y;
		std::cin >> p1x >> p1y >> p2x >> p2y;
		point p1(p1x,p1y);
		point p2(p2x,p2y);
		line_v.push_back(line(p1,p2));
	}

	for(int i=0;i<groupnum-1;++i) {
		for(int j=i+1;j<groupnum;++j) {
			if(cross(line_v[i],line_v[j])) {
				union_parent(line_parent,i,j);
			}
		}
	}

	int group[3001] = {0,};
	int cnt(0);
	int max(0);
    /////////////////
	for(int i=0;i<groupnum;++i) {
		line_parent[i]=get_parent(line_parent,line_parent[i]);
	}
    ///////////////// 이부분 압축 진행 안해주면 문제생길수 있음
    // 현재 부모노드가 맞게 연결됐는지 체크!!
	for(int i=0;i<groupnum;++i) {
		group[line_parent[i]]++;
	}

	for(int i=0;i<groupnum;++i) {
		if(group[i]!=0) {
			cnt++;
			max=std::max(max,group[i]);
		}
	}

	std::cout << cnt << '\n' << max << '\n';

	return 0;
}

bool point::operator<=(const point &in) const {
	if(this->x==in.x) {
		return this->y <= in.y;
	}
	return this->x <= in.x;
}