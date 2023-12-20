#include <iostream>
#include <queue>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::queue<int> Q;

    int N,K;
    std::cin >> N >> K;
    std::cout << '<';

    for(int i=1;i<=N;++i) {
        Q.push(i);
    }

    while(Q.size()>1) {
        for(int i=0;i<K-1;++i) {
            Q.push(Q.front());
            Q.pop();
        }
        std::cout << Q.front() << ", ";
        Q.pop();
    }
    std::cout << Q.front();
    std::cout << '>';
    return 0;
}
