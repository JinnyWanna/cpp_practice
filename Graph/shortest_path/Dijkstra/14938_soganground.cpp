#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct Vpair{
	int next;
	int cost;

	Vpair(int _next, int _cost) : next(_next), cost(_cost) {}
};

struct Qpair{
	int node;
	int cost;
	
	Qpair(int _node, int _cost) : node(_node), cost(_cost) {}
};

struct cmp {
	bool operator()(const Qpair A, const Qpair B) const {
		if(A.cost==B.cost) {
			return A.node > B.node;
		}
		return A.cost > B.cost;
	}
};

void dijkstra(const std::vector<std::vector<Vpair>> &link, std::vector<bool> &visited, std::vector<int> &dist, int startnode) {
	std::priority_queue<Qpair,std::vector<Qpair>,cmp> pQ; 

	pQ.push({startnode,0});
	dist[startnode]=0;

	while(!pQ.empty()) {
		int cur_node = pQ.top().node;
		int cost = pQ.top().cost;
		pQ.pop();

		if(visited[cur_node]==true) continue;

		visited[cur_node]=true;

		for(int i=0;i<link[cur_node].size();++i) {
			int next = link[cur_node][i].next;
			int ncost = link[cur_node][i].cost;

			if(dist[next]>cost+ncost) {
				dist[next] = cost + ncost;
				pQ.push(Qpair(next, dist[next]));
			}
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	const int INF = 100000000;

	int node, m, edge;
	std::cin >> node >> m >> edge;
	std::vector<int> map(node+1);
	std::vector<std::vector<Vpair>> link(node+1,std::vector<Vpair>());

	for(int i=1;i<=node;++i) {
		std::cin >> map[i];
	}

	for(int i=0;i<edge;++i) {
		int a, b, l;
		std::cin >> a >> b >> l;
		link[a].push_back(Vpair(b,l));
		link[b].push_back(Vpair(a,l));
	}
	int ans_max(0);
	for(int i=1;i<=node;++i) { // 착륙지점 i
		std::vector<bool> visited(node+1,false);
		std::vector<int> dist(node+1,INF);
		int sum(0);

		dijkstra(link,visited,dist,i);
		for(int j=1;j<=node;++j) {
			if(dist[j]<=m) {
				sum+=map[j];
			} 
		}

		ans_max=std::max(ans_max,sum);
	}

	std::cout << ans_max << '\n';

	return 0;
}
