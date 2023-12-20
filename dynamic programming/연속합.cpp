#include <iostream>
#include <vector>
#include <algorithm>
// 왼쪽수 부터 구간합의 최대를 구하고, 그 수가 자신의 수보다 크면 저장
// 수 자신 vec[i]보다 dp[i-1]가 큰경우 dp에 dp[i-1]+vec[i]

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> vec;
    vec.push_back(0); // dummy data
    for(int i=1;i<=n;++i) {
        int num;
        std::cin >> num;
        vec.push_back(num);
    }
 // 왼쪽수부터 진행.
    int answer=-1000;
    int dp[100001]={0,};
    for(int i=1;i<=n;++i) {
        dp[i]=std::max(vec[i],dp[i-1]+vec[i]);
        answer=std::max(answer,dp[i]);
    }

    std::cout << answer;    

    return 0;
}