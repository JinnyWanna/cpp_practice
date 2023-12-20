#include <iostream>
#include <vector>
#include <algorithm>

int M,N;
int arr[9]; int used[9];
std::vector<int> usevec;

void dfs(int k,int l) {
    if(k==N) {
        for(int i=0;i<N;++i) {
            std::cout << arr[i] << ' ';
        }
        std::cout << '\n';
        return;
    }

    for(int i=l;i<M;++i) {
        if(!used[i]) {
            arr[k]=usevec[i];
            used[i]=true;
            dfs(k+1,i+1);
            used[i]=false;
        }
    }
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::cin >> M >> N;

    for(int i=0;i<M;++i) {
        int k;
        std::cin >> k;
        usevec.push_back(k);
    }

    std::sort(usevec.begin(),usevec.end());

    dfs(0,0);
    return 0;
}