#include <iostream>

int arr[8];

void dfs(int K, int range, int ea) { // Kst number select

    if(K==ea) {
        for(int i=0;i<ea;++i) {
            std::cout << arr[i] << ' ';
        }
        std::cout << '\n';
        return;
    }
    else { // 0~(k-1)st number select
        for(int i=1;i<=range;++i) {
            arr[K]=i;
            dfs(K+1,range,ea);
        }
    }

}
int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL); std::cout.tie(NULL);
    int M, N;
    std::cin >> M >> N;

    dfs(0,M,N);

    return 0;
}