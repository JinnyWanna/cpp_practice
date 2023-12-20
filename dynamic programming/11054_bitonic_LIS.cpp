#include <iostream>
#include <algorithm>

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    int arr[1001];

    for(int i=1;i<=n;++i) {
        std::cin >> arr[i];
    }

    int cnt_up[1001]={0,};
    int cnt_down[1001]={0,};

    std::fill_n(cnt_up,1001,1);
    std::fill_n(cnt_down,1001,1);

    for(int i=1;i<=n;++i) {
        for(int j=i-1;j>=1;--j) {
            if(arr[i]>arr[j]) {
                cnt_up[i]=std::max(cnt_up[i],cnt_up[j]+1);
            }
        }
    }

    for(int i=n;i>=1;--i) {
        for(int j=i+1;j<=n;++j) {
            if(arr[i]>arr[j]) {
                cnt_down[i]=std::max(cnt_down[i],cnt_down[j]+1);
            }
        }
    }

    int answer=1;
    for(int i=1;i<=n;++i) {
        answer=std::max(answer,cnt_up[i]+cnt_down[i]-1);
    }

    std::cout << answer;
    return 0;
}