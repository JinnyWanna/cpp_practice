#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::string str1, str2;
    str1='0'; str2='0';
    
    std::string substr1;
    std::cin >> substr1;
    str1+=substr1;
    
    std::string substr2;
    std::cin >> substr2;
    str2+=substr2;

    int dp[1001][1001]={0, };
    bool index[1001][1001]={false,};
    for(int i=1;i<str1.length();++i) {
        for(int j=1;j<str2.length();++j) {
            if(str1[i]==str2[j]) {
                dp[i][j]=std::max(dp[i][j-1],dp[i-1][j-1]+1);
                index[i][j]=true;  
            }
            else {
                dp[i][j]=std::max(dp[i][j-1],dp[i-1][j]);
            }
        }
    }

    std::stack<char> s;
    int find_idx=dp[str1.length()-1][str2.length()-1];

    for(int i=str1.length()-1;i>=1;--i) {
        for(int j=str2.length()-1;j>=1;--j) {
            if(index[i][j]==true&&dp[i][j]==find_idx) {
                s.push(str1[i]);
                find_idx--;
                break;
            }
        }
    }

    std::cout << dp[str1.length()-1][str2.length()-1] << '\n';
    for(int i=0;i<dp[str1.length()-1][str2.length()-1];++i) {
        std::cout << s.top();
        s.pop();
    }
    return 0;
}