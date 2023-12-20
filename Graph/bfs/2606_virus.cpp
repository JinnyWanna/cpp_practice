#include <iostream>
#include <queue>

int pc, line;
int cnt(0);
bool node_link[101][101];
bool visited[101];
std::queue<int> Q;

void dfs(int cur_node) {

    Q.push(cur_node);

    while(!Q.empty()) {
        cur_node=Q.front();
        Q.pop();
        for(int i=1;i<=pc;++i) {
            if(!visited[i]&&node_link[cur_node][i]) {
                visited[i]=true;
                Q.push(i);
                cnt++;
            } 
        }
    }
}
 
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::cin >> pc >> line;
    for(int i=0;i<line;++i) {
        int x,y;
        std::cin >> x >> y;
        node_link[x][y]=true;
        node_link[y][x]=true;
    }
    visited[1]=true;

    dfs(1); 

    std::cout << cnt << '\n';
    return 0;
}