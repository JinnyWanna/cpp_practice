#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
// MST
typedef long long lint;

struct point {
	lint x,y,z;
	int index;
	point() : x(0), y(0), z(0), index(0) {}
	point(lint _x, lint _y, lint _z, int index) : x(_x), y(_y), z(_z), index(index) {}

	point(const point &p) {
		this->x=p.x;
		this->y=p.y;
		this->z=p.z;
		this->index = p.index;
	}
};

struct pair {
	int cur;
	int next;
	lint cost;

	pair(int _cur, int _next, lint _cost) : cur(_cur), next(_next), cost(_cost) {}
};

bool cmp(const pair &A, const pair &B) {
	return A.cost < B.cost;
}

int get_parent(std::vector<int> &parent, int x) {
	if(x==parent[x]) return x;
	return parent[x] = get_parent(parent,parent[x]);
}

void union_parent(std::vector<int> &parent, int x, int y) {
	x=get_parent(parent,x);
	y=get_parent(parent,y);

	if(x<y) parent[y] = x;
	else if(x>y) parent[x] = y;
}

bool same_parent(std::vector<int> &parent, int x, int y) {
	if(get_parent(parent,x)==get_parent(parent,y)) 
		return true;
	
	return false;
}

bool cmpx(const point &p1, const point &p2) {
	return p1.x < p2.x;
}

bool cmpy(const point &p1, const point &p2) {
	return p1.y < p2.y;
}

bool cmpz(const point &p1, const point &p2) {
	return p1.z < p2.z;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	
	std::vector<pair> edge;
	std::vector<int> parent(N);
	for(int i=0;i<N;++i) {
		parent[i]=i;
	}

	std::vector<point> points;
	int idx = 0;
	for(int i=0;i<N;++i) {
		point p;
		std::cin >> p.x >> p.y >> p.z;
		p.index=idx++;
		points.push_back(point(p));
	}

	std::sort(points.begin(),points.end(),cmpx);
	for(int i=0;i<N-1;++i) {
		lint co = points[i+1].x-points[i].x;
		edge.push_back(pair(points[i].index,points[i+1].index,co));
	}

	std::sort(points.begin(),points.end(),cmpy);
	for(int i=0;i<N-1;++i) {
		lint co = points[i+1].y-points[i].y;
		edge.push_back(pair(points[i].index,points[i+1].index,co));
	}

	std::sort(points.begin(),points.end(),cmpz);
	for(int i=0;i<N-1;++i) {
		lint co = points[i+1].z-points[i].z;
		edge.push_back(pair(points[i].index,points[i+1].index,co));
	}

	int ans(0);
	std::sort(edge.begin(),edge.end(),cmp);
	for(int i=0;i<edge.size();++i) {
		if(same_parent(parent,edge[i].cur,edge[i].next) == false) {
			union_parent(parent,edge[i].cur,edge[i].next);
			ans+=edge[i].cost;
		}
	}

	std::cout << ans << '\n';

	return 0;
}