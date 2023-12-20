#include <iostream>
#include <vector>

const int INF = 100000000;

const int dx[4] = {1,-1,0,0};
const int dy[4] = {0,0,1,-1};

struct point{
	int x, y;

	point(int x, int y) : x(x), y(y) {}

	point(const point &p) {
		this->x = p.x;
		this->y = p.y;
	}
};

struct teleport {
	point p; // 텔레포트로 이동 위치
	int cost;

	teleport(point _p1, int _cost) : p(_p1), cost(_cost) {}
};

void Bellman_ford(const std::vector<std::vector<int>> &map, std::vector<std::vector<int>> &dist, std::vector<teleport> &tp, const int W, const int H, const int G) {
	dist[0][0]=0;
	for(int i=0;i<W*H-G-1;++i) {
		for(int a=0;a<W;++a) {
			for(int b=0;b<H;++b) {
				if(dist[a][b]==INF) continue;
				if(a==W-1&&b==H-1) continue; 

				if(map[a][b]>=0) {
					int tp_x = tp[map[a][b]].p.x;
					int tp_y = tp[map[a][b]].p.y;
					if(dist[tp_x][tp_y]>dist[a][b]+tp[map[a][b]].cost)
						dist[tp_x][tp_y]=dist[a][b]+tp[map[a][b]].cost;
				}
				else {
					for(int j=0;j<4;++j) {
						int next_x = a+dx[j];
						int next_y = b+dy[j];
						if(next_x>=0&&next_x<W&&next_y>=0&&next_y<H) {
							if(map[next_x][next_y]==-1) continue;
							else
								if(dist[next_x][next_y]>dist[a][b]+1) dist[next_x][next_y]=dist[a][b]+1;
						}
					}
				}
			}
		}
	}
}	

bool find_ans(const std::vector<std::vector<int>> &map, std::vector<std::vector<int>> &dist, std::vector<teleport> &tp, const int W, const int H, const int G) {
	

	for(int a=0;a<W;++a) {
		for(int b=0;b<H;++b) {
			if(a==W-1&&b==H-1) continue; 
			if(dist[a][b]==INF) continue;

			if(map[a][b]>=0) {
				int tp_x = tp[map[a][b]].p.x;
				int tp_y = tp[map[a][b]].p.y;
				if(dist[tp_x][tp_y]>dist[a][b]+tp[map[a][b]].cost) return false;
			}
			else if(map[a][b]==-2){
				for(int j=0;j<4;++j) {
					int next_x = a+dx[j];
					int next_y = b+dy[j];
					if(next_x>=0&&next_x<W&&next_y>=0&&next_y<H) {
						if(map[next_x][next_y]==-1) continue;
						else
							if(dist[next_x][next_y]>dist[a][b]+1) return false;
					}
				}
			}
		}
	}
	
	return true;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	// -2 yard , -1 stone , 0 1 2 3... tp index

	while(true) {
		int W, H; // graveyard

		std::cin >> W >> H;
		if(W==0&&H==0) break;
		
		std::vector<std::vector<int>> map(W,std::vector<int>(H,-2));
		std::vector<std::vector<int>> dist(W,std::vector<int>(H,INF)); 
		int G; // gravestone
		std::cin >> G;
		for(int i=0;i<G;++i) {
			int x,y;
			std::cin >> x >> y;
			map[x][y]=-1;
		}
		int E; // haunted hole
		std::cin >> E;

		std::vector<teleport> tp;
		int index(0);
		for(int i=0;i<E;++i) {
			int x1, y1, x2, y2, T;
			std::cin >> x1 >> y1 >> x2 >> y2 >> T;
			map[x1][y1]=index;
			tp.push_back(teleport(point(x2,y2),T));
			index++;
		}

		Bellman_ford(map,dist,tp,W,H,G);
		int ans = dist[W-1][H-1];

		if(!find_ans(map,dist,tp,W,H,G)) {
			std::cout << "Never\n";
		}

		else if(ans==INF) {
			std::cout << "Impossible\n";
		}

		else {
			std::cout << ans << '\n';
		}
	}
	return 0;
}