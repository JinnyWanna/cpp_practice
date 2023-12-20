#include <iostream>
#include <vector>
#include <queue>

bool visited[100001];
int before[100001];
std::vector<int> path;

struct pair{
    int cur_point;
    int cnt;
};

void bfs(std::queue<pair> &Q,int start,int cur,int end) {
    Q.push({cur,0});
    visited[cur]=true;
    while(!Q.empty()) {
        cur=Q.front().cur_point;
        int time=Q.front().cnt;
        Q.pop();

        if(cur==end) {
            std::cout << time << '\n';

            int idx=cur;
            while(idx!=start) {
                path.push_back(idx);
                idx=before[idx];
            }
            std::cout << start << ' ';
            for(int i=path.size()-1;i>=0;--i) {
                std::cout << path[i] << ' ';
            }
            return;
        }

        if(cur-1>=0&&!visited[cur-1]) {
            Q.push({cur-1,time+1});
            visited[cur-1]=true;
            before[cur-1]=cur;
        }
        if(cur+1<=100000&&!visited[cur+1]) {
            Q.push({cur+1,time+1});
            visited[cur+1]=true;
            before[cur+1]=cur;
        }
        if(2*cur<=100000&&!visited[2*cur]) {
            Q.push({2*cur,time+1});
            visited[2*cur]=true;
            before[2*cur]=cur;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int N, K;
    std::cin >> N >> K;
    std::queue<pair> Q;

    if(N>K) {
        std::vector<int> v;
        for(int i=N;i>=K;--i) {
            v.push_back(i);
        }
        std::cout << N-K << '\n';
        for(int i=0;i<v.size();++i) {
            std::cout << v[i] << ' ';
        }
        return 0;
    }

    bfs(Q,N,N,K);

    return 0;
}