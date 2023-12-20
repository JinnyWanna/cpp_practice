#include <iostream>
#include <vector>
#include <algorithm>

int K,N;

int parametic_search(std::vector<int> vec,unsigned int start,unsigned int end) {
// mid 지점에서 count 개로 자를수 있는지 체크
    int ans(0);
    while(start<=end) {
        int cnt=0;
        int mid=(start+end)/2;
        for(int i=0;i<K;++i) {
            cnt+=(vec[i]/mid);
        }
        if(cnt>=N) { //가능, mid부터 end까지로 다시 진행
            start=mid+1;
            if(mid>ans) ans=mid;
        }
        else {
            end=mid-1;
        }
    }
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::cin >> K >> N;

    std::vector<int> input_vec;

    for(int i=0;i<K;++i) {
        int num;
        std::cin >> num;
        input_vec.push_back(num);
    }    

    unsigned int end=*std::max_element(input_vec.begin(),input_vec.end());

    int ans = parametic_search(input_vec,1,end);
    std::cout << ans;
    return 0;
}