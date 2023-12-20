#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int N,M; // M 들수있는 무게
    std::cin >> N >> M;

    std::vector<int> weight;
    std::vector<int> value;

    std::vector<int> dp(M+1);
    for(int i=1;i<=N;++i) {
        int wei, val, cnt;
        std::cin >> wei >> val >> cnt;
        for(int j=cnt;j>0;j>>=1) {
            int twosquare=j-(j>>1);
            weight.push_back(wei*twosquare);
            value.push_back(val*twosquare);
        }
    }

    for(int i=0;i<weight.size();++i) {
        for(int j=M;j>weight[i];--j) {
            if(j-weight[i]>=0) {
                dp[j]=std::max(dp[j],dp[j-weight[i]]+value[i]);
            }
        }
    }
    std::cout << dp[M];

    return 0;
}