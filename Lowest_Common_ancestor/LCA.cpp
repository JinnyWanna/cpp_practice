#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>

int depth[10001];

void input(int &root, const int N, std::vector<std::vector<int>> &edge,
           int &node1, int &node2) {
    memset(depth, 0, sizeof(depth));

    for (int i = 0; i < N - 1; ++i) {
        int x, y;
        std::cin >> x >> y;

        edge[x].push_back(y);
        depth[y]++;
    }

    for (int i = 1; i <= N; ++i) {
        if (depth[i] == 0) {
            root = i;
            break;
        }
    }

    std::cin >> node1 >> node2;
}

void dfs(int curnode, int pnode, int lv, const int N,
         std::vector<std::vector<int>> &edge,
         std::vector<std::vector<int>> &parent, std::vector<int> &level,
         const int MAX) {
    level[curnode] = lv;
    parent[curnode][0] = pnode;

    for (auto i = edge[curnode].begin(); i < edge[curnode].end(); ++i) {
        if (*i == pnode) continue;

        dfs(*i, curnode, lv + 1, N, edge, parent, level, MAX);
    }

    return;
}

void connect(const int N, std::vector<std::vector<int>> &parent,
             const int MAX) {
    for (int k = 1; k < MAX; ++k) {
        for (int i = 1; i <= N; ++i) {
            parent[i][k] = parent[parent[i][k - 1]][k - 1];
        }
    }
}

int lca(int a, int b, const int N, std::vector<std::vector<int>> &edge,
        std::vector<std::vector<int>> &parent, std::vector<int> &level,
        const int MAX) {
    if (a == b) return a;

    if (level[a] < level[b]) {
        std::swap(a, b);
    }

    int diff = level[a] - level[b];


    if (level[a] != level[b]) {
        for (int i = MAX; i >= 0; --i) {
            if (level[parent[a][i]] >= level[b]) {
                a = parent[a][i];
            }
        }
    }

    if (a == b) return a;

    for (int i = MAX - 1; i >= 0; --i) {
        if (parent[a][i] != parent[b][i]) {
            a = parent[a][i];
            b = parent[b][i];
        }
    }

    return parent[a][0];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;

    while (tc--) {
        int N;
        std::cin >> N;

        const int MAX = (int)ceil(log2(N)) + 1;

        std::vector<std::vector<int>> edge(N + 1, std::vector<int>());
        std::vector<int> level(N + 1, 0);
        std::vector<std::vector<int>> parent(N + 1, std::vector<int>(MAX, 0));

        int node1, node2;
        int root = 0;

        input(root, N, edge, node1, node2);

        dfs(root, 0, 1, N, edge, parent, level, MAX);
        connect(N, parent, MAX);
        std::cout << lca(node1, node2, N, edge, parent, level, MAX) << '\n';

        edge = std::vector<std::vector<int>>();
        parent = std::vector<std::vector<int>>();
        level = std::vector<int>();
    }

    return 0;
}
