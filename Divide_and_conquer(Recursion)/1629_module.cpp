#include <iostream>
#include <vector>
#include <algorithm>

int a,b,c;

long long int func(int x,int y) {
    if(y==0) return 1;
    else if(y==1) return x;

    if(y%2>0) return func(x,y-1)*x%c;
    long long int mod=func(x,y/2);
    mod%=c;
    return (mod*mod)%c;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);


    std::cin >> a >> b >> c;
    long long int ans = func(a,b);

    std::cout << ans%c;

    return 0;
}
