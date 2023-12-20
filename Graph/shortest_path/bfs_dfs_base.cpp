#include <iostream>
#include <queue>
bool visited_dfs[1001]={true,};
bool visited_bfs[1001]={true,};
int node,line,startnode;
bool arr[1001][1001];
std::queue<int> Q;

void dfs(int cur_point) {

    std::cout << cur_point << ' ';

    for(int i=1;i<=node;++i) {
        if(arr[cur_point][i]) {
            if(!visited_dfs[i]) {
                visited_dfs[i]=true;
                dfs(i);
            }
        }
    }
}

void bfs(int cur_point) { 
    // 재귀 안쓰임. 첫 수만 큐에 넣어주고, true해준뒤, while문으로 진행
    Q.push(cur_point);
    visited_bfs[cur_point]=true;

    while(!Q.empty()) {
        cur_point=Q.front();
        Q.pop();

        std::cout << cur_point << ' '; 

        for(int i=1;i<=node;++i) {
            if(arr[cur_point][i]&&!visited_bfs[i]) {
                visited_bfs[i]=1;
                Q.push(i);
            }
        }
    }   
}

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    
    std::cin >> node >> line >> startnode;

    for(int i=0;i<line;++i) {
        int x,y;
        std::cin >> x >> y;
        arr[x][y]=true;
        arr[y][x]=true;
    }
    visited_dfs[startnode]=true;
    dfs(startnode);
    std::cout << '\n';
    bfs(startnode);
    std::cout << '\n';
    return 0;
}