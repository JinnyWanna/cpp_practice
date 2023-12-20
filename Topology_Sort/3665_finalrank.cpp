#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#define fastio                        \
    std::ios::sync_with_stdio(false); \
    std::cin.tie(nullptr);            \
    std::cout.tie(nullptr);

std::vector<int> topology_sort(const int n, int *indeg, bool edge[][501], std::queue<int> &Q) {
    std::vector<int> ret;

    while(!Q.empty()) {
        int cur = Q.front();
        Q.pop();
        ret.push_back(cur);

        for(int i=1;i<=n;++i) {
            if(edge[cur][i] == true) {
                indeg[i]--;

                if(indeg[i] == 0) {
                    Q.push(i);
                }
            }
        }
    }
    return ret;
    
}

int main() {
    fastio;
    
    int tc;
    std::cin >> tc;
    while(tc--) {
        int n;
        std::cin >> n;

        bool edge[501][501] = {false, };
        bool seq[501] = {false, };
        int indeg[501] = {0, };

        for(int i=0;i<n;++i) {
            int num;
            std::cin >> num;
            seq[num] = true;

            for(int j=1;j<=n;++j) {
                if(seq[j] != true) {
                    edge[num][j] = true;
                    indeg[j]++;
                }
            } 
        }

        int m;
        std::cin >> m;

        for(int i=0;i<m;++i) {
            int x, y;
            std::cin >> x >> y;
            if(edge[x][y] == true) {
                edge[x][y] = false;
                edge[y][x] = true;
                indeg[y]--;
                indeg[x]++;
            }
            else {
                edge[y][x] = false;
                edge[x][y] = true;
                indeg[x]--;
                indeg[y]++;
            } 
        }

        std::queue<int> Q;

        for(int i=1;i<=n;++i) {
            if(indeg[i] == 0) 
                Q.push(i);
        }

        std::vector<int> ans = topology_sort(n,indeg,edge,Q);
        if(ans.size() != n) {   
            std::cout << "IMPOSSIBLE\n";
            continue;
        }

        for(auto i : ans) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}