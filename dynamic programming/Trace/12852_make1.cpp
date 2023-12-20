#include <iostream>
#include <vector>
#include <queue>

bool visited[1000001];

struct pair{
    int num;
    int cnt;
    std::vector<int> vec;
};

void find(std::queue<pair> &Q) {
    while(!Q.empty()) {
        int num=Q.front().num;
        int cnt=Q.front().cnt;
        std::vector<int> vec=Q.front().vec;
        vec.push_back(num);
        Q.pop();
        if(num==1) {
            std::cout << cnt << '\n';
            for(int i=0;i<vec.size();++i) {
                std::cout << vec[i] << ' ';
            }
            return;
        }

        if(num%3==0&&!visited[num/3]) {
            visited[num/3]=true;
            Q.push({num/3,cnt+1,vec});
        }
        if(num%2==0&&!visited[num/2]) {
            visited[num/2]=true;
            Q.push({num/2,cnt+1,vec});
        }
        if(!visited[num-1]) {
            visited[num-1]=true;
            Q.push({num-1,cnt+1,vec});
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);  std::cout.tie(nullptr);
    
    int N;
    std::cin >> N;
    std::queue<pair> Q;
    Q.push({N,0});
    find(Q);
    return 0;   
}

/* 다른풀이
아래부터, 1부터 쌓아 올라가는 식으로 풀이
dp[i]=min(dp[i-1],dp[i/3],dp[i/2])+1 (i/3괴 i/2는 가능한 경우에만.)
경로를 기억하기 위해, 새로운 배열 하나를 더 만들어서, 지나친 값을 저장.
*/