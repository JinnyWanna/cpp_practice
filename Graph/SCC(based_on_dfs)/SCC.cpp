// https://dlog0518.tistory.com/50

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

#define fastio                        \
    std::ios::sync_with_stdio(false); \
    std::cin.tie(nullptr);            \
    std::cout.tie(nullptr);

const int MAX = 10001;

int idx, lambda[MAX];
bool finished[MAX];
std::vector<int> graph[MAX];
std::vector<std::vector<int>> SCC;
std::stack<int> s;
int v, e;

void input() {
    std::cin >> v >> e;

    for (int i = 0; i < e; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
    }
}

int dfs(int cur) {
    lambda[cur] = ++idx;
    s.push(cur);
    int parent = lambda[cur];

    for (auto i = graph[cur].begin(); i < graph[cur].end(); ++i) {
        if (lambda[*i] == 0)
            parent = std::min(parent, dfs(*i));

        else if (finished[*i] == false)
            parent = std::min(parent, lambda[*i]);
    }

    if (parent == lambda[cur]) {
        std::vector<int> scc;
        while (true) {
            int top = s.top();
            s.pop();
            scc.push_back(top);
            finished[top] = true;
            if (top == cur) break;
        }
        std::sort(scc.begin(), scc.end());
        SCC.push_back(scc);
    }
    return parent;
}

int main() {
    fastio;

    input();

    for (int i = 1; i <= v; ++i) {
        if (lambda[i] == 0) dfs(i);
    }

    std::cout << SCC.size() << '\n';
    std::sort(SCC.begin(), SCC.end());

    for (int i = 0; i < SCC.size(); ++i) {
        for (int j = 0; j < SCC[i].size(); ++j) {
            std::cout << SCC[i][j] << ' ';
        }
        std::cout << "-1\n";
    }

    return 0;
}