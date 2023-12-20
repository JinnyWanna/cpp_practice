#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct Vpair {
	int next;
	int cost;
	int time;
	Vpair(int _next, int _cost, int _time) : next(_next), cost(_cost), time(_time) {}
};

struct Qpair {
	int cur_node;
	int cost;
	int time;

	Qpair(int _cur_node, int _cost, int _time) : cur_node(_cur_node), cost(_cost), time(_time) {}

	Qpair(const Qpair &pair) {
		this->cur_node = pair.cur_node;
		this->cost = pair.cost;
		this->time = pair.time;
	}
};

struct cmp{
	bool operator()(const Qpair &A, const Qpair &B) {
		return A.time > B.time;
	};
};

void input(std::vector<std::vector<Vpair>> &link, const int K) {
	for(int i=0;i<K;++i) {
			int x,y,z,m;
			std::cin >> x >> y >> z >> m;
			link[x].push_back(Vpair(y,z,m));
	}
	return;
}

void input(const Qpair &now, std::vector<std::vector<int>> &dist, const std::vector<Vpair> :: const_iterator &i, const int M) {
	for(int j=now.cost+i->cost;j<=M;++j) {
		if(dist[i->next][j]>now.time+i->time) {
			dist[i->next][j]=now.time+i->time;
		}
	}
}

void dijkstra(const std::vector<std::vector<Vpair>> &link, std::vector<std::vector<int>> &dist, const int N, const int M) {
	std::priority_queue<Qpair, std::vector<Qpair>, cmp> pQ;
	pQ.push(Qpair(1,0,0));
	dist[1][0]=0;

	while(!pQ.empty()) {
		Qpair now(pQ.top());
		pQ.pop();
		
		if(now.cur_node==N) {
			std::cout << now.time <<'\n';
			return;
		}
		
		for(auto i=link[now.cur_node].begin();i<link[now.cur_node].end();++i) {

			if(dist[i->next][now.cost+i->cost]>now.time+i->time&&now.cost+i->cost<=M) {
				input(now,dist,i,M);
				pQ.push(Qpair(i->next,now.cost+i->cost,dist[i->next][now.cost+i->cost]));
			}
		}
	}
	std::cout << "Poor KCM\n";
	return;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	const int INF = 10000000;

	int test_case;
	std::cin >> test_case;
	for(int t=0;t<test_case;++t) {
		int N, M, K;
		std::cin >> N >> M >> K;
		std::vector<std::vector<Vpair>> link(N+1,std::vector<Vpair>());
		std::vector<std::vector<int>> dist(N+1,std::vector<int>(M+1,INF));
		
		input(link,K);
		dijkstra(link,dist,N,M);
	}

	return 0;
}