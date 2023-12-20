#include <iostream>
#include <vector>
#include <queue>

struct point {
	int x,y;
	
	point(int _x, int _y) : x(_x), y(_y) {}

	point(const point &p) {
		this->x = p.x;
		this->y = p.y;
	}

	point& operator=(const point &A) {
		this->x=A.x;
		this->y=A.y;

		return *this;
	}
};

struct Qpair {
	int x;
	int y;
	int cost;

	Qpair(int _x, int _y, int _cost) : x(_x), y(_y), cost(_cost) {}

	Qpair(const Qpair &Q) {
		this->x = Q.x;
		this->y = Q.y;
		this->cost = Q.cost;
	}
};

struct cmp {
	bool operator()(const Qpair &A, const Qpair &B) {
		return A.cost > B.cost;
	}
};

void dijkstra(std::vector<std::vector<char>> &map, const int &N, std::vector<std::vector<bool>> &visited) {
	int dx[4] = {1,-1,0,0};
	int dy[4] = {0,0,1,-1};

	std::priority_queue<Qpair,std::vector<Qpair>,cmp> pQ;
	pQ.push(Qpair(1,1,0));
	visited[1][1]=true;

	while(!pQ.empty()) {
		Qpair now(pQ.top());
		pQ.pop();

		if(now.x==N&&now.y==N) {
			std::cout << now.cost << '\n';
			return;
		}

		for(int i=0;i<4;++i) {
			if(1<=now.x+dx[i]&&now.x+dx[i]<=N&&1<=now.y+dy[i]&&now.y+dy[i]<=N&&visited[now.x+dx[i]][now.y+dy[i]]==false) {
				visited[now.x+dx[i]][now.y+dy[i]]=true;
				if(map[now.x+dx[i]][now.y+dy[i]]=='1') {
					pQ.push(Qpair(now.x+dx[i],now.y+dy[i],now.cost));
				}
				else if(map[now.x+dx[i]][now.y+dy[i]]=='0') {
					pQ.push(Qpair(now.x+dx[i],now.y+dy[i],now.cost+1));
				}
			}
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	int N;
	std::cin >> N;

	std::vector<std::vector<char>> map(N+1,std::vector<char>(N+1,0));
	std::vector<std::vector<bool>> visited(N+1,std::vector<bool>(N+1,false));
	for(int i=1;i<=N;++i) {
		for(int j=1;j<=N;++j) {
			std::cin >> map[i][j];
		}
	}
	dijkstra(map,N,visited);

	return 0;
}