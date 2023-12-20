#include <iostream>
#include <vector>
#include <algorithm>
// 전깃줄 교차를 없애기위해 제거해야 하는 줄 수?

class cable {

public:
    int left;
    int right;
    int dp;
};

int compare1(cable A,cable B) { // left 작은순으로 정렬.
    return A.left < B.left;
}
int compare2(cable A, cable B) {
    return A.dp > B.dp;
}
int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<cable> cable_vec;
    cable_vec.push_back({0,0,1}); // dummy data
    for(int i=1;i<=N;++i) {
        int left, right;
        std::cin >> left >> right;
        cable_vec.push_back({left,right,1});
    }

    std::sort(cable_vec.begin(),cable_vec.end(),compare1);

    // right에서 연결할 케이블들을 먼저 선택하자.
    int answer=0;
    for(int i=2;i<=N;++i) {
        for(int j=i-1;j>=1;--j) {
            if(cable_vec[i].right>cable_vec[j].right) {
                cable_vec[i].dp=std::max(cable_vec[i].dp,cable_vec[j].dp+1);
            }
        }
        answer=std::max(answer,cable_vec[i].dp);
    }
    std::cout << N-answer;
    return 0;
}