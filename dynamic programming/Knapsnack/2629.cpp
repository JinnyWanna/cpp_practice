#include <iostream>
#include <vector>
#include <cmath>

void solved(std::vector<int> &weight,int start,int end,int sum,bool (*ans)[15001]) {
    if(start>end||ans[start][sum]) { // 이미 체크한 무게를 안보게해서, 시간 절약
        return;
    }
    ans[start][sum]=true;
    solved(weight,start+1,end,sum,ans); // 이번 추 이용x
    solved(weight,start+1,end,sum+weight[start],ans); // 이번 추 사용
    solved(weight,start+1,end,abs(sum-weight[start]),ans); // 뺌, 반대쪽에 두는경우
}
//i까지 시행했을때, 추를 이용한거, 이용 안한거, 반대저울에 올려놓은것들이 모두 계산됨.

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    bool dp[31][15001]={false, };
    // dp를 1차원으로 하면 dfs가 돌아갔을때 이미 지나친 자리는 안가게됨
    // dp를 2차원으로 하여 순서까지 체크해주자
    int N; // 추 개수
    std::cin >> N;
    std::vector<int> weight;
    for(int i=0;i<N;++i) {
        int x;
        std::cin >> x;
        weight.push_back(x);
    }

    solved(weight,0,N,0,dp);

    int find_num;
    std::cin >> find_num;

    for(int i=0;i<find_num;++i) {
        int x;
        std::cin >> x;
        if(x>15000) std::cout << "N ";
        else if(dp[N][x]) std::cout << "Y ";
        else std::cout << "N ";
    }

    return 0;
}

/*
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int N, M;
    std::cin >> N >> M;
    
    int m[101];
    int c[101];

    for(int i=1;i<=N;++i) {
        std::cin >> m[i];
    }
    int sum=0;
    for(int i=1;i<=N;++i) {
        std::cin >> c[i];
        sum+=c[i];
    }
    int dp[10001]={0,};

	for(int i=1;i<=N;++i) {
		for(int j=sum;j>0;--j) {
			if(j-c[i]>=0) {
				dp[j]=std::max(dp[j],dp[j-c[i]]+m[i]);
			}
		}
	}
	for(int i=1;i<=sum;++i) {
		if(dp[i]>=M) {
			std::cout << i;
			return 0;
		}
	} 

    return 0;
}
*/