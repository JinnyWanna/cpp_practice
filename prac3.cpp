#include <bits/stdc++.h>

void bfs(int &ans, std::vector<std::vector<int>> &edge, const int source, const int sink, const int N, std::vector<std::vector<int>> &capacity, std::vector<std::vector<int>> &flow) {

	while(true) { // bfs 1번당 유량경로 1개
		std::queue <int> Q;
		std::vector<int> parent(N+1, -1); // -1 ~visited // n visited
		Q.push(source);

		while(!Q.empty()) {
			int cur = Q.front();
			Q.pop();

			for(auto next : edge[cur]) {
				if(capacity[cur][next] - flow[cur][next] > 0 && parent[next] == -1) { // 용량이 남아있고, 방문 안한점이여야 함
					parent[next] = cur;

					if(next == sink) break;
					Q.push(next);
				}
			}
		}

		if(parent[sink] == -1) break; // sink까지 연결 실패 - 중지
	
		int minf_allow = INT_MAX;
		for(int i = sink; i != source; i = parent[i]) {
			minf_allow = std::min(minf_allow, capacity[parent[i]][i] - flow[parent[i]][i]);
		}

		for(int i = sink; i != source; i = parent[i]) {
			flow[parent[i]][i] += minf_allow;
			flow[i][parent[i]] -= minf_allow;
		}
		ans += minf_allow;
	}
	return;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	int N, P;
	std::cin >> N >> P;

	std::vector<std::vector<int>> flow(N+1, std::vector<int>(N+1, 0));
	std::vector<std::vector<int>> capacity(N+1, std::vector<int>(N+1, 0));
	std::vector<std::vector<int>> edge(N+1, std::vector<int>());

	for(int i=0; i<P ;++i) {
		int x, y;
		std::cin >> x >> y;

		edge[x].push_back(y);
		edge[y].push_back(x);

		capacity[x][y] = 1;
	}
	int ans(0);
	bfs(ans, edge, 1, 2, N, capacity, flow);

	std::cout << ans << '\n';
	return 0;
}