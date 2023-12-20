#include <iostream>
#include <vector>
#include <algorithm>
// 1. input
// 2. 섬 구분
// 3. 섬 사이의 거리 계산해서 edge pair 생성
// 4. kruskal 
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};

struct pair {
	int cur;
	int next;
	int cost;

	pair(int _cur, int _next, int _cost) : cur(_cur), next(_next), cost(_cost) {}
};

void dfs(int row, int col, std::vector<std::vector<int>> &map, std::vector<std::vector<bool>> &visited, const int N, const int M, int idx) {
	map[row][col]=idx;
	visited[row][col]=true;

	for(int i=0;i<4;++i) {
		int nrow = row+dx[i];
		int ncol = col+dy[i];

		if(0<=nrow&&nrow<N&&0<=ncol&&ncol<M) {
			if(map[nrow][ncol]==1&&visited[nrow][ncol]==false) {
				dfs(nrow,ncol,map,visited,N,M,idx);
			}
		} 
	}
}

void go_lower(int cost, int row, int col, const std::vector<std::vector<int>> &map, const int N, const int M, int idx, std::vector<pair> &edge) {
	int nrow = row-1;
	int ncol = col;
	if(nrow<0) return;
	if(map[nrow][ncol]==idx) return;

	if(map[nrow][ncol]!=idx&&map[nrow][ncol]!=0) {
		if(cost<2) return;
		edge.push_back(pair(idx,map[nrow][ncol],cost));
	}

	else
		go_lower(cost+1,nrow,ncol,map,N,M,idx,edge);
}

void go_upper(int cost, int row, int col, const std::vector<std::vector<int>> &map, const int N, const int M, int idx, std::vector<pair> &edge) {
	int nrow = row+1;
	int ncol = col;
	if(nrow>=N) return;
	if(map[nrow][ncol]==idx) return;

	if(map[nrow][ncol]!=idx&&map[nrow][ncol]!=0) {
		if(cost<2) return;
		edge.push_back(pair(idx,map[nrow][ncol],cost));
	}

	else
		go_upper(cost+1,nrow,ncol,map,N,M,idx,edge);
}

void go_right(int cost, int row, int col, const std::vector<std::vector<int>> &map, const int N, const int M, int idx, std::vector<pair> &edge) {
	int nrow = row;
	int ncol = col+1;
	if(ncol>=M) return;
	if(map[nrow][ncol]==idx) return;

	if(map[nrow][ncol]!=idx&&map[nrow][ncol]!=0) {
		if(cost<2) return;
		edge.push_back(pair(idx,map[nrow][ncol],cost));
	}

	else
		go_right(cost+1,nrow,ncol,map,N,M,idx,edge);
}

void go_left(int cost, int row, int col, const std::vector<std::vector<int>> &map, const int N, const int M, int idx, std::vector<pair> &edge) {
	int nrow = row;
	int ncol = col-1;
	if(ncol<0) return;
	if(map[nrow][ncol]==idx) return;

	if(map[nrow][ncol]!=idx&&map[nrow][ncol]!=0) {
		if(cost<2) return;
		edge.push_back(pair(idx,map[nrow][ncol],cost));
	}

	else
		go_left(cost+1,nrow,ncol,map,N,M,idx,edge);
}

bool cmp(const pair &A, const pair &B) {
	return A.cost < B. cost;
}

int get_parent(std::vector<int> &parent, int x) {
	if(x==parent[x]) return x;
	return parent[x] = get_parent(parent,parent[x]);
}

void union_parent(std::vector<int> &parent, int x, int y) {
	x=get_parent(parent,x);
	y=get_parent(parent,y);

	if(x<y) parent[y] = x;
	else if(x>y) parent[x] = y;
}

bool same_parent(std::vector<int> &parent, int x, int y) {
	if(get_parent(parent,x)==get_parent(parent,y)) 
		return true;
	
	return false;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	int N, M;
	std::cin >> N >> M;
	std::vector<std::vector<int>> map(N,std::vector<int>(M,0));
	std::vector<std::vector<bool>> visited(N,std::vector<bool>(M,false));
	std::vector<pair> edge;

	for(int i=0;i<N;++i) {
		for(int j=0;j<M;++j) {
			std::cin >> map[i][j];
		}
	}
	int idx(2); // 2번 섬부터 존재

	for(int i=0;i<N;++i) {
		for(int j=0;j<M;++j) {
			if(map[i][j]==1&&visited[i][j]==false) {
				dfs(i,j,map,visited,N,M,idx);
				idx++;
			}
		}
	} // 섬 구분 끝

	std::vector<int> parent(idx); // 2번 섬 ~ idx-1 번 섬 이용
	for(int i=0;i<idx;++i) {
		parent[i]=i;
	}

	for(int i=0;i<N;++i) {
		for(int j=0;j<M;++j) {
			if(map[i][j]!=0) {
				go_left(0,i,j,map,N,M,map[i][j],edge);
				go_right(0,i,j,map,N,M,map[i][j],edge);
				go_upper(0,i,j,map,N,M,map[i][j],edge);
				go_lower(0,i,j,map,N,M,map[i][j],edge);
			}
		}
	}

	std::sort(edge.begin(),edge.end(),cmp);
	
	int ans(0);
	int cnt(0);
	for(int i=0;i<edge.size();++i) {
		if(same_parent(parent,edge[i].cur,edge[i].next) == false) {
			union_parent(parent,edge[i].cur,edge[i].next);
			cnt++;
			ans+=edge[i].cost;
		}
	}
	if(cnt != idx-3) {
		std::cout << "-1\n";
		return 0;
	}
	std::cout << ans << '\n';

	return 0;
}