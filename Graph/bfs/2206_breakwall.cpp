#include <iostream>
#include <algorithm>
#include <queue>

struct pair{
    int first;
    int second;
    bool wall;
    int cnt;
};
//
char map[1001][1001];
int N,M;
bool visited[1001][1001];
bool wall_visited[1001][1001];
//
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
//
std::queue<pair> Q;

int bfs(int cur_col,int cur_row,bool break_wall,int cnt) { 
    Q.push({cur_col,cur_row,break_wall,cnt});
    visited[cur_col][cur_row]=true;

    while(!Q.empty()) {
        cur_col=Q.front().first;
        cur_row=Q.front().second;
        break_wall=Q.front().wall;
        cnt=Q.front().cnt;
        if(cur_col==N&&cur_row==M) {
            return cnt;
        }
        Q.pop();
        for(int i=0;i<4;++i) {
            int ncol=cur_col+dx[i];
            int nrow=cur_row+dy[i];
            if(0<ncol&&ncol<=N&&0<nrow&&nrow<=M&&!break_wall&&!visited[ncol][nrow]) {
                if(map[ncol][nrow]=='0') {
                    visited[ncol][nrow]=true;
                    Q.push({ncol,nrow,break_wall,cnt+1});
                } // 들어감
                else if(map[ncol][nrow]=='1') {
                    wall_visited[ncol][nrow]=true;// 이제 벽뚫고 움직인 경로
                    Q.push({ncol,nrow,true,cnt+1});
                }
            }
            else if(0<ncol&&ncol<=N&&0<nrow&&nrow<=M&&break_wall&&!wall_visited[ncol][nrow]) {
                if(map[ncol][nrow]=='0') {
                    wall_visited[ncol][nrow]=true;
                    Q.push({ncol,nrow,break_wall,cnt+1});
                } // 들어감
            }
        }
    }
    return 0;
}

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::cin >> N >> M;
    for(int i=1;i<=N;++i) {
        for(int j=1;j<=M;++j) {
            std::cin >> map[i][j];
        }
    }

    int ans=bfs(1,1,false,1);

    if(ans==0) {
        std::cout << "-1";
        return 0;
    }

    std::cout << ans;

    return 0;
}