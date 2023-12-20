#include <iostream>
#include <queue>
#include <vector>
//
const int INF = 100000000;
const int MAX = 800+1;
//
struct Vpair{
    int link;
    int cost;
};

struct Qpair{
    int cur_node;
    int cost;
};
//
struct cmp{
    bool operator()(Qpair x,Qpair y) {
        return x.cost>y.cost;
    }
};
//
std::vector<Vpair> map[MAX];
int N,E; // Node수, linE수
int dist[MAX];
bool visited[MAX];
int point1,point2; // 방문지점
//
void bfs(int cur_node) { // 방문지점 체크해야함. 길이 양쪽으로 뚫려있어서 체크 안하면 중복발생.
// 일단 큐에는 다 넣은뒤, 방문한 노드를 재방문한 경우 그냥 continue하자.
    std::priority_queue<Qpair,std::vector<Qpair>,cmp> pQ;
    pQ.push({cur_node,0});
    
    for(int i=1;i<=N;++i) {
        dist[i]=INF;
        visited[i]=false;
    } //init

    dist[cur_node]=0; 

    while(!pQ.empty()) {
        cur_node=pQ.top().cur_node;
        int cost=pQ.top().cost;
        pQ.pop();
        if(visited[cur_node]) {
            continue; 
        }
        visited[cur_node]=true;
        //
        for(int i=0;i<map[cur_node].size();++i) {
            int ncost=map[cur_node][i].cost;
            int next_node=map[cur_node][i].link;

            if(dist[next_node]>cost+ncost) {
                dist[next_node]=cost+ncost;
                pQ.push({next_node,dist[next_node]});
            }
        }
    }
} 

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::cin >> N >> E;
    for(int i=0;i<E;++i) {
        int x,y,z;
        std::cin >> x >> y >> z; // x<->y , 비용 z 인 경로 존재 
        map[x].push_back({y,z});
        map[y].push_back({x,z});
    } // 지도 완성
    std::cin >> point1 >> point2; // 
    bfs(1);

    int ans;
    int ans1=dist[point1]; 
    int ans2=dist[point2];
    bfs(point2);
    ans1+=dist[N];

    bfs(point1);
    ans2+=dist[N];
    if(ans2>ans1) {
        ans=ans1;
    }
    else {
        ans=ans2;
    }
    ans += dist[point2];

    if(ans>=INF) {
        std::cout << "-1";
        return 0;
    }

    std::cout << ans << '\n';
    return 0;
}