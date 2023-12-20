#include <iostream>
#include <queue>
#include <algorithm>

int box[102][102][102];
int N,M,H;
bool visited[102][102][102];
int day[102][102][102];
struct pair{
    int first;
    int second;
    int third;
};

int dx[6]={1,-1,0,0,0,0};
int dy[6]={0,0,1,-1,0,0};
int dz[6]={0,0,0,0,1,-1};
int col,row,height;
std::queue<pair> Q;

bool check() {
    for(int k=1;k<=H;++k) {
        for(int i=1;i<=N;++i) {
            for(int j=1;j<=M;++j) {
                if(box[i][j][k]==0) {
                    return false; // 아직 다 익지 않음.
                } 
            }
        }
    }
    return true;
}

void bfs() {
    while(!Q.empty()) {
        col=Q.front().first;
        row=Q.front().second;
        height=Q.front().third;
        Q.pop();
        box[col][row][height]=1;
        for(int i=0;i<6;++i) {
            int ncol=col+dx[i];
            int nrow=row+dy[i];
            int nheight=height+dz[i];
            if(0<ncol&&ncol<=N&&0<nrow&&nrow<=M&&0<nheight&&nheight<=H&&box[ncol][nrow][nheight]==0&&!visited[ncol][nrow][nheight]) {
                day[ncol][nrow][nheight]=day[col][row][height]+1;
                box[ncol][nrow][nheight]=1;
                visited[ncol][nrow][nheight]=true;
                Q.push({ncol,nrow,nheight});
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    
    std::cin >> M >> N >> H; // box[N][M][H];
    for(int k=1;k<=H;++k) {
        for(int i=1;i<=N;++i) {
            for(int j=1;j<=M;++j) {
                std::cin >> box[i][j][k];
            }
        }
    }
    for(int k=1;k<=H;++k) {
        for(int i=1;i<=N;++i) {
            for(int j=1;j<=M;++j) {
                if(box[i][j][k]==1) {
                    Q.push({i,j,k});
                }
            }
        }
    }

    bfs();
    
    if(!check()) std::cout << "-1";
    else {
        int maxi=0;
        for(int k=1;k<=H;++k) {
            for(int i=1;i<=N;++i) {
                for(int j=1;j<=M;++j) {
                    maxi=std::max(maxi,day[i][j][k]);
                }
            }
        }
        std::cout << maxi;
    }
    return 0;
}