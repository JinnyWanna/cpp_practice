#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

const int MAX_n = 500+1;
const int INF = 10000000;

struct pair{
    int cur;
    int next;
    int time; // -10000~10000
};


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int N,M;
    long long int dist[MAX_n];
    std::vector<pair> map;

    std::cin >> N >> M;
    
    for(int i=0;i<M;++i) {
        int x,y,z;
        std::cin >> x >> y >> z;
        map.push_back({x,y,z}); // x->y cost z
    }    
    for(int i=1;i<=N;++i) {
        dist[i]=INF;
    }
    dist[1]=0;
    for(int i=1;i<N;++i) {
        for(int j=0;j<map.size();++j) {
            if(dist[map[j].cur]==INF) {
                continue;
            }

            // INF일때 컨티뉴 이유: 다른 방법으로 갈수없는 INF노드 두개 사이의 edge가 -1일때를 생각해보면
            // 연결당한 INF노드 하나가 INF-1로 갱신되는 오류 발생. 따라서 INF일 경우 그냥 탐색을 하지 말자.
            if(dist[map[j].next]>dist[map[j].cur]+map[j].time) {
                dist[map[j].next]=dist[map[j].cur]+map[j].time;
            }
        }
    }
    for(int j=0;j<map.size();++j) {
        if(dist[map[j].cur]==INF) continue;
        if(dist[map[j].next]>dist[map[j].cur]+map[j].time) {
            std::cout << "-1";
            return 0;
        }  
    }

    for(int i=2;i<=N;++i) {
        if(dist[i]==INF) {
            std::cout << "-1" <<'\n';
            continue;
        }
        std::cout << dist[i] << '\n';
    }
    // 무한 순환이 가능한 경우 -1 출력.

    return 0;
}