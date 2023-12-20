#include <iostream>
#include <algorithm>
#include <vector>

int N,C; // C개 설치
std::vector<int> v;

int dist(int start,int end) {
    int ans=0;

    while(start<=end) {
        int cnt=1;
        int mid=(start+end)/2;
        int prev=v[0];
        for(int i=1;i<N;++i) {
            if(v[i]-prev>=mid) {
                prev=v[i];
                cnt++;
            }
        }
        if(cnt>=C) {
            start=mid+1;
            if(ans<mid) ans=mid;
        }
        else end=mid-1;
    }

    return ans;
}


int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    std::cin >> N >> C;

    for(int i=0;i<N;++i) {
        int num;
        std::cin >> num;
        v.push_back(num);
    }

    std::sort(v.begin(),v.end());
    int end=v[N-1]-v[0];

    std::cout << dist(0,end);

    return 0;
}