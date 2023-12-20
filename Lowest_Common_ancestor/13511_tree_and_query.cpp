#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

typedef long long lint;

#define fastio                        \
    std::ios::sync_with_stdio(false); \
    std::cin.tie(nullptr);            \
    std::cout.tie(nullptr);

struct pair {
    lint next;
    lint cost;

    pair(lint _next, lint _cost) : next(_next), cost(_cost) {}
};

void input(std::vector<std::vector<pair>> &edge, const lint N) {
    for (lint i = 1; i < N; ++i) {
        lint x, y, z;
        std::cin >> x >> y >> z;

        edge[x].push_back(pair(y, z));
        edge[y].push_back(pair(x, z));
    }

    return;
}

void dfs(const lint N, lint curnode, lint pnode, lint cost, lint lv,
         std::vector<std::vector<pair>> &parent,
         std::vector<std::vector<pair>> &edge, std::vector<lint> &level) {

    parent[curnode][0].next = pnode;
    parent[curnode][0].cost = cost;
    level[curnode] = lv;

    for(auto i=edge[curnode].begin(); i<edge[curnode].end(); ++i) {
        if(i->next == pnode) continue;

        dfs(N,i->next,curnode,i->cost,lv+1,parent,edge,level);
    }
}

void mkpnt(const lint N, const lint MAX, std::vector<std::vector<pair>> &parent) {
    for(int k=1; k<=MAX; ++k) {
        for(int i=1; i<=N; ++i) {
            parent[i][k].next = parent[parent[i][k-1].next][k-1].next;
            parent[i][k].cost = parent[parent[i][k-1].next][k-1].cost + parent[i][k-1].cost;
        }
    }
}

lint LCA_one(lint a, lint b, std::vector<std::vector<pair>> &parent,
             std::vector<lint> &level, const lint N, const lint MAX) {
    
    lint ret_cost = 0;

    if(level[a] < level[b]) {
        std::swap(a,b);
    }

    if(level[a] != level[b]) {
        for(lint i=MAX;i>=0;--i) {
            if(level[parent[a][i].next] >= level[b]) {
                ret_cost+=parent[a][i].cost;
                a = parent[a][i].next;
            }
        }
    }

    if(a==b) return ret_cost;

    for(int i=MAX;i>=0;--i) {
        if(parent[a][i].next != parent[b][i].next) {
            ret_cost+=parent[a][i].cost;
            ret_cost+=parent[b][i].cost;

            a = parent[a][i].next;
            b = parent[b][i].next;
        }
    }
    return ret_cost+parent[a][0].cost+parent[b][0].cost;
}

lint find(const lint MAX, lint target, lint copy_a, std::vector<std::vector<pair>> &parent) {
    for(int i=MAX;i>=0;--i) {
        if(target - (1<<i) >= 1) {
            target -= (1<<i);
            copy_a = parent[copy_a][i].next;
        }
    }    
    return copy_a;
}

// a->b k번째 수 // lca를 돌려야 최대노드 수를 알 수 있음
lint LCA_two(lint a, lint b, lint target, std::vector<std::vector<pair>> &parent,
             std::vector<lint> &level, const lint N, const lint MAX) {

    if(a == b) return a;

    lint topdist = 0;
    lint totdist = 0;
    
    lint copy_a = a;
    lint copy_b = b;

    if (level[a] < level[b]) { // swap한경우 a - v, b - u
        std::swap(a,b);

        for(lint i=MAX; i>=0; --i) {
            if(level[parent[a][i].next] >= level[b]) {
                topdist += (1<<i);
                totdist += (1<<i);
                a = parent[a][i].next;
            }
        }

        if(a == b) {
            topdist += 1;
            totdist += 1;

            return find(MAX,totdist-target+1,copy_b,parent);
        }

        else {
            for(lint i=MAX; i>=0; --i) {
                if(parent[a][i].next != parent[b][i].next) {
                    topdist += (1<<i);
                    totdist += (1<<i)*2;

                    a = parent[a][i].next;
                    b = parent[b][i].next;
                }
            }
            topdist += 2;
            totdist += 3;

            if(totdist+1 - topdist > target) {
                return find(MAX,target,copy_a,parent);
            }

            else if(totdist+1 - topdist < target) {
                return find(MAX,totdist-target+1,copy_b,parent);
            }

            else {
                return parent[a][0].next;
            }
        }
    }

    else { // 안한경우 
        if(level[a] != level[b]) { // level이 같은 경우도 있음
            for(lint i=MAX; i>=0; --i) {
                if(level[parent[a][i].next] >= level[b]) {
                    topdist += (1<<i);
                    totdist += (1<<i);
                    a = parent[a][i].next;
                }
            }
        }
        if(a == b) {
            topdist += 1;
            totdist += 1;

            if(target < topdist) {
                return find(MAX,target,copy_a,parent);
            }
            else {
                return a;   
            }
        }

        else {
            for(int i=MAX; i>=0; --i) {
                if(parent[a][i].next != parent[b][i].next) {
                    topdist += (1<<i);
                    totdist += (1<<i)*2;

                    a = parent[a][i].next;
                    b = parent[b][i].next;
                }
            }
            topdist += 2;
            totdist += 3;

            if(target < topdist) {
                return find(MAX,target,copy_a,parent);
            }

            else if(target > topdist) {
                target = totdist - target + 1;
                return find(MAX,target,copy_b,parent);
            }

            else {
                return parent[a][0].next;
            }
        }
    }
    return 0;
}

int main() {
    fastio;

    lint N;
    std::cin >> N;

    const lint MAX = (lint)ceil(log2(N + 1));

    std::vector<std::vector<pair>> edge(N + 2, std::vector<pair>());
    std::vector<std::vector<pair>> parent(N + 2, std::vector<pair>(MAX + 2, pair(0, 0)));
    std::vector<lint> level(N + 2, 0);

    input(edge,N);

    dfs(N,1,0,0,1,parent,edge,level);
    
    mkpnt(N,MAX,parent);

    lint M;
    std::cin >> M;
    for(lint i=0;i<M;++i) {
        lint x;
        std::cin >> x;
        if(x == 1) {
            lint y,z;
            std::cin >> y >> z;

            std::cout << LCA_one(y,z,parent,level,N,MAX) << '\n';
        }
        if(x == 2) {
            lint q,w,e;
            std::cin >> q >> w >> e;

            std::cout << LCA_two(q,w,e,parent,level,N,MAX) << '\n';
        }
    }


    return 0;
}