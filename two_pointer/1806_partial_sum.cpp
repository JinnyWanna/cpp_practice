#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    const int INF = 2147483647;

    int N, S;
    std::cin >> N >> S; // N개 수 S이하
    std::vector<int> seq(N);
    for(int i=0;i<N;++i) {
        std::cin >> seq[i];
    }
    
    int start=0;
    int end=0;
    int length = INF;
    int sum=seq[0];

    while(start<=end&&end<N) {
        if(sum>S) {
            length=std::min(length,end-start+1);
            sum-=seq[start];
            start++;
        }
        else if(sum==S) {
            length=std::min(length,end-start+1);
            end++;
            sum+=seq[end];
        }
        else {
            end++;
            sum+=seq[end];
        }

    }
    if(length==INF) {
        std::cout << '0';
    }
    else {
        std::cout << length;
    }
    return 0;
}