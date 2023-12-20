#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

#define fastio                        \
    std::ios::sync_with_stdio(false); \
    std::cin.tie(nullptr);            \
    std::cout.tie(nullptr);

struct path {
    int before;
    int minpath;
    int maxpath;

    path() : before(0), minpath(0), maxpath(0) {}

    path(int _before, int _minpath, int _maxpath)
        : before(_before), minpath(_minpath), maxpath(_maxpath) {}

    path(const path &p) {
        this->before = p.before;
        this->maxpath = p.maxpath;
        this->minpath = p.minpath;
    }
};

struct pair {
    int next;
    int cost;

    pair() : next(0), cost(0) {}

    pair(int _next, int _cost) : next(_next), cost(_cost) {}

    pair(const pair &p) {
        this->next = p.next;
        this->cost = p.cost;
    }
};

void dfs(int curnode, int pnode, int lv, int cost,
         std::vector<std::vector<pair>> &edge,
         std::vector<std::vector<path>> &parent, std::vector<int> &level) {  //
    level[curnode] = lv;
    parent[curnode][0].before = pnode;  //
    parent[curnode][0].maxpath = cost;
    parent[curnode][0].minpath = cost;

    for (auto i = edge[curnode].begin(); i < edge[curnode].end(); ++i) {
        if (i->next == pnode) continue;

        dfs(i->next, curnode, lv + 1, i->cost, edge, parent, level);
    }
    return;
}
// min은 INT_MAX , max는 0 start
void LCA(int min, int max, int a, int b, const int N, const int MAX,
         std::vector<std::vector<path>> &parent, std::vector<int> &level) {
    if (level[a] < level[b]) {
        std::swap(a, b);
    }

    if (level[a] != level[b]) {
        for (int i = MAX; i >= 0; --i) {
            if (level[parent[a][i].before] >= level[b]) {
                min = std::min(min, parent[a][i].minpath);
                max = std::max(max, parent[a][i].maxpath);
                a = parent[a][i].before;
            }
        }
    }

    if (a == b) {
        std::cout << min << ' ' << max << '\n';
        return;
    }

    for (int i = MAX - 1; i >= 0; --i) {
        if (parent[a][i].before != parent[b][i].before) {
            min = std::min(
                min, std::min(parent[a][i].minpath, parent[b][i].minpath));
            max = std::max(
                max, std::max(parent[a][i].maxpath, parent[b][i].maxpath));

            a = parent[a][i].before;
            b = parent[b][i].before;
        }
    }

    min = std::min(min, std::min(parent[a][0].minpath, parent[b][0].minpath));

    max = std::max(max, std::max(parent[a][0].maxpath, parent[b][0].maxpath));

    std::cout << min << ' ' << max << '\n';

    return;
}

void mkparent(const int N, const int MAX,
              std::vector<std::vector<path>> &parent) {
    for (int k = 1; k <= MAX; ++k) {
        for (int i = 1; i <= N; ++i) {
            parent[i][k].before = parent[parent[i][k - 1].before][k - 1].before;
            parent[i][k].maxpath =
                std::max(parent[i][k - 1].maxpath,
                         parent[parent[i][k - 1].before][k - 1].maxpath);
            parent[i][k].minpath =
                std::min(parent[i][k - 1].minpath,
                         parent[parent[i][k - 1].before][k - 1].minpath);
        }
    }
}

void input_edge(const int N, std::vector<std::vector<pair>> &edge) {
    for (int i = 1; i < N; ++i) {
        int x, y, z;
        std::cin >> x >> y >> z;
        edge[x].push_back(pair(y, z));
        edge[y].push_back(pair(x, z));
    }
}

int main() {
    fastio;

    int N;
    std::cin >> N;

    const int MAX = (int)ceil(log2(N + 1));

    std::vector<std::vector<pair>> edge(N + 1, std::vector<pair>());
    std::vector<std::vector<path>> parent(
        N + 1, std::vector<path>(MAX + 1, path(0, 0, 0)));
    std::vector<int> level(N + 1, 0);

    input_edge(N, edge);

    dfs(1, 0, 1, 0, edge, parent, level);

    mkparent(N, MAX, parent);

    int K;
    std::cin >> K;

    for (int i = 0; i < K; ++i) {
        int x, y;
        std::cin >> x >> y;

        LCA(1000001, 0, x, y, N, MAX, parent, level);
        // 함수 돌리기
    }

    return 0;
}