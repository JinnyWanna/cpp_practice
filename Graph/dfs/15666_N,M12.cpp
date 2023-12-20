#include <iostream>
#include <vector>
#include <algorithm>

int N, M;
std::vector<int> input_vec;
int ans_arr[9];
bool visited_arr[9];
int length;

void dfs(int k,int l) {
    if(k==M) {
        for(int i=0;i<M;++i) {
            std::cout << ans_arr[i] << ' ';
        }
        std::cout << '\n';
        return;
    }

    for(int i=l;i<length;++i) {
        ans_arr[k]=input_vec[i];
        dfs(k+1,i);
    }
}

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::cin >> N >> M;

    for(int i=0;i<N;++i) {
        int input;
        std::cin >> input;
        input_vec.push_back(input);
    }
// input vec 생성
    std::sort(input_vec.begin(),input_vec.end());
    input_vec.erase(std::unique(input_vec.begin(),input_vec.end()),input_vec.end());
    length=input_vec.size();

    dfs(0,0);
    return 0;
}