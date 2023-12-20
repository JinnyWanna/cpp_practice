#include <iostream>
#include <algorithm>
#include <vector>

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int grape[10001];
    int n;
    std::cin >> n;

    for(int i=1;i<=n;++i) {
        std::cin >> grape[i];
    }

    int maximum[10001];
    maximum[1]=grape[1]; maximum[2]=grape[1]+grape[2];


    for(int i=3;i<=n;++i) {
        maximum[i]=grape[i]+std::max(maximum[i-2],maximum[i-3]+grape[i-1]);
        maximum[i]=std::max(maximum[i],maximum[i-1]);
    }
    std::cout << maximum[n];
    return 0;
}