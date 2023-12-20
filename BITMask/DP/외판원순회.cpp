#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
#define INT_MAX 1000000000
#define fastio                        \
    std::ios::sync_with_stdio(false); \
    std::cin.tie(nullptr);            \
    std::cout.tie(nullptr);

int N;
int dp[10][1<<10]; 
int W[11][11];

void input() {
    std::cin >> N;
    
    for(int i=0;i<N;++i) {
        for(int j=0;j<N;++j) {
            std::cin >> W[i][j];
        }
    }
}

int dfs(int before, int dpnum) {
    int &ret = dp[before][dpnum];

    if(dpnum == (1<<N)-2) return W[before][0] ? W[before][0] : INT_MAX;
    if(ret != -1) return ret;

    ret = INT_MAX;
    for(int i=1;i<N;++i) {
        if(!(dpnum & (1<<i)) && W[before][i] != 0) {    
            ret = std::min(ret,dfs(i,dpnum | (1<<i)) + W[before][i]);
        }
    }

    return ret;
}

int main() {
    fastio;

    input();
    memset(dp,-1,sizeof(dp));

    std::cout << dfs(0,0) << '\n';
    return 0;
}