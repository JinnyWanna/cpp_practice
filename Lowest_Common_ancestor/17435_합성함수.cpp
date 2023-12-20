#include <algorithm>
#include <iostream>
#include <queue>
#include <cmath>
#include <vector>

#define fastio                        \
    std::ios::sync_with_stdio(false); \
    std::cin.tie(nullptr);            \
    std::cout.tie(nullptr);

// parent[a][b] a의 2^b 번째 조상

void mkparent(std::vector<std::vector<int>> &parent, const int m, const int MAX) {
    // parent[i][k] = parent[parent[i][k-1]][k-1];

    for(int k = 1; k<=MAX; ++k) {
        for(int i=1; i<=m; ++i) {
            parent[i][k] = parent[parent[i][k-1]][k-1];
        }
    }
}

int main() {
    fastio;

    int m;
    std::cin >> m;

    const int MAX = (int)ceil(log2(500000+1));

    std::vector<std::vector<int>> parent(m+1,std::vector<int>(MAX,0));    

    for(int i=1;i<=m;++i) {
        std::cin >> parent[i][0];
    }

    mkparent(parent,m,MAX);

    int Q;
    std::cin >> Q;

    for(int i=0;i<Q;++i) {
        int x, y;
        std::cin >> x >> y;
        // y의 x번째 조상
        for(int j=MAX;j>=0;--j) {
            if(x>=pow(2,j)) {
                y=parent[y][j];
                x-=pow(2,j);
            }
        }
        std::cout << y << '\n';
    }

    return 0;
}

/*
5
3 3 5 4 3
1
2 1
*/