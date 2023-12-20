#include <iostream>
#include <vector>
#include <algorithm>

int whole, sel;
int cow[10]; // 1~9
int visited[10]; // 1~9 이용
std::vector<int> ans_vec;

bool is_prime(int);

void dfs(int select_num,int ans,int k) {
    if(select_num>sel) {
        if(!is_prime(ans)) {
            return;
        }
        ans_vec.push_back(ans);
        return;
    }

    for(int i=k;i<=whole;++i) {
        if(!visited[i]) {
            visited[i]=true;
            dfs(select_num+1,ans+cow[i],i+1);
            visited[i]=false;
        }
    }
}

bool is_prime(int num) {
    if(num<2) return false;
    for(int i=2;i*i<=num;++i) {
        if(num%i==0) return false;
    }
    return true;
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::cin >> whole >> sel;
    for(int i=1;i<=whole;++i) {

        std::cin >> cow[i];
    }

    dfs(1,0,1);

    if(ans_vec.size()==0) {
        std::cout << -1;
        return 0;
    }

    std::sort(ans_vec.begin(),ans_vec.end());
    ans_vec.erase(std::unique(ans_vec.begin(),ans_vec.end()),ans_vec.end()); 
    for(int i=0;i<ans_vec.size();++i) {
        std::cout << ans_vec[i] << ' ';
    }
    return 0;
}