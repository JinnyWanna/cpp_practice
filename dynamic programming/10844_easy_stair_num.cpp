#include <iostream>
#include <algorithm>
#include <vector>

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    long long dp[10][101];
    dp[0][1]=0;
    for(int i=1;i<=9;++i) {
        dp[i][1]=1;
    }

    for(int i=2;i<=N;++i) {
        for(int j=0;j<=9;++j) {
            if(j==0) {
                dp[j][i]=dp[j+1][i-1];
            }
            else if(j==9) {
                dp[j][i]=dp[j-1][i-1];
            }
            else {
                dp[j][i]=(dp[j-1][i-1]+dp[j+1][i-1])%1000000000;
            }
        }
    }
    long long sum=0;
    for(int j=0;j<=9;++j) {
        sum+=dp[j][N];
    }
    sum%=1000000000;
    std::cout << sum;
    return 0;
}