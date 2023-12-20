#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <stack>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int N;
    std::cin >> N;

    std::queue<int> queue;
    std::vector<int> vec;
    for(int i=0;i<N;++i) {
        int num;
        std::cin >> num;
        queue.push(num);
        vec.push_back(num);
    }
    for(int i=N-1;i>0;--i) {
        vec[i-1]=std::max(vec[i-1],vec[i]);
    }
    int cur_num(0);
    int cur_point(0);
    int cnt;
    do {
        if(cur_num==0) {
            cur_num=queue.front();
            queue.pop();
            cnt=1;
            if(vec[cur_point]==cur_num) {
                std::cout << "-1" << ' ';
                cur_num=0;
                cur_point++;
            }
        }
        else{ 
            if(queue.front()>cur_num) {
                while(cnt) {
                    std::cout << queue.front() << ' ';
                    cnt--;
                }
                cur_num=0;
                cur_point++;
            }
            else {
                cnt++;
                queue.pop();
                cur_point++;
            }
        }
    } while(!queue.empty());
    return 0;
}
