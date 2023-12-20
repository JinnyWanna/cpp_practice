#include <iostream>
#include <algorithm>
#include <vector>
// 파일을 어떤 순서로 합쳐야하는가?
//

int main(void) {
	std::ios_base::sync_with_stdio(false); 
    std::cin.tie(nullptr); std::cout.tie(nullptr);

	int T;
    std::cin >> T;
    for(int i=0;i<T;++i) {
        int k;
        std::cin >> k;
        int ch[501];
        int ch_sum[501][501]={0,};
        int dp[501][501];
        for(int i=1;i<=k;++i) {
            std::cin >> ch[i];
        }
        for(int i=1;i<=k;++i) {
            for(int j=i;j<=k;++j) {
                for(int t=i;t<=j;++t) {
                    ch_sum[i][j]+=ch[t];
                }
            }
        }

        for(int leng=1;leng<k;++leng) {
            for(int i=1;i<=k-leng;++i) {
                int j=leng+i;
                dp[i][j]=1000000000;
                for(int t=i;t<j;++t) {
                    dp[i][j]=std::min(dp[i][j],dp[i][t]+dp[t+1][j]+ch_sum[i][j]);
                }
            }
        }
        std::cout << dp[1][k] << '\n';
    }

    return 0;
}


