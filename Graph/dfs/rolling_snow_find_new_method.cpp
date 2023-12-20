#include <iostream>
#include <vector>
#include <algorithm>
int length, times;
int length_arr[101];
std::vector<int> ans_vec;

void find(int cur_time,int cur_pos, bool move, int size) { // move가 true면 두칸이동

    if(cur_time>times) {
        ans_vec.push_back(size);
        return;
    }
    if(cur_pos==0) {
        find(cur_time+1,cur_pos+1,false,size);
        find(cur_time+1,cur_pos+2,true,size);
    }
    
    if(move) { // true
        size=(size/2)+length_arr[cur_pos];

        find(cur_time+1,cur_pos+1,false,size);
        find(cur_time+1,cur_pos+2,true,size);
    }

    else { // false
        size+=length_arr[cur_pos];

        find(cur_time+1,cur_pos+1,false,size);
        find(cur_time+1,cur_pos+2,true,size);
    }

}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::cin >> length >> times;
    
    for(int i=1;i<=length;++i) {
        std::cin >> length_arr[i];       
    }

    find(0,0,false,1);
    find(0,0,true,1);

    std::sort(ans_vec.begin(),ans_vec.end(),std::greater<int>());

    std::cout << ans_vec[0];

    return 0;
}

/*
#include <bits/stdc++.h>
using namespace std;
int n, m, a[101];

int bruteForce(int idx, int cnt, int size){
    if(cnt > m) return 0;
    if(cnt == m) return size;
    int ans = 0;
    ans = max(bruteForce(idx + 1, cnt + 1, size + a[idx+1]), bruteForce(idx + 2, cnt + 1, size/2 + a[idx+2]));
    return ans;
}

int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i];
    cout << bruteForce(0,0,1);
}
*/