#include <iostream>
#include <vector>
#include <queue>

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

int map_arr[501][501];

struct pair{
    int value;
    int row_index;
    int col_index;
};

struct cmp{
    bool operator()(pair A, pair B) {
        if(A.value==B.value) {
            if(A.row_index==B.row_index) {
                return A.col_index > B.col_index;
            }
            return A.row_index > B.row_index;
        }
        return A.value < B.value;
    }
};

void check(int map[501][501],std::priority_queue<pair,std::vector<pair>,cmp> &pQ,int row,int col) {
    while(!pQ.empty()) {
        int cul_row = pQ.top().row_index;
        int cul_col = pQ.top().col_index;
        int value = pQ.top().value;
        pQ.pop();

        for(int i=0;i<4;++i) { // 현재 위치와 같은 숫자를 만난경우는 더하면안됨.
            int nrow = cul_row + dx[i];
            int ncol = cul_col + dy[i];
            if(1<=nrow&&nrow<=row&&1<=ncol&&ncol<=col) {
                if(map_arr[nrow][ncol]<=value) continue;
                map[cul_row][cul_col]+=map[nrow][ncol];
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int map[501][501]={1,};
    map[1][1]=1;
    std::priority_queue<pair,std::vector<pair>,cmp> pQ;
    
    int row, col;
    std::cin >> row >> col;
    
    for(int i=1;i<=row;++i) {
        for(int j=1;j<=col;++j) {
            int num;
            std::cin >> num;
            map_arr[i][j]=num;
            pQ.push({num,i,j});
        }
    }
    
    check(map,pQ,row,col);

    std::cout << map[row][col];
    return 0;
}

// https://jaimemin.tistory.com/364