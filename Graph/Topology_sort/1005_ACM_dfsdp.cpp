#include <algorithm>
#include <iostream>
#include <vector>
#define fastio                        \
    std::ios::sync_with_stdio(false); \
    std::cin.tie(nullptr);            \
    std::cout.tie(nullptr);

int input(const int N, const int rules, std::vector<int> &buildings,
           std::vector<std::vector<int>> &edge, int &target) {
    for (int i = 1; i <= N; ++i) {
        std::cin >> buildings[i];
    }

    for (int i = 0; i < rules; ++i) {
        int x, y;
        std::cin >> x >> y;
        edge[y].push_back(x);
    }

    std::cin >> target;

	return 0;
}

void dfs(int cur, std::vector<int> &dp, std::vector<int> &buildings,
         std::vector<std::vector<int>> &edge) {
    if(dp[cur] != -1) return;
    dp[cur] = buildings[cur];

    for (auto i = edge[cur].begin(); i < edge[cur].end(); ++i) {
        dfs(*i, dp, buildings, edge);

        if (dp[cur] < buildings[cur] + dp[*i])
            dp[cur] = buildings[cur] + dp[*i];
    }
}

int main() {
    fastio;

    int T;
    std::cin >> T;

    while (T--) {
        int N, rules, target;
        std::cin >> N >> rules;

        std::vector<int> buildings(N + 1, 0);
        std::vector<std::vector<int>> edge(N + 1, std::vector<int>());
        std::vector<int> dp(N + 1, -1);
    
        input(N, rules, buildings, edge, target);

        dfs(target, dp, buildings, edge);
        std::cout << dp[target] << '\n';
    }

    return 0;
}