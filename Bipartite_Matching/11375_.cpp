#include <bits/stdc++.h>

bool dfs(int worker, std::vector<int> &Bmatch, std::vector<int> &Amatch, std::vector<bool> &visited, const std::vector<std::vector<int>> &edge) {
    for (auto work = edge[worker].begin(); work < edge[worker].end(); ++work) {
        if (visited[*work] == true) continue;

        visited[*work] = true;

        if (Bmatch[*work] == -1 || dfs(Bmatch[*work], Bmatch, Amatch, visited, edge)) {
            Amatch[worker] = *work;
            Bmatch[*work] = worker;

            return true;
        }
    }

    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int N, M; // 직원 / 일 수
    std::cin >> N >> M;

    std::vector<std::vector<int>> edge(N + 1, std::vector<int>());
	
    std::vector<int> Bmatch(M + 1, -1);  // work 에대한 worker 매치  // input이 B집합
    std::vector<int> Amatch(N + 1, -1);    // worker가 할 work 매치 // input이 A집합
	// 위 둘은 기능적으로 같음, work를 받아서 worker를 출력할지, worker를 받아서 work를 출력할지만 결정
    std::vector<bool> visited(M + 1, false);

    for (int i = 0; i < N; ++i) {
        int K;
        std::cin >> K;

        for (int j = 0; j < K; ++j) {
            int work;
            std::cin >> work;

            edge[i].push_back(work - 1);
        }
    }

    int ans = 0;

    for (int i = 0; i < N; ++i) {
        visited = std::vector<bool>(M + 1, false);

        if (dfs(i, Bmatch, Amatch, visited, edge)) {
            ans++;
        }
    
    }

    std::cout << ans << '\n';

    return 0;
}