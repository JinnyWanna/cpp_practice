#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

const int INF = 1000000000; // infinite
const int MAX = 20000+1;
//
struct Vpair{
    int link; // 연결된 노드
    int cost; // 이동 비용
};

struct Qpair{
    int cost; // 현위치의 최소 비용
    int cur_point; // 현위치
};

struct cmp{
    bool operator()(Qpair x,Qpair y){
        return x.cost>y.cost;
    }
};

//
int node,line,startnode;
std::vector<Vpair> map_vec[MAX];
int dist[MAX];
// 다익스트라 알고리즘 :: 특정 지점까지 이동하는데 드는 최소 비용을 구함

// 우선순위 큐로 현재 비용이 가장 작은 노드부터 선택. 
// 현재비용+추가비용 < 기록된 비용 ==> 새로 기록

void bfs() {
    std::priority_queue<Qpair,std::vector<Qpair>,cmp> pQ;
    pQ.push({0,startnode});
    dist[startnode]=0;

    while(!pQ.empty()) {
        int cost=pQ.top().cost;
        int cur=pQ.top().cur_point;
        pQ.pop();

        for(int i=0;i<map_vec[cur].size();++i) {
            int link_point=map_vec[cur][i].link;
            int ncost=map_vec[cur][i].cost;
            if(dist[link_point]>cost+ncost) {
                dist[link_point]=cost+ncost;
                pQ.push({dist[link_point],link_point});
            }
        }
    }

}

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::cin >> node >> line >> startnode;

    for(int i=0;i<line;++i) {
        int x,y,z;
        std::cin >> x >> y >> z;
        map_vec[x].push_back({y,z}); // x->y 비용 z
    }
    for(int i=1;i<=node;++i) {
        dist[i]=INF;
    }

    bfs();

    for(int i=1;i<=node;++i) {
        if(dist[i]==INF) {
            std::cout << "INF" << '\n';
        }
        else{
            std::cout << dist[i] << '\n';
        }
    }

    return 0;
}