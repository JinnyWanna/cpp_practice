#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
#include <cstring>

#define fastio                        \
    std::ios::sync_with_stdio(false); \
    std::cin.tie(nullptr);            \
    std::cout.tie(nullptr);

int N;
int dp[1 << 20];
int cost[21][21];

void input() {
    std::cin >> N;

    for(int i=0;i<N;++i) {
        for(int j=0;j<N;++j) {
            std::cin >> cost[i][j];
        }
    }
}

int dfs(int cur, int dpnum) {
    int &ret = dp[dpnum];

    if(cur == N) return 0;
    if(ret != -1) return ret;

    ret = INT_MAX;
    for(int i=0;i<N;++i) {
        if(!(dpnum & (1 << i)))
            ret = std::min(ret,dfs(cur+1,dpnum|(1<<i))+cost[cur][i]); 
    }
    return ret;
}

int main() {
    fastio;

    input();
    memset(dp,-1,sizeof dp);
    std::cout << dfs(0,0) << ' ' << dp[0] << '\n';
    
    return 0;
}