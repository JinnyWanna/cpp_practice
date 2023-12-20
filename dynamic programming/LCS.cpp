#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::string str1, str2;
    std::cin >> str1 >> str2;

    int str1_len=str1.length();
    int str2_len=str2.length();

    int dp[1001][1001]={0,};

    for(int i=1;i<=str1_len;++i) {
        for(int j=1;j<=str2_len;++j) {
            if(str1[i-1]==str2[j-1]) {
                dp[i][j]=dp[i-1][j-1]+1;
            }
            else {
                dp[i][j]=std::max(dp[i][j-1],dp[i-1][j]);
            }
        }
    }
    std::cout << dp[str1_len][str2_len];
    return 0;
}