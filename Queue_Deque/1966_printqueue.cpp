#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

typedef struct _Data {
    int save;
    int index;
}Data;


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int T; // Data case
    std::cin >> T;
    
    for(int i=0;i<T;++i) {
        std::queue<Data> q; 
        std::vector<int> max_vec;
        int N, M; // N - num of data, M - find index
        std::cin >> N >> M;
        for(int j=0;j<N;++j) {
            int num;
            std::cin >> num;
            q.push({num,j});
            max_vec.push_back(num);
        }
        std::sort(max_vec.begin(),max_vec.end());
        int cnt=1;
        while(q.size()>0) {
            if(q.front().save==max_vec.back()) {
                max_vec.pop_back();
                if(q.front().index==M) {
                    std::cout << cnt << '\n';
                    break;
                }
                else {
                    q.pop();
                    cnt++;
                }
            }
            else {
                q.push(q.front());
                q.pop();
            }
        }
    }
    return 0;
}
