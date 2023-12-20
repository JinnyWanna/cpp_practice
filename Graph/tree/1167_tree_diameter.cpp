#include <iostream>
#include <vector>
#include <algorithm>

struct Vpair {
	int next;
	int cost;
};

int ans[100001]; // ans[현노드]=ans[전노드]+현노드 거리 // ans 0만 탐색
bool visited[100001];
void dfs(const std::vector<std::vector<Vpair>> &link, int node) {
	visited[node]=true;
	for(int i=0;i<link[node].size();++i) {
		if(!visited[link[node][i].next]) {
			visited[link[node][i].next]=true;
			ans[link[node][i].next]=ans[node]+link[node][i].cost;
			dfs(link,link[node][i].next);
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	int vertex;
	std::cin >> vertex;

	std::vector<std::vector<Vpair>> link(vertex+1);

	for(int i=0;i<vertex;++i) {
		int x;
		std::cin >> x;
		while(true) {
			int y;
			std::cin >> y;
			if(y==-1) break;
			int z;
			std::cin >> z;
			link[x].push_back({y,z});
		}
	}

	dfs(link,1);

	int max=0;
	int idx;
	for(int i=1;i<=vertex;++i) {
		if(max<ans[i]) {
			max=ans[i];
			idx=i;
		}
	}
	
	std::fill(ans,ans+vertex+1,0);
	std::fill(visited,visited+vertex+1,0);

	dfs(link, idx);

	for(int i=1;i<=vertex;++i) {
		if(max<ans[i]) {
			max=ans[i];
		}
	}

	std::cout << max << '\n';

	return 0;
}