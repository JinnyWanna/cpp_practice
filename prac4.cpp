#include <bits/stdc++.h>

struct pair {
    int start;
    int end;
};

int idx;

int dfs(const int node, int before, std::vector<std::vector<int>> &edge, std::vector<pair> &ans_edge, std::vector<int> &order) {

    order[node] = ++idx;

    int num = order[node];

    for(auto &next : edge[node]) {
        if(order[next] == 0) {

            int low = dfs(next, node, edge, ans_edge, order);

            num = std::min(num, low);

            if(low >= order[node]) {
                ans_edge.push_back({std::min(node, next), std::max(next, node)});
            }
        }

        else {
            num = std::min(num, order[next]);
        }
    }

    return num;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);  

    int V, E;
    std::cin >> V >> E;

    std::vector<std::vector<int>> edge(V+1, std::vector<int>());
    std::vector<pair> ans_edge;

    std::vector<int> order(V+1, 0);

    for(int i=0;i<E;++i) {
        int x, y;
        std::cin >> x >> y;

        edge[x].push_back(y);
        edge[y].push_back(x);
    }

    dfs(1,0,edge,ans_edge,order);

    std::cout << ans_edge.size() << '\n';

    for(int i=0;i<ans_edge.size();++i) {
        std::cout << ans_edge[i].start << ' ' << ans_edge[i].end << '\n';
    }

    return 0;
}