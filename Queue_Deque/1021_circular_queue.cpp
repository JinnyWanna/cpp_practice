#include <iostream>
#include <deque>
#include <queue>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::deque<int> DQ_right;
    std::deque<int> DQ_left;
    
    std::queue<int> selectQ1;
    std::queue<int> selectQ2;
    int N,M;
    std::cin >> N >> M; // N:sizeofdeque, M=numofselect
    
    for(int i=1;i<=N;++i) {
        DQ_right.push_back(i);
        DQ_left.push_back(i);
    }
    for(int i=1;i<=M;++i) {
        int num;
        std::cin >> num;
        selectQ1.push(num);
        selectQ2.push(num);
    } //selectQ에 있는 순서대로 DQ에서 출력. 

    int cnt(0);
    // 이동횟수 저장. right, left중 횟수가 적은것 선택하여
    // cnt에 그 수 ++

    for(int i=0;i<M;++i) {
        int cnt_right(0);
        int cnt_left(0);
        // right
        while(1) {
            if(DQ_right.front()==selectQ1.front()) {
                DQ_right.pop_front();
                selectQ1.pop();
                break;
            }
            else {
                DQ_right.push_back(DQ_right.front());
                DQ_right.pop_front();
                cnt_right++;       
            }
        }
        // left
        while(1) {
            if(DQ_left.front()==selectQ2.front()) {
                DQ_left.pop_front();
                selectQ2.pop();
                break;
            }
            else {
                DQ_left.push_front(DQ_left.back());
                DQ_left.pop_back();
                cnt_left++;       
            }
        }
        // cnt+=min
        cnt+=std::min(cnt_left,cnt_right);
    }
    std::cout << cnt;
    return 0;
}
