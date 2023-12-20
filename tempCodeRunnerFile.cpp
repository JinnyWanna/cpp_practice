#include <bits/stdc++.h>

// 16928


void make_edge(const int N, const int M, std::vector<std::vector<int>> &edge) {

	int arr[101] = {0, };

	for(int i=0; i<N; ++i) {
		int x, y;
		std::cin >> x >> y;
		arr[x] = y;
	}

	for(int i=0; i<M; ++i) {
		int x, y;
		std::cin >> x >> y;
		arr[x] = y;
	}
	
	for(int i = 1; i<=100; ++i) {
		for(int j=i+1; j<=i+6 && j<=100; ++j) {
			if(arr[j] != 0) {
				edge[i].push_back(arr[j]);
			}
			edge[i].push_back(j);
		}
	}
}

void bfs(std::vector<std::vector<int>> &edge, const int start, const int end) {
	std::queue<int> Q;
	std::vector<bool> visited(101, false);
	std::vector<int> num(101, 0);

	Q.push(start);
	visited[start] = 0;

	while(!Q.empty()) {
		int now = Q.front();
		Q.pop();

		if(now == end) {
			std::cout << num[end] << '\n';
			return;
		}

		for(auto next : edge[now]) {
			if(visited[next] == false) { // 방문 안한 노드만 방문
				visited[next] = true; // 방문체크
				num[next] = num[now] + 1;
				Q.push(next);
			}
		}

	}
	return;
}


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	int N, M;
	std::cin >> N >> M;

	std::vector<std::vector<int>> edge(101, std::vector<int>());

	make_edge(N, M, edge);

	bfs(edge,1,100);

	return 0;
}