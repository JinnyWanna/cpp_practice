#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    int N;
    std::cin >> N;

    std::vector<int> vec;
    std::vector<int> answer;
    int dp[1001];    

    std::fill_n(dp,1001,1);

    vec.push_back(0);
    for(int i=1;i<=N;++i) {
        int vecin;
        std::cin >> vecin;
        vec.push_back(vecin);
    }

    int ans=0;
    for(int i=1;i<=N;++i) {
        for(int j=i-1;j>=1;--j) {
            if(vec[i]>vec[j])
                dp[i]=std::max(dp[j]+1,dp[i]);
        }
        ans=std::max(dp[i],ans);
    }
    int cnt=ans;
    for(int i=N;i>=1;--i) {
        if(dp[i]==cnt) {
            cnt--;
            answer.push_back(vec[i]);
        }
        if(cnt==0) break;
    }

    std::cout << ans << '\n';
    for(int i=ans-1;i>=0;--i) {
        std::cout << answer[i] << ' ';
    }
    return 0;
}