#include <iostream>
#include <vector>
#include <algorithm>
int N;
std::vector<long long> ans_vec;
int input_num[15];

void dfs(int num,int plus,int sub,int mul, int divd,long long ans) {
    if(num==N) {
        ans_vec.push_back(ans);
        return;
    }

    if(plus>0) {
        dfs(num+1,plus-1,sub,mul,divd,ans+input_num[num+1]);
    }
    if(sub>0) {
        dfs(num+1,plus,sub-1,mul,divd,ans-input_num[num+1]);
    }
    if(mul>0) {
        dfs(num+1,plus,sub,mul-1,divd,ans*input_num[num+1]);
    }
    if(divd>0) {
        dfs(num+1,plus,sub,mul,divd-1,ans/input_num[num+1]);
    }
    
}

int main() {

    std::cin >> N;
    for(int i=1;i<=N;++i) {
        std::cin >> input_num[i];
    }
    int plus, sub, mul, divd;
    std::cin >> plus;
    std::cin >> sub;
    std::cin >> mul;
    std::cin >> divd;
    dfs(1,plus,sub,mul,divd,input_num[1]);
    std::sort(ans_vec.begin(),ans_vec.end());

    std::cout << ans_vec[ans_vec.size()-1] << '\n';
    std::cout << ans_vec[0];
    return 0;
}