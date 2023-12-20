#include <iostream>
#include <algorithm>
#include <queue>

struct pair {
    int first;
    int second;
    int move;
};

char map[102][102];
int N,M;

int delta[4][2]={{-1,0},{1,0},{0,-1},{0,1}};

void bfs(int col,int row,int k) {
    std::queue<pair> Q;
    Q.push({col,row,k});
    
    while(!Q.empty()) {
        col=Q.front().first;
        row=Q.front().second;
        k=Q.front().move;
        if(col==N&&row==M) {
            std::cout << k;
            return;
        }
        map[col][row]='0';
        Q.pop();
        for(int i=0;i<4;++i) {
            int ncol=col+delta[i][0];
            int nrow=row+delta[i][1];
            if(map[ncol][nrow]=='1') {
                Q.push({ncol,nrow,k+1});
                map[ncol][nrow] = '0';
            }
        }
    }
}

int main() {

    std::cin >> N >> M;
    for(int i=1;i<=N;++i) {
        for(int j=1;j<=M;++j) {
        std::cin >> map[i][j];
        }
    }

    bfs(1,1,1);

    return 0;
}