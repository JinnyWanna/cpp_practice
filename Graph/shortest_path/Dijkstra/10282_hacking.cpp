#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

struct Vpair {
	int next;
	int cost;
};

struct Qpair {
	int cur_node;
	int cost;
};

struct cmp {
	bool operator()(Qpair A, Qpair B) {
		if(A.cost==B.cost) {
			return A.cur_node > B.cur_node;
		}
		return A.cost > B.cost;
	}
};

void dijkstra(std::vector<std::vector<Vpair>> &link, std::vector<bool> &visited, std::vector<int> &dist, int start) {
	std::priority_queue<Qpair,std::vector<Qpair>,cmp> pQ;
	
	pQ.push({start,0});
	dist[start]=0;

	while(!pQ.empty()) {
		int cur_node = pQ.top().cur_node;
		int cost = pQ.top().cost;
		pQ.pop();

		if(visited[cur_node] == true) continue;

		visited[cur_node] = true;
		
		for(int i=0;i<link[cur_node].size();++i) {
			int ncost = link[cur_node][i].cost;
			int next = link[cur_node][i].next;

			if(dist[next] > ncost + cost) {
				dist[next] = ncost + cost;
				pQ.push({next,dist[next]});
			}
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	const int INF = 100000000;

	int test_case;
	std::cin >> test_case;

	for(int t=0;t<test_case;++t) {
		int n, d, c; // n : 노드 수 , d : 간선 수 , c : 첫 노드
		std::cin >> n >> d >> c;
		
		std::vector<std::vector<Vpair>> link(n+1,std::vector<Vpair>());
		std::vector<int> dist(n+1,INF);
		std::vector<bool> visited(n+1,false);

		for(int i=0;i<d;++i) {
			int a, b, s; // b -> a cost s
			std::cin >> a >> b >> s;
			link[b].push_back({a,s});
		}
	
		dijkstra(link, visited, dist, c);

		int ans_infected(0);
		int ans_time(0);

		for(int i=1;i<=n;++i) {
			if(dist[i]==INF) continue;
			ans_infected++;
			ans_time=std::max(ans_time,dist[i]);
		}

		std::cout << ans_infected << ' ' << ans_time <<'\n';
	}

	return 0;
}