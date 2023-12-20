#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

bool visited[100001];
int N, K;

std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,std::greater<std::pair<int,int>>> pQ;

void bfs() {

    pQ.push({0,N});
    visited[N]=true;

    while(!pQ.empty()) {
        int point=pQ.top().second;
        int time=pQ.top().first;
        pQ.pop();

        if(point==K) {
            std::cout << time;
            return;
        }

        if(point*2<=100000&&!visited[point*2]) {
            pQ.push({time,point*2});
            visited[point*2]=true;
        }
        if(point-1>=0&&!visited[point-1]) {
            pQ.push({time+1,point-1});
            visited[point-1]=true;
        }
        if(point+1<=100000&&!visited[point+1]) {
            pQ.push({time+1,point+1});
            visited[point+1]=true;
        }

    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::cin >> N >> K;

    bfs();

    return 0;
}