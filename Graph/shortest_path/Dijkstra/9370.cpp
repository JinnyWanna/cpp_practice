#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
//
const int MAX_n = 2000 + 1;
const int INF = 10000000;
//
int node, edge, num_possible_dest;
int startnode, between1, between2;
int dist[MAX_n];
bool visited[MAX_n];
//
struct Vpair {
    int next;
    int cost;
};
//
struct Qpair {
    int cur_node;
    int cost; 
};

struct cmp {
    bool operator() (Qpair x, Qpair y) {
        return x.cost>y.cost;
    }  
};

std::vector<Vpair> map[MAX_n];

void dijkstra(int start) { // start지점을 기준으로 모든 지점의 최소비용을 구함
    std::priority_queue<Qpair,std::vector<Qpair>,cmp> pQ;
    //init
    for(int i=1;i<=node;++i) {
        dist[i]=INF;
        visited[i]=false;
    }

    pQ.push({start,0});
    dist[start]=0;
    while(!pQ.empty()) {
        int cur=pQ.top().cur_node;
        int cost=pQ.top().cost;
        pQ.pop();
        if(visited[cur]) {
            continue;
        }
        visited[cur]=true;
        // 다익스트라 : 가장 비용이 낮은 노드에서 주변을 탐색하고
        // 그 노드에서 다른 노드로 갈수있는 비용이 현재 기록된 비용보다 작을경우 갱신
        // cost+ncost<dist[cur]일 경우 dist[cur]=cost+ncost;
        for(int i=0;i<map[cur].size();++i) {
            int next=map[cur][i].next;
            int ncost=map[cur][i].cost;
            
            if(dist[next]>cost+ncost) {
                dist[next]=cost+ncost;
                pQ.push({next,dist[next]});
            }
        }
    }
}

//
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    int T;
    std::cin >> T;
    for(int a=0;a<T;++a) {
        std::cin >> node >> edge >> num_possible_dest;
        std::cin >> startnode >> between1 >> between2;
        int cross; // 꼭 지나간 경로.
        // 이제 출발지~between1~between2~도착지 or 출~be2~be1~도착이 출~도착과 같은경우,
        // 그지점이 목적지가 될 수 있다.
        // 출발지점을 시작점으로 bfs한번, be1을 시작점으로 bfs 한번, be2를 시작점으로 bfs한번
        // 총 3번 진행하여 답을 구할 수 있다.//
        for(int i=0;i<edge;++i) {
            int a,b,d;
            std::cin >> a >> b >> d;
            map[a].push_back({b,d});
            map[b].push_back({a,d});

            if((a==between1&&b==between2)||(b==between1&&a==between2)) {
                cross=d;
            }

        }
        int result_start_end[MAX_n];
        int result_between1_end[MAX_n];
        int result_between2_end[MAX_n];

        dijkstra(startnode);
        for(int i=1;i<=node;++i) {
            result_start_end[i]=dist[i];
        }
        dijkstra(between1);
        for(int i=1;i<=node;++i) {
            result_between1_end[i]=dist[i];
        }
        dijkstra(between2);
        for(int i=1;i<=node;++i) {
            result_between2_end[i]=dist[i];
        }

        std::vector<int> ans;
        for(int i=0;i<num_possible_dest;++i) {
            int x;
            std::cin >> x;
            if((result_start_end[x]==cross+result_start_end[between1]+result_between2_end[x])||(result_start_end[x]==cross+result_start_end[between2]+result_between1_end[x])) {
                ans.push_back(x);
            }
        }
        std::sort(ans.begin(),ans.end());

        for(int i=0;i<ans.size();++i){
            std::cout << ans[i] << ' ';
        }

        std::cout << '\n';
        for(int i=1;i<=node;++i) {
            map[i].clear();
        }
    }
    return 0;
}