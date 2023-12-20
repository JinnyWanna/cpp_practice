#include <iostream>
#include <vector>
#include <algorithm>
#define modl 1000000007


long long int func(long long int x,long long int y) { // x의 y제곱을 modl로 나눈 나머지
    if(y==0) return 1;
    else if(y==1) return x;

    if(y%2>0) return func(x,y-1)*x%modl;
    long long int mod=func(x,y/2);
    mod%=modl;
    return (mod*mod)%modl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    int n,k;
    std::cin >> n >> k;

    long long int A,B;
    A=1; B=1;
    for(int i=1;i<=n;++i) {
        A*=i;
        A%=modl;
    }
    for(int i=1;i<=k;++i) {
        B*=i;
        B%=modl;
    }
    for(int i=1;i<=n-k;++i) {
        B*=i;
        B%=modl;
    }    
    long long int ans=func(B,modl-2);
    ans=ans*A%modl;

    std::cout << ans;
    return 0;
}
