#include <iostream>
#include <vector>

void find_sub(int root, const std::vector<std::vector<int>> &link, std::vector<bool> &visited, std::vector<int> &subnum) {
	int cur_node = root;
	visited[cur_node] = true;

	for(auto i=link[cur_node].begin();i<link[cur_node].end();++i) {
		if(visited[*i] == false) {
			find_sub(*i,link,visited,subnum);
			subnum[cur_node]+=subnum[*i];
		}
	}	
}
	
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	int N, R, Q;
	std::cin >> N >> R >> Q;
	std::vector<std::vector<int>> link(N+1,std::vector<int>());

	for(int i=0;i<N-1;++i) {
		int x,y;
		std::cin >> x >> y;
		link[x].push_back(y);
		link[y].push_back(x);
	}

	std::vector<bool> visited(N+1,false);
	std::vector<int> subnum(N+1,1); // 자기자신 1

	find_sub(R,link,visited,subnum);

	for(int i=0;i<Q;++i) {
		int a;
		std::cin >> a;
		std::cout << subnum[a] << '\n';
	}

	return 0;
}