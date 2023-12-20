#include <iostream>
#include <vector>
#include <queue>

struct Vpair{
    int next;
    int cost;
};

struct Qpair{
    int node;
    int cost;
};

struct cmp {
    bool operator()(Qpair x, Qpair y) {
        if(x.cost==y.cost) {
            return x.node>y.node;
        }
        return x.cost > y.cost;
    }
};

const int INF = 2147483647;
int dist[1001];
int before[1001];


void dijkstra(int start, const std::vector<Vpair> *map,std::priority_queue<Qpair,std::vector<Qpair>,cmp> &pQ) {
    pQ.push({start,0});
    for(int i=0;i<=1000;++i) {
        dist[i]=INF;
    }
    dist[start]=0;
    while(!pQ.empty()) {
        int cur_node=pQ.top().node;
        int cost=pQ.top().cost;
        pQ.pop();
        if(cost>dist[cur_node]) continue;
        for(int i=0;i<map[cur_node].size();++i) {
            int next=map[cur_node][i].next;
            int ncost=map[cur_node][i].cost;

            if(dist[next]>ncost+cost) {
                before[next]=cur_node;
                dist[next]=ncost+cost;
                pQ.push({next,dist[next]});
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int city, bus;
    std::vector<Vpair> map[1001]; // map[cur]={next,cost};
    std::priority_queue<Qpair,std::vector<Qpair>,cmp> pQ;
    
    std::cin >> city >> bus;

    for(int i=0;i<bus;++i) {
        int x, y, z;
        std::cin >> x >> y >> z;
        map[x].push_back({y,z});
    }
    int start, end;
    std::cin >> start >> end;
    dijkstra(start,map,pQ);

    std::cout << dist[end] << '\n';
    std::vector<int> path;
    while(end!=0) {
        path.push_back(end);
        end=before[end];
    }
    std::cout << path.size() << '\n';
    for(int i=path.size()-1;i>=0;--i) {
        std::cout << path[i] << ' ';
    } 
    return 0;
}