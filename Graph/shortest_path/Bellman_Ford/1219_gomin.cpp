#include <iostream>
#include <vector>
#include <queue>

typedef long long lint;
const lint INF = 1000000000;

struct pair {
	lint cur;
	lint next;
	lint cost;

	pair(lint _cur, lint _next, lint _cost) : cur(_cur), next(_next), cost(_cost) {}

	pair(const pair &p) {
		this->cur = p.cur;
		this->next = p.next;
		this->cost = p.cost;
	}
};

void Bellman_ford(const std::vector<pair> &edge, std::vector<lint> &dist, const lint N, const lint M, const lint start) {
	dist[start]=0;
	for(int i=0;i<N-1;++i) {
		for(int j=0;j<M;++j) {
			if(dist[edge[j].cur]==INF) continue;

			if(dist[edge[j].next]>dist[edge[j].cur]+edge[j].cost) {
				dist[edge[j].next] = dist[edge[j].cur]+edge[j].cost;
			}
		}
	}
}

bool in_cycle(const std::vector<pair> &edge, std::vector<lint> &dist, const lint N, const lint M, const int start, const int end) {
	
	std::vector<bool> visited(N,false);
	visited[start]=true;

	std::queue<int> Q;
	Q.push(start);

	while(!Q.empty()) {
		int cur = Q.front();
		Q.pop();
		if(cur==end) {
			return true;
		}

		for(auto i = edge.begin();i<edge.end();++i) {
			if(cur==i->cur) {
				if(!visited[i->next]) {
					visited[i->next] = true;
					Q.push(i->next);
				}
			}
		}
	}

	return false;
}

bool find_cycle(const std::vector<pair> &edge, std::vector<lint> &dist, const lint N, const lint M, const lint end) {

	for(int j=0;j<M;++j) {
		if(dist[edge[j].cur]==INF) continue;

		if(dist[edge[j].next]>dist[edge[j].cur]+edge[j].cost) { 
			if(in_cycle(edge,dist,N,M,edge[j].next,end)) {
				return true;
			}
		}
	}
	return false;
}



int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	int N, start, end, M;
	std::cin >> N >> start >> end >> M;

	std::vector<pair> edge;
	std::vector<lint> dist(N,INF);
	std::vector<lint> city(N);

	for(int i=0;i<M;++i) {
		lint x,y,z;
		std::cin >> x >> y >> z;
		edge.push_back(pair(x,y,z));
	}

	for(int i=0;i<N;++i) {
		std::cin >> city[i];
	}

	for(int i=0;i<edge.size();++i) {
		edge[i].cost = edge[i].cost-city[edge[i].next];
	}


	Bellman_ford(edge,dist,N,M,start);
	
	if(dist[end]==INF) {
		std::cout << "gg\n";
		return 0;
	}

	if(find_cycle(edge,dist,N,M,end)) {
		std::cout << "Gee\n";
		return 0;
	}

	std::cout << -dist[end]+city[start] << '\n';
	

	return 0;
}