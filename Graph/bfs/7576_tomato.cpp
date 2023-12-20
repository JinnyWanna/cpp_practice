#include <iostream>
#include <queue>
#include <algorithm>

int box[1002][1002];
int N,M;
bool visited[1002][1002];
int day[1002][1002];
struct pair{
    int first;
    int second;
};

int delta[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
int col,row;
std::queue<pair> Q;

bool check() {
    for(int i=1;i<=N;++i) {
        for(int j=1;j<=M;++j) {
            if(box[i][j]==0) {
                return false; // 아직 다 익지 않음.
            } 
        }
    }
    return true;
}

void bfs() {
    while(!Q.empty()) {
        col=Q.front().first;
        row=Q.front().second;
        Q.pop();
        box[col][row]=1;
        for(int i=0;i<4;++i) {
            int ncol=col+delta[i][0];
            int nrow=row+delta[i][1];
            if(0<ncol&&ncol<=N&&0<nrow&&nrow<=M&&box[ncol][nrow]==0&&!visited[ncol][nrow]) {
                day[ncol][nrow]=day[col][row]+1;
                box[ncol][nrow]=1;
                visited[ncol][nrow]=true;
                Q.push({ncol,nrow});
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    
    std::cin >> M >> N; // box[N][M];

    for(int i=1;i<=N;++i) {
        for(int j=1;j<=M;++j) {
            std::cin >> box[i][j];
        }
    }

    for(int i=1;i<=N;++i) {
        for(int j=1;j<=M;++j) {
            if(box[i][j]==1) {
                Q.push({i,j});
            }
        }
    }
    bfs();
    
    if(!check()) std::cout << "-1";
    else {
        int maxi=0;
        for(int i=1;i<=N;++i) {
            for(int j=1;j<=M;++j) {
                maxi=std::max(maxi,day[i][j]);
            }
        }
        std::cout << maxi;
    }
    return 0;
}