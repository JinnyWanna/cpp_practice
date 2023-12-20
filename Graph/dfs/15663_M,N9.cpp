#include <iostream>
#include <vector>
#include <algorithm>

int N, M;
std::vector<int> input_vec;
int ans_arr[9];
bool visited_arr[9];

void dfs(int k) {
    if(k==M) {
        for(int i=0;i<M;++i) {
            std::cout << ans_arr[i] << ' ';
        }
        std::cout << '\n';
        return;
    }
    int before=-1;
    for(int i=0;i<N;++i) { 
        if((!visited_arr[i])&&input_vec[i]!=before) {
            before=input_vec[i];
            visited_arr[i]=true;
            ans_arr[k]=input_vec[i];
            dfs(k+1);
            visited_arr[i]=false;
        }
    }

}

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::cin >> N >> M;
    for(int i=0;i<N;++i) {
        int num;
        std::cin >> num;
        input_vec.push_back(num);
    }
    std::sort(input_vec.begin(),input_vec.end());

    dfs(0);

    return 0;
}