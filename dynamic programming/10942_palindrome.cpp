#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    int N;
    std::cin >> N;

    int seq[2001];

    for(int i=1;i<=N;++i) {
        std::cin >> seq[i];
    }

    bool dp[2000+1][2000+1]={false, }; // 
    for(int i=1;i<=N;++i) {
        dp[i][i]=true;
    }
    for(int i=1;i<N;++i) {
        if(seq[i]==seq[i+1]) dp[i][i+1]=true;
    }
    for(int j=2;j<=N-1;++j) {
        for(int i=1;i<=N-j;++i) {
            if(dp[i+1][i+j-1]) { // 이게 true일때
                if(seq[i]==seq[i+j]) {
                    dp[i][i+j]=true;
                }
            }
        }
    }

    int M;
    std::cin >> M;

    for(int i=0;i<M;++i) {
        int x,y;
        std::cin >> x >> y;
        if(dp[x][y]) {
            std::cout << '1' << '\n';
        }
        else {
            std::cout << '0' << '\n';
        }
    }

    return 0;
}