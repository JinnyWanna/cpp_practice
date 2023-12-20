#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    int RGB[1001][3] = {0,};
    int dp[1001][3][3] = {0,}; // [1001][현위치][N집] // N집을 정해놓고 감

    for(int i=0;i<=N;++i) {
        for(int j=0;j<3;++j) {
            for(int k=0;k<3;++k) {
                dp[i][j][k] = 1001;
            }
        }
    }
    
    for(int i=1;i<=N;++i) {
        std::cin >> RGB[i][0] >> RGB[i][1] >> RGB[i][2];
    }
    
    dp[1][0][1] = RGB[1][0];
    dp[1][0][2] = RGB[1][0];
    dp[1][1][0] = RGB[1][1];
    dp[1][1][2] = RGB[1][1];
    dp[1][2][0] = RGB[1][2];
    dp[1][2][1] = RGB[1][2];

    for(int i=2;i<=N-1;++i) {
        dp[i][0][0] = RGB[i][0] + std::min(dp[i-1][1][0],dp[i-1][2][0]);
        dp[i][0][1] = RGB[i][0] + std::min(dp[i-1][1][1],dp[i-1][2][1]);
        dp[i][0][2] = RGB[i][0] + std::min(dp[i-1][1][2],dp[i-1][2][2]);
        dp[i][1][0] = RGB[i][1] + std::min(dp[i-1][0][0],dp[i-1][2][0]);
        dp[i][1][1] = RGB[i][1] + std::min(dp[i-1][0][1],dp[i-1][2][1]);
        dp[i][1][2] = RGB[i][1] + std::min(dp[i-1][0][2],dp[i-1][2][2]);
        dp[i][2][0] = RGB[i][2] + std::min(dp[i-1][0][0],dp[i-1][1][0]);
        dp[i][2][1] = RGB[i][2] + std::min(dp[i-1][0][1],dp[i-1][1][1]);
        dp[i][2][2] = RGB[i][2] + std::min(dp[i-1][0][2],dp[i-1][1][2]);
    }

    int ans;

    dp[N][0][1] = dp[N-1][0][1]+RGB[N][1];
    ans = dp[N][0][1];
    dp[N][0][2] = dp[N-1][0][2]+RGB[N][2];
    ans = std::min(ans,dp[N][0][2]);
    dp[N][1][0] = dp[N-1][1][0]+RGB[N][0];
    ans = std::min(ans,dp[N][1][0]);
    dp[N][1][2] = dp[N-1][1][2]+RGB[N][2];
    ans = std::min(ans,dp[N][1][2]);
    dp[N][2][0] = dp[N-1][2][0]+RGB[N][0];
    ans = std::min(ans,dp[N][2][0]);
    dp[N][2][1] = dp[N-1][2][1]+RGB[N][1];
    ans = std::min(ans,dp[N][2][1]);

    std::cout << ans << '\n';

    return 0;
}

/*
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    int RGB[1001][3] = {0,};
    int dp[1001][3][3] = {0,};
    
    for(int i=0;i<=N;++i) {
        for(int j=0;j<3;++j) {
            for(int k=0;k<3;++k) {
                dp[i][j][k] = 1001;
            }
        }
    }
    
    for(int i=1;i<=N;++i) {
        std::cin >> RGB[i][0] >> RGB[i][1] >> RGB[i][2];
    }
    
    for(int i=0;i<3;++i) {
        for(int j=0;j<3;++j) {
            if(i==j) continue;

            dp[1][i][j] = RGB[1][i];
        }
    }

    for(int i=2;i<=N-1;++i) {
        for(int j=0;j<3;++j) {
            dp[i][0][j] = RGB[i][0] + std::min(dp[i-1][1][j],dp[i-1][2][j]);
        }
        for(int j=0;j<3;++j) {
            dp[i][1][j] = RGB[i][1] + std::min(dp[i-1][0][j],dp[i-1][2][j]);
        }
        for(int j=0;j<3;++j) {
            dp[i][2][j] = RGB[i][2] + std::min(dp[i-1][1][j],dp[i-1][0][j]);
        }
    }

    std::vector<int> ans;

    for(int i=0;i<3;++i) {
        for(int j=0;j<3;++j) {
            if(i==j) continue;

            ans.push_back(dp[N-1][i][j]+RGB[N][j]);
        }
    }

    std::cout << *std::min_element(ans.begin(),ans.end()) << '\n';

    return 0;
}
*/
