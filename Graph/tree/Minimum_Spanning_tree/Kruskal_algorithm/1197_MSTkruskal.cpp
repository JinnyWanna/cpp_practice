#include <iostream>
#include <vector>
#include <algorithm>

struct pair{
	int cur;
	int next;
	int cost;

	pair() : cur(0), next(0), cost(0) {}

	pair(int _cur, int _next, int _cost) : cur(_cur), next(_next), cost(_cost) {}

	pair(const pair& p) {
		this->cur=p.cur;
		this->next=p.next;
		this->cost=p.cost;
	}
};

bool cmp(const pair &A, const pair &B) {
	return A.cost < B.cost;
}

int get_parent(std::vector<int> &parent, const int x) {
	if(x==parent[x]) return x;

	return parent[x] = get_parent(parent,parent[x]);
}

void union_parent(std::vector<int> &parent, int x, int y) {
	x=parent[x];
	y=parent[y];

	if(x<y)	parent[y]=x;
	else if(x>y) parent[x]=y;
}

bool same_parent(std::vector<int> &parent, const int x, const int y) {
	if(get_parent(parent,x)==get_parent(parent,y)) return true;
	
	return false;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	int V, E;
	std::cin >> V >> E;

	std::vector<pair> edge;
	std::vector<int> parent(V+1);
	for(int i=1;i<=V;++i) {
		parent[i]=i;
	}

	for(int i=0;i<E;++i) {
		pair p;
		std::cin >> p.cur >> p.next >> p.cost;
		edge.push_back(pair(p));
	}

	std::sort(edge.begin(), edge.end(), cmp);

	int ans(0);
	for(int i=0;i<E;++i) {
		if(same_parent(parent,edge[i].cur,edge[i].next) == false) {
			union_parent(parent,edge[i].cur,edge[i].next);
			ans+=edge[i].cost;
		}
	}
	
	std::cout << ans << '\n';

	return 0;
}