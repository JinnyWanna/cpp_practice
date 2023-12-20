#include <iostream>
#include <vector>
#include <queue>

const int up = 1;
const int down = 2;
const int left = 3;
const int right = 4;

const int INF = 10000000;

struct point {
	int x,y;
	
	point() : x(), y() {}
	point(int _x, int _y) : x(_x), y(_y) {}

	point(const point &p) {
		this->x = p.x;
		this->y = p.y;
	}
};

struct Qpair{
	point cur_point;
	int value;
	int before_move;
	Qpair(point _cur_point, int _value) : cur_point(_cur_point), value(_value), before_move(0) {}

	Qpair(point _cur_point, int _value, int _before_move) : cur_point(_cur_point), value(_value), before_move(_before_move) {}

	Qpair(const Qpair &pair) {
		this->cur_point.x = pair.cur_point.x;
		this->cur_point.y = pair.cur_point.y;
		this->value = pair.value;
		this->before_move = pair.before_move;
	}
};

struct cmp {
	bool operator()(Qpair A, Qpair B) {
		return A.value > B.value;
	}
};

void dijkstra(std::vector<std::vector<int>> &dist, std::vector<std::vector<bool>> &visited, const point start, const int H, const int W) {
	std::priority_queue<Qpair, std::vector<Qpair>, cmp> pQ; 
	pQ.push(Qpair(start,0));
	dist[start.x][start.y] = 0;

	while(!pQ.empty()) {
		Qpair now(pQ.top());
		pQ.pop();

		if(0<=now.cur_point.x-1&&!visited[now.cur_point.x-1][now.cur_point.y]) {
			if(now.before_move==left) { // 이동방향 그대로 경우 가중치 0
				if(dist[now.cur_point.x-1][now.cur_point.y]>=now.value) { 
					dist[now.cur_point.x-1][now.cur_point.y] = now.value;
					pQ.push(Qpair(point(now.cur_point.x-1,now.cur_point.y),now.value,left));
				}
			}
			else { // 이동 가중치 1
				if(dist[now.cur_point.x-1][now.cur_point.y]>=now.value+1) { 
				
					dist[now.cur_point.x-1][now.cur_point.y] = now.value+1;
					pQ.push(Qpair(point(now.cur_point.x-1,now.cur_point.y),now.value+1,left));
				}
			}
		}

		if(0<=now.cur_point.y-1&&!visited[now.cur_point.x][now.cur_point.y-1]) {
			if(now.before_move==down) { // 이동방향 그대로 경우 가중치 0
				if(dist[now.cur_point.x][now.cur_point.y-1]>=now.value) {
					dist[now.cur_point.x][now.cur_point.y-1] = now.value;
					pQ.push(Qpair(point(now.cur_point.x,now.cur_point.y-1),now.value,down));
				}
			}
			else { // 이동 가중치 1
				if(dist[now.cur_point.x][now.cur_point.y-1]>=now.value+1) {
					dist[now.cur_point.x][now.cur_point.y-1] = now.value+1;
					pQ.push(Qpair(point(now.cur_point.x,now.cur_point.y-1),now.value+1,down));
				}
			}
		}

		if(now.cur_point.x+1<H&&!visited[now.cur_point.x+1][now.cur_point.y]) {
			if(now.before_move==right) { // 이동방향 그대로 경우 가중치 0
				if(dist[now.cur_point.x+1][now.cur_point.y]>=now.value) {
					dist[now.cur_point.x+1][now.cur_point.y] = now.value;
					pQ.push(Qpair(point(now.cur_point.x+1,now.cur_point.y),now.value,right));
				}
			}
			else { // 이동 가중치 1
				if(dist[now.cur_point.x+1][now.cur_point.y]>=now.value+1) {
					dist[now.cur_point.x+1][now.cur_point.y] = now.value+1;
					pQ.push(Qpair(point(now.cur_point.x+1,now.cur_point.y),now.value+1,right));
				}
			}
		}
		if(now.cur_point.y+1<W&&!visited[now.cur_point.x][now.cur_point.y+1]) {
			if(now.before_move==up) { // 이동방향 그대로 경우 가중치 0
				if(dist[now.cur_point.x][now.cur_point.y+1]>=now.value) {
					dist[now.cur_point.x][now.cur_point.y+1] = now.value;
					pQ.push(Qpair(point(now.cur_point.x,now.cur_point.y+1),now.value,up));
				}
			}
			else { // 이동 가중치 1
				if(dist[now.cur_point.x][now.cur_point.y+1]>=now.value+1) {
					dist[now.cur_point.x][now.cur_point.y+1] = now.value+1;
					pQ.push(Qpair(point(now.cur_point.x,now.cur_point.y+1),now.value+1,up));
				}
			}
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);
	
	int W, H;
	std::cin >> W >> H;

	std::vector<std::vector<bool>> visited(H,std::vector<bool>(W,false));
	std::vector<std::vector<int>> dist(H,std::vector<int>(W,INF));

	point start, end;
	bool input = false;
	
	for(int i=0;i<H;++i) {
		for(int j=0;j<W;++j) {
			char wall;
			std::cin >> wall;
			if(wall=='*') {
				visited[i][j]=true;
			}
			else if(wall=='C'&&!input) {
				start = point(i,j);
				input = true;
			}
			else if(wall=='C'&&input) {
				end = point(i,j);
			}
		}
	} 

	dijkstra(dist, visited, start, H, W);
	std::cout << dist[end.x][end.y]-1 <<'\n';
	return 0;
}