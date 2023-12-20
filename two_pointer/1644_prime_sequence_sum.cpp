#include <iostream>
#include <vector>
#include <algorithm>


void eratos(std::vector<int> &seq,int find) {
    bool *arr = new bool[find+1];
    std::fill(arr,arr+find+1,true);
    for(int i=2;i*i<=find;++i) {
        if(!arr[i]) continue;

        for(int j=i*i;j<=find;j+=i) {
            arr[j]=false;
        }
    }
    for(int i=2;i<=find;++i) {
        if(arr[i]) {
            seq.push_back(i);
        }
    }
    delete []arr;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::vector<int> num;    
    int N;
    std::cin >> N;   
    
    if(N==1) {
        std::cout << '0';
        return 0;
    }
    eratos(num,N); // num 배열에 N보다 작은 소수들 모두 저장

    int start=0; int end=0;
    int cnt=0;
    int sum=num[0];
    while(start<=end&&end<num.size()) {
        if(sum==N) {
            cnt++;
            sum-=num[start];
            start++;
        }
        else if(sum>N) {
            sum-=num[start];
            start++;
        }
        else {
            end++;
            sum+=num[end];
        }
    }
    std::cout << cnt;

    return 0;
}