#include <iostream>
#include <vector>
#include <algorithm>
// 현재 500 하루당 k 감소
// N개의 키트 이용가능, 다음줄에 N개의 키트의 성능 주어짐 
// 항상 500이상 유지. 500밑이면 return
// 가능한 방법의 수 구하기

int day, loss;
std::vector<int> kit_vec;
int cnt=0;
bool used_kit_arr[10]; // 1~8 이용 , false 초기화
void dfs(int cur_day,int cur_weight) {

    if(cur_weight<500) return;

    if(cur_day==day+1) {
        cnt++;
        return;
    }

    for(int i=1;i<=day;++i) {
        if(!used_kit_arr[i]) {
            used_kit_arr[i]=true;
            cur_weight=cur_weight+kit_vec[i]-loss;
            dfs(cur_day+1,cur_weight); // cur_weight 연산을 진행하고 dfs하면 문제생김.
            used_kit_arr[i]=false;
        }
    }
}

int main() {

    std::cin >> day >> loss;
    kit_vec.push_back(0);
    for(int i=0;i<day;++i) {
        int kit;
        std::cin >> kit;
        kit_vec.push_back(kit); 
    }

    dfs(1,500);
    std::cout << cnt;
    return 0;
}