#include <iostream>
#include <vector>

const int INF = 10000000;

struct pair{
	int cur;
	int next;
	int cost;

	pair(int _cur, int _next, int _cost) : cur(_cur), next(_next), cost(_cost) {}

	pair(const pair &p) {
		this->cur=p.cur;
		this->next=p.next;
		this->cost=p.cost;
	}
};

void bellman_ford(std::vector<int> &dist, std::vector<pair> &edge, const int V, const int E) {
	
	for(int i=1;i<=V;++i) {
		for(int j=0;j<E;++j) {
			if(dist[edge[j].next]>dist[edge[j].cur]+edge[j].cost) {
				dist[edge[j].next]=dist[edge[j].cur]+edge[j].cost;
			}
		}
	}
}

bool check_cycle(std::vector<int> &dist, std::vector<pair> &edge, const int V, const int E) {
	for(int j=0;j<E;++j) {
		if(dist[edge[j].next]>dist[edge[j].cur]+edge[j].cost) {
			return false;	
		}
	}
	return true;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	int test_case;
	std::cin >> test_case;
	for(int t=0;t<test_case;++t) {
		int V, E, W;
		std::cin >> V >> E >> W;
		std::vector<int> dist(V+1,0);
		std::vector<pair> edge;

		for(int i=0;i<E;++i) {
			int x,y,z;
			std::cin >> x >> y >> z;
			edge.push_back(pair(x,y,z));
			edge.push_back(pair(y,x,z));
		}
		for(int i=0;i<W;++i) {
			int x,y,z;
			std::cin >> x >> y >> z;
			edge.push_back(pair(x,y,-z));
		}

		bellman_ford(dist,edge,V,2*E+W);

		if(!check_cycle(dist,edge,V,2*E+W)) {
			std::cout << "YES\n";
		}
		else {
			std::cout << "NO\n";
		}
	}
	return 0;
}

// https://www.acmicpc.net/board/view/72995