#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#define fastio                        \
    std::ios::sync_with_stdio(false); \
    std::cin.tie(nullptr);            \
    std::cout.tie(nullptr);

int N, M;
std::queue<int> Q;

void input(std::vector<int> &student, std::vector<std::vector<int>> &edge) {

    for (int i = 0; i < M; ++i) {
        int x, y;
        std::cin >> x >> y;
        edge[x].push_back(y);
        student[y]++;
    }

    for (int i = 1; i <= N; ++i) {
        if (student[i] == 0) {
            Q.push(i);
        }
    }
}

std::vector<int> topology_sort(std::vector<int> &student, std::vector<std::vector<int>> &edge) {
    std::vector<int> seq;

    while (!Q.empty()) {
        int cur = Q.front();
        Q.pop();
        seq.push_back(cur);

        for (auto i = edge[cur].begin(); i < edge[cur].end(); ++i) {
            student[*i]--;

            if (student[*i] == 0) {
                Q.push(*i);
            }
        }
    }

    return seq;
}

int main() {
    fastio;
    std::cin >> N >> M;

    std::vector<int> student(N + 1, 0);
    std::vector<std::vector<int>> edge(N + 1, std::vector<int>());

    input(student,edge);

    std::vector<int> ans = topology_sort(student,edge);

    for (auto i = ans.begin(); i < ans.end(); ++i) {
        std::cout << *i << ' ';
    }

    std::cout << '\n';
    return 0;
}