#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct point {
	double x, y;
	
	point() : x(0), y(0) {}
	point(double _x, double _y) : x(_x), y(_y) {}

	point(const point &p) {
		this->x = p.x;
		this->y = p.y;
	}
};

struct Vpair {
	int cur;
	int next;
	double cost;

	Vpair(int _cur, int _next, double _cost) : cur(_cur), next(_next), cost(_cost) {}

	Vpair(const Vpair &pair) {
		this->cur = pair.cur;
		this->next = pair.next;
		this->cost = pair.cost;
	}
};

bool cmp(const Vpair &A, const Vpair &B) {
	return A.cost < B.cost;
}

int get_parent(std::vector<int> &parent, int x) {
	if(parent[x]==x) return x;
	return parent[x] = get_parent(parent, parent[x]);
}

void union_parent(std::vector<int> &parent, int x, int y) {
	x=get_parent(parent,x);
	y=get_parent(parent,y);

	if(x<y) parent[y] = x;
	else if(x>y) parent[x] = y;
}

bool same_parent(std::vector<int> &parent, int x, int y) {
	x=get_parent(parent,x);
	y=get_parent(parent,y);

	if(x==y) return true;
	return false;
}

int main () {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	int n;
	std::cin >> n;

	std::vector<point> stars;

	for(int i=0;i<n;++i) {
		point p;
		std::cin >> p.x >> p.y;
		stars.push_back(point(p));
	}

	std::vector<Vpair> edge;
	std::vector<int> parent(n);
	for(int i=0;i<n;++i) {
		parent[i]=i;
	}

	for(int i=0;i<n;++i) {
		for(int j=i+1;j<n;++j) {
			double co = sqrt(pow(stars[i].x-stars[j].x,2)+pow(stars[i].y-stars[j].y,2));
			edge.push_back(Vpair(i,j,co));
		}
	}
	std::sort(edge.begin(),edge.end(),cmp);

	double ans(0);

	for(int i=0;i<edge.size();++i) {
		if(same_parent(parent,edge[i].cur,edge[i].next) == false) {
			union_parent(parent,edge[i].cur,edge[i].next);
			ans+=edge[i].cost;
		}
	}

	std::cout.precision(2);
	std::cout << std::fixed;

	std::cout << ans << '\n';

	return 0;
}